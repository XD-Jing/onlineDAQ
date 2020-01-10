#include"sMDT/sMDTClient.h"
#include <iostream>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


sMDTClient::sMDTClient(){
    i = 0;
    try {Init();}
    catch (const char* msg) {std::cerr << msg << std::endl;}
}

sMDTClient::~sMDTClient(){
    //close(client_sockfd);
}

int sMDTClient::Init(){
    memset(&remote_addr,0,sizeof(remote_addr)); 
    remote_addr.sin_family=AF_INET;
    remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    remote_addr.sin_port=htons(8000);

    if ((client_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0) throw "socket error";

    return 0;
}

int sMDTClient::Send(){
    //strcpy(buf,"message %i\n", i++);
    sprintf(buf, "message %d", i++);
    printf("sending: %s\n",buf); 
    sin_size=sizeof(struct sockaddr_in);
    if((len=sendto(client_sockfd,buf,strlen(buf),0,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr)))<0) throw "sendint error";
    usleep(1000000);

    //if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,&sin_size))<0) throw "receive error";
    //printf("received packet from %s:\n",inet_ntoa(remote_addr.sin_addr));
    //buf[len]='/0';
    //printf("contents: %s\n",buf);

    return 0;
}

int sMDTClient::Work(){
    while (1){
        try {Send();}
        catch (const char* msg) {std::cerr << msg << std::endl;}
    }
    return 0;
}

