#!/bin/bash

if [[ "$(docker images -q nginx 2> /dev/null)" == "" ]]; then
    docker pull nginx
fi
docker run -d -p 81:81 --name server nginx

docker cp server.c server:/server.c
docker cp nginx/nginx.conf server:/etc/nginx/nginx.conf

docker exec server apt-get update
docker exec server apt-get install -y gcc libfcgi-dev spawn-fcgi

docker exec server gcc /server.c -o /server -lfcgi
docker exec server spawn-fcgi -p 8080 /server
docker exec server nginx -s reload

open http://localhost:81
echo "Press Enter to exit"
read key

docker stop server
docker rm server
docker rmi -f nginx
