#include"sMDT/sMDTServer.h"
#include <iostream>

sMDTServer::sMDTServer(){
    try {Init();}
    catch (const char* msg) {std::cerr << msg << std::endl;}
}

sMDTServer::~sMDTServer(){
    //close(server_sockfd);
}

int sMDTServer::Init(){
    memset(&my_addr,0,sizeof(my_addr));
    my_addr.sin_family=AF_INET;
    my_addr.sin_addr.s_addr=INADDR_ANY;
    my_addr.sin_port=htons(8000);

    if ((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0) throw "socket error";
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0) throw "bind error";

    sin_size=sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");
    return 0;

}

int sMDTServer::Receive(){
    if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,(socklen_t*)&sin_size))<0) throw "receive error";
    printf("received packet from %s:\n",inet_ntoa(remote_addr.sin_addr));
    buf[len]='/0';
    printf("contents: %s\n",buf);

    return 0;
}

int sMDTServer::Listen(){
    while (1){
        try {Receive();}
        catch (const char* msg) {std::cerr << msg << std::endl;}
    }
    return 0;
}

