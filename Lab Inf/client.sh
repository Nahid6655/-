#!/bin/bash

echo "Клиент для отправки сообщений на сервер"
echo "Введите сообщение (для выхода введите 'quit'):"

while true; do
    read -p "> " message
    
    if [ "$message" = "quit" ]; then
        break
    fi
    
    # Отправляем сообщение серверу и слушаем ответ на другом порту
    echo "$message" | nc localhost 12345
done
