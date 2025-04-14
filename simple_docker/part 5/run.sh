#!/bin/bash

export DOCKER_CONTENT_TRUST=1
docker build -t hello:world .
docker images

docker save -o hello.tar hello:world
dockle --input hello.tar
rm hello.tar

#docker run -d -p 80:81 -v /nginx:/etc/nginx/ --name server hello:world
unset DOCKER_CONTENT_TRUST
docker run -d -p 80:81 --name server hello:world

open http://localhost:80/
open http://localhost:80/status
echo "Press Enter to exit"
read key

docker stop server
docker rm server
docker rmi -f hello:world
