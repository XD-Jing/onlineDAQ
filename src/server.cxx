#include <string>
#include <iostream>
#include <sMDT/sMDTServer.h>

int main(){

    sMDTServer *server = new sMDTServer();
    server->Listen();
    return 0;

}
