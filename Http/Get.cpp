#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "../lib/Split.hpp"
#include "Fetch.hpp"


// TODO: Generate new instance and set heap every request
Http::Response g_Res;

void GetThreadFunc(const char* hostname) {
    printf("url: %s\n", hostname);
    int sock;
    char buf[32];

    sock = Socket::GetSock(hostname);
    std::cout << "sock: " << sock << std::endl;

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

        g_Res.m_RawText += buf; 
    }
    g_Res.m_Status = true;
    close(sock);
    return;
}

Http::Response* Http::Get(const char* url) {
    std::thread th(GetThreadFunc, url);
    th.join();
    std::vector<std::string> elems = SplitStr(g_Res.m_RawText, '\n');
    bool isHeaderDone = false;
    for (int i = 0; i < elems.size(); i++ ) {
        if (elems[i] == "\r\n") {
            isHeaderDone = true;
            continue;
        }
        if (isHeaderDone) {
            g_Res.m_BodyText += elems[i]; 
        } else {
            g_Res.m_HeaderText += elems[i]; 
        }
    }

    return &g_Res;
}


