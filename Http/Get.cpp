#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



#include "Fetch.hpp"


void GetThreadFunc(const char* hostname) {
    printf("url: %s\n", hostname);
    struct sockaddr_in server;
    int sock;
    char buf[32];
    unsigned int** pAddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0 ) {
        perror("socket");
        return;
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
            } else {
                printf("%s: %s\n", hstrerror(h_errno), hostname);
            }
            return;
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
            return;
        }
    } else {
        if (connect(sock, (struct sockaddr*)&server, sizeof(server)) != 0) {
            perror("connect");
            return;
        }
    }

    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "GET / HTTP/1.0\r\n\r\n");

    int idx = write(sock, buf, (int)strlen(buf));
    if (idx < 0) {
        perror("write");
        return;
    }

    while (idx > 0) {
        memset(buf, 0, sizeof(buf));
        idx = read(sock, buf, sizeof(buf));
        if (idx < 0) {
            perror("read");
            return;
        }
        write(1, buf, idx);
    }

    close(sock);
    return;
}

Http::Response* Http::Get(const char* url) {
    std::thread th(GetThreadFunc, url);
    th.join();
    auto res = new Http::Response;
    res->m_Status = true;
    res->m_BodyText = "bodyText";
    return res;
}


