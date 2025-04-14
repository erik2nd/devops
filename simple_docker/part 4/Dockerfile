FROM nginx:latest

COPY server.c /server.c
COPY nginx/nginx.conf /etc/nginx/nginx.conf

RUN apt-get update && \
    apt-get install -y gcc libfcgi-dev spawn-fcgi && \
    gcc /server.c -o /server -lfcgi && \
    rm -rf /var/lib/apt/lists/*
    
CMD spawn-fcgi -p 8080 /server && nginx -g "daemon off;"
