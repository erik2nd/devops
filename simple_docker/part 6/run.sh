#!/bin/bash

docker-compose build
docker-compose up

echo "Press Enter to exit"
read key

docker-compose down
docker-compose down --rmi all
