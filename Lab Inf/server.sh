#!/bin/bash
port=12345
echo "TCP-server is start on $port"
while true; do
nc -l -p $port | while read line; do
echo "Client: $line"
echo "OK: $line" | nc localhost $port 
done
sleep 1
done
