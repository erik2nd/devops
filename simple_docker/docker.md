# Simple Docker

## Contents

1. [Ready-made docker](#1-ready-made-docker)  
2. [Operations with container](#2-operations-with-container)  
3. [Mini web server](#3-mini-web-server)  
4. [Your own docker](#4-your-own-docker)  
5. [Dockle](#5-dockle)  
6. [Basic Docker Compose](#6-basic-docker-compose)
 
<br>

## 1. Ready-made docker

- **Task:** 
    - Take the official docker image from nginx and download it using docker pull

- **Command:**
    - `docker pull nginx`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_1.png" alt="Downloading docker image from nginx" title="Downloading docker image from nginx" width="460"> </p>

    *** 
    <br>

- **Task:** 
    - Check for the docker image with docker images

- **Command:**
    - `docker images`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_2.png" alt="Checking for the nginx docker image" title="Checking for the nginx docker image" width="350"> </p>

    *** 
    <br>

- **Task:** 
    - Run docker image with docker run -d [image_id|repository]

- **Command:**
    - `docker run -d nginx`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_3.png" alt="Running nginx docker image" title="Running nginx docker image" width="410"> </p>

    *** 
    <br>

- **Task:** 
    - Check that the image is running with docker ps

- **Command:**
    - `docker ps`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_4.png" alt="Checking that nginx image is running" title="Checking that nginx image is running" width="640"> </p>

    *** 
    <br>

- **Task:** 
    - View container information with docker inspect [container_id|container_name]
    - From the command output define the container size, list of mapped ports and container ip

- **Commands:**
    - `docker inspect 0dd1d23278c3`
    - `docker system df -v`

- **Output:**     
    - Image size: 1.09 kB
    - Container size: 192 MB
    - Mapped ports: 80/tcp
    - Container ip: 172.17.0.2

    <p style="text-align: left; margin: 0;">
    <img src="images/1_5.png" alt="nginx container information" title="nginx container information" width="470"> 
    <img src="images/1_6.png" alt="nginx container information" title="nginx container information" width="470"> </p>
    <p style="text-align: left; margin: 0;">
    <img src="images/1_7.png" alt="Sizes of image and container" title="Sizes of image and container" width="750"> </p>

    *** 
    <br>

- **Task:** 
    - Stop docker container with docker stop [container_id|container_name]

- **Command:**
    - `docker stop 0dd1d23278c3`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_8.png" alt="Stopping nginx container" title="Stopping nginx container" width="280"> </p>

    *** 
    <br>

- **Task:** 
    - Check that the container has stopped with docker ps

- **Command:**
    - `docker ps`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_9.png" alt="Checking that nginx container has stopped" title="Checking that nginx container has stopped" width="450"> </p>

    *** 
    <br>

- **Task:** 
    - Run docker with ports 80 and 443 in container, mapped to the same ports on the local machine, with run command
    - Check that the nginx start page is available in the browser at localhost:80

- **Command:**
    - `docker run -d -p 80:80 -p 443:443 nginx`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_10.png" alt="Running nginx docker image on ports 80 and 443" title="Running nginx docker image on ports 80 and 443" width="480"> 
    <img src="images/1_11.png" alt="localhost:80 content" title="localhost:80 content" width="450"> </p>

    *** 
    <br>

- **Task:** 
    - Restart docker container with docker restart [container_id|container_name]
    - Check in any way that the container is running

- **Commands:**
    - `docker restart cbb328e83e62`
    - `docker ps`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_12.png" alt="Restarting nginx container and checking that it is running" title="Restarting nginx container and checking that it is running" width="800"> </p>


## 2. Operations with container

- **Task:** 
    - Read the nginx.conf configuration file inside the docker container with the exec command

- **Command:**
    - `docker exec dbcfaac0fb43 cat /etc/nginx/nginx.conf`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_1.png" alt="Restarting nginx container and checking that it is running" title="Restarting nginx container and checking that it is running" width="460"> </p>

    *** 
    <br>

- **Task:** 
    - Create a nginx.conf file on a local machine
    - Configure it on the /status path to return the nginx server status page

- **Command:**
    - `touch nginx.conf`

- **File:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_2.png" alt="Configured nginx.conf file" title="Configured nginx.conf file" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Copy the created nginx.conf file inside the docker image using the docker cp command
    - Restart nginx inside the docker image with exec
    - Check that localhost:80/status returns the nginx server status page

- **Commands:**
    - `docker cp nginx.conf dbcfaac0fb43:/etc/nginx/nginx.conf`
    - `docker exec dbcfaac0fb43 nginx -s reload`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_3.png" alt="Copying nginx.conf file and restarting nginx inside docker image" title="Copying nginx.conf file and restarting nginx inside docker image" width="660"> 
    <img src="images/2_4.png" alt="localhost:80/status content" title="localhost:80/status content" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Export the container to a container.tar file with the export command

- **Command:**
    - `docker export -o container.tar dbcfaac0fb43`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_5.png" alt="Exporting docker container" title="Exporting docker container" width="400"> </p>

    *** 
    <br>

- **Task:** 
    - Stop the container

- **Command:**
    - `docker stop dbcfaac0fb43`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_6.png" alt="Stopping docker container" title="Stopping docker container" width="340"> </p>

    *** 
    <br>

- **Task:** 
    - Delete the image with docker rmi [image_id|repository]without removing the container first

- **Command:**
    - `docker rmi -f nginx`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_7.png" alt="Forced deleting nginx image" title="Forced deleting nginx image" width="560"> </p>

    *** 
    <br>

- **Task:** 
    - Delete stopped container

- **Commands:**
    - `docker rm dbcfaac0fb43`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_8.png" alt="Deleting stopped nginx container" title="Deleting stopped nginx container" width="450"> </p>

    *** 
    <br>

- **Task:** 
    - Import the container back using the import command

- **Command:**
    - `docker import container.tar new-nginx`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_9.png" alt="Importing container back from container.tar file" title="Importing container back from container.tar file" width="460"> </p>

    *** 
    <br>

- **Task:** 
    - Run the imported container
    - Check that localhost:80/status returns the nginx server status page

- **Command:**
    - `docker run -d -p 80:80 new-nginx nginx -g "daemon off;"`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2_10.png" alt="Running imported container" title="Running imported container" width="720"> 
    <img src="images/2_4.png" alt="localhost:80/status content" title="localhost:80/status content" width="500"> </p>

- **Extra:**
    - *nginx -g "daemon off;"* - this tells Nginx to run in the foreground, which is required for Docker containers to stay running

## 3. Mini web server   

- **Task:** 
    - Write a mini server in C and FastCgi that will return a simple page saying Hello World!

- **Command:**
    - `touch server.c`

- **File:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/3_1.png" alt="Mini server in C and FastCgi" title="Mini server in C and FastCgi" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Write nginx.conf that will proxy all requests from port 81 to 127.0.0.1:8080
    - Put the nginx.conf file under ./nginx/nginx.conf 

- **Commands:**
    - `mkdir nginx`
    - `touch nginx/nginx.conf`

- **File:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/3_2.png" alt="Created nginx.conf file" title="Created nginx.conf file" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Run the written mini server via spawn-fcgi on port 8080
    - Check that browser on localhost:81 returns the page that was written

- **Command:**
    - `bash run.sh`

- **File & output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/3_3.png" alt="sh script to run written mini server via spawn-fcgi on port 8080" title="sh script to run written mini server via spawn-fcgi on port 8080" width="500"> 
    <img src="images/3_4.png" alt="localhost:81/status content" title="localhost:81/status content" width="500"> </p>

## 4. Your own docker 

- **Task:** 
    - Write your own docker image that:
        1) builds mini server sources on FastCgi from [3](#3-mini-web-server)
        2) runs it on port 8080
        3) copies inside the image written ./nginx/nginx.conf
        4) runs nginx

- **Commands:**
    - `touch Dockerfile`

- **File:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/4_1.png" alt="Created Dockerfile" title="Created Dockerfile" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Build the written docker image with docker build, specifying the name and tag
    - Check with docker images that everything is built correctly
    - Run the built docker image by mapping port 81 to 80 on the local machine and mapping the ./nginx folder inside the container to the address where the nginx configuration files are located 
    - Check that the page of the written mini server is available on localhost:80

- **Command:**
    - `bash run.sh`

- **File & output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/4_2.png" alt="sh script to build and run the written docker image" title="sh script to build and run the written docker image" width="500"> 
    <img src="images/4_3.png" alt="localhost:80 content" title="localhost:80 content" width="500"> </p>

- **Extra:**
    - To mount a volume, the path /nginx must be shared from the host and known to Docker. To do it, shared paths should be configured from Docker -> Preferences... -> Resources -> File Sharing

    - Volume is a special mechanism for data storage that allows containers to retain data outside their isolated environment. Flag -v allows to connect a folder or file from host's filesystem to the filesystem of the container. Data stored in volumes persists even after the container is stopped or removed, unlike data stored inside the container itself, which disappears when the container is deleted
   
    *** 
    <br>

- **Task:** 
    - Add proxying of /status page in ./nginx/nginx.conf to return the nginx server status
    - Restart docker image
    - Check that localhost:80/status now returns a page with nginx status

- **Command:**
    - `docker restart server`

- **File & output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/4_4.png" alt="Changed nginx.conf file" title="Changed nginx.conf file" width="500">
    <img src="images/4_5.png" alt="localhost:80/status content" title="localhost:80/status content" width="500"> </p>

## 5. Dockle   

- **Task:** 
    - Check the image from the previous task with dockle [image_id|repository]

- **Commands:**
    - `docker save -o hello.tar hello:world`
    - `dockle --input hello.tar`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/5_1.png" alt="Vulnerabilities of image" title="Vulnerabilities of image" width="680"> </p>

    ***
    <br>

- **Task:** 
    - Fix the image so that there are no errors or warnings when checking with dockle

- **Commands:**
    - `docker save -o hello.tar hello:world`
    - `dockle --input hello.tar`

- **File & output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/5_2.png" alt="Fixed Dockerfile" title="Fixed Dockerfile" width="500">
    <img src="images/5_3.png" alt="Checking image for vulnerabilities after fix" title="Checking image for vulnerabilities after fix" width="560"> </p>

- **Extra:**
    - Command for clearing Docker cache: `docker system prune -a`    

## 6. Basic Docker Compose

- **Task:** 
    - Write a docker-compose.yml file, using which:
        1) Start the docker container from Part 5 (it must work on local network, i.e., you don't need to use EXPOSE instruction and map ports to local machine)
        2) Start the docker container with nginx which will proxy all requests from port 8080 to port 81 of the first container
    - Map port 8080 of the second container to port 80 of the local machine    

- **Files:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/6_1.png" alt="Written docker-compose.yml file" title="Written docker-compose.yml file" width="500">
    <img src="images/6_2.png" alt="Dockerfile for second container" title="Dockerfile for second container" width="500"> 
    <img src="images/6_3.png" alt="nginx.conf for second container" title="nginx.conf for second container" width="500"> </p>

    *** 
    <br>

- **Task:** 
    - Build and run the project with the docker-compose build and docker-compose up commands
    - Check that the browser returns the page you wrote on localhost:80 as before

- **Commands:**
    - `bash run.sh`    

- **File:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/6_4.png" alt="sh script to build and run project" title="sh script to build and run project" width="500">
    <img src="images/6_5.png" alt="localhost:80 content" title="localhost:80 content" width="500"> 
    <img src="images/6_6.png" alt="localhost:80/status content" title="localhost:80/status content" width="500">  </p>