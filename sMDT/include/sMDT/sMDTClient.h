#ifndef _sMDTClient_h_
#define _sMDTClient_h_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class sMDTClient
{
    private:

        int client_sockfd;
        int len;
        struct sockaddr_in remote_addr;
        int sin_size;
        char buf[BUFSIZ];
        int i;


    public:
        sMDTClient();
        ~sMDTClient();

        int Init();
        int Send();
        int Work();
};

#endif
