//
// Created by leiszner on 3/9/17.
//

#ifndef FTP_FTPCLIENT_H
#define FTP_FTPCLIENT_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fstream>

using namespace std;

class FTPClient
{
    public:
        void connectSocket(char *ip, unsigned int port);
        void sendMsg(char *message, unsigned int buffersize);
        void downloadFile(char *filename);
        char* receiveMsg();
        char* retriveFile();
        unsigned int calcNewPort(int a, int b);
        int getClient();
    private:
        int client;
        const unsigned int buffersize = 1024;
        char buffer[];
        struct sockaddr_in server_addr;
};


#endif //FTP_FTPCLIENT_H
