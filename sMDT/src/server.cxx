#include "sMDT/server.h"
#include "sMDT/format.h"
#include <iostream>
#include <unistd.h>

server::server(){
    try {Init();}
    catch (const char* msg) {std::cerr << msg << std::endl;}
}

server::~server(){
    close(sockfd);
}

int server::Init(){
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(8080);

    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0) throw "socket error";
    if (bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr))<0) throw "bind error";

    return 0;
}

int server::Send(buffXDC buffer){
    if((len=sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr)))<0) throw "sendint error";
    return 0;
}
