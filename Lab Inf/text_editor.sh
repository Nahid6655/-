#!/bin/bash
touch notes.txt
echo "Write text"
while true; do 
read input 
if [ "$input" == "exit" ]; then
break 
fi 
echo " $input" >> notes.txt
done
echo " Text:"
cat notes.txt 
rm notes.txt 
