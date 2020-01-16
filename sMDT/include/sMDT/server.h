#ifndef _server_h_
#define _server_h_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sMDT/format.h"

class server
{
    private:

        int i;
        int sockfd;
        int len;
        struct sockaddr_in clie_addr;
        struct sockaddr_in serv_addr;
        int sin_size;
        char buf[BUFSIZ];


    public:
        server();
        ~server();

        int Init();
        int Send(buffXDC);
};

#endif
