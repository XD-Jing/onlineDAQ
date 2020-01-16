#include "sMDT/monitor.h"
#include "sMDT/format.h"
#include <iostream>
#include <unistd.h>

monitor::monitor(){
    try {Init();}
    catch (const char* msg) {std::cerr << msg << std::endl;}
    SwitchOn();
    g = new gui();
}

monitor::~monitor(){
    close(sockfd);
}

int monitor::Init(){
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    //addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    addr.sin_port=htons(8080);
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0) throw "socket error";
    if (bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr))<0) throw "bind error";

    printf("bind\n");
    return 0;
}

int monitor::SwitchOn(){
    printf("on\n");
    buffXDC buffer;
    int i;
    int s = sizeof(struct sockaddr);
    printf("%i\n", sizeof(buffer));
    while( true ){
        int n = recvfrom(sockfd, &buffer, 2* sizeof(buffer), 0, (struct sockaddr *) &addr, (socklen_t*)sizeof(struct sockaddr)); 
        printf("%i %i %i\n", n, buffer.indexXDC, buffer.channel);
        //int n = recvfrom(sockfd, &i, sizeof(i), 0, (struct sockaddr *) &addr, (socklen_t*)sizeof(struct sockaddr)); 
        //printf("receive %i\n", i);
        //printf("receive\n");
        g->update(buffer);
    }
    return 0;
}
