#include "sMDT/server.h"
#include "sMDT/format.h"
#include <iostream>
#include <unistd.h>

server::server(){
    i = 0;
    try {Init();}
    catch (const char* msg) {std::cerr << msg << std::endl;}
}

server::~server(){
    close(sockfd);
}

int server::Init(){
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    //serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(8080);

    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0) throw "socket error";
    //if (bind(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) throw "bind error";

    return 0;
}

int server::Send(buffXDC buffer){
    i++;
    if((len=sendto(sockfd, &buffer, 2*sizeof(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)))<0) throw "sendint error";
    //if((len=sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)))<0) throw "sendint error";
    return 0;
}
