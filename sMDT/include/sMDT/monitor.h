#ifndef _monitor_h_
#define _monitor_h_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sMDT/format.h"
#include "sMDT/gui.h"

class monitor
{
    private:

        int sockfd;
        int len;
        struct sockaddr_in my_addr;
        struct sockaddr_in addr;
        int sin_size;
        char buf[BUFSIZ];
        gui *g;



    public:
        monitor();
        ~monitor();
        int Init();

        int SwitchOn();
};

#endif
