#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "Fetch.hpp"


int Socket::GetSock(const char* hostname) {
    int sock;
    struct sockaddr_in server;
    unsigned int** pAddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0 ) {
        perror("socket");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    server.sin_addr.s_addr = inet_addr(hostname);
    if(server.sin_addr.s_addr == 0xffffffff) {
        struct hostent *pHost;
        pHost = gethostbyname(hostname);
        if(pHost == NULL) {
            if (h_errno == HOST_NOT_FOUND) {
                printf("404 not found: %s\n", hostname);
                return -1;
            } else {
                printf("%s: %s\n", hstrerror(h_errno), hostname);
            }
            return -1;
        }

        pAddr = (unsigned int **)pHost->h_addr_list;
        while (*pAddr != NULL) {
            server.sin_addr.s_addr = *(*pAddr);

            if(connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0) {
                break;
            }
        }

        if (*pAddr == NULL) {
            perror("connect");
            return -1;
        }
    } else {
        if (connect(sock, (struct sockaddr*)&server, sizeof(server)) != 0) {
            perror("connect");
            return -1;
        }
    }

    return sock;
}

