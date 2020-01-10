#ifndef _sMDTServer_h_
#define _sMDTServer_h_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class sMDTServer
{
    private:

        int server_sockfd;
        int len;
        struct sockaddr_in my_addr;
        struct sockaddr_in remote_addr;
        int sin_size;
        char buf[BUFSIZ];


    public:
        sMDTServer();
        ~sMDTServer();

        int Init();
        int Receive();
        int Listen();
};

#endif
