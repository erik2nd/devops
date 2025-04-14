#include "fcgi_stdio.h"

int main() {
    while (FCGI_Accept() >= 0) {  // FCGI_Accept listens for requests
        // Send HTTP headers
        printf("Content-type: text/html\r\n\r\n");

        // Send the response body
        printf("<html><head><title>Hello</title></head>");
        printf("<body><h1>Hello, World!</h1></body></html>");
    }
    return 0;
}
