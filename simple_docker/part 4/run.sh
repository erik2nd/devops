#!/bin/bash

docker build -t hello:world .
docker images

#docker run -d -p 80:81 -v /nginx:/etc/nginx/ --name server hello:world
docker run -d -p 80:81 --name server hello:world

open http://localhost:80/
open http://localhost:80/status
echo "Press Enter to exit"
read key

docker stop server
docker rm server
docker rmi -f hello:world
