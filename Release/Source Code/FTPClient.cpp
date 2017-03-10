//
// Created by leiszner on 3/9/17.
//

#include "FTPClient.h"

using namespace std;

void FTPClient::connectSocket(char *ip, unsigned int port)
{
    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client < 0)
    {
        cout << "Creating socket failed" << endl;
        exit(1);
    }

    cout << "Socket has been created" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((uint16_t) port);

    inet_pton(AF_INET, ip, &server_addr.sin_addr.s_addr);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "Connected to the server" << endl;
        cout << "Port number: " << port << endl;
        cout << "IP: " << ip << endl;
}

char* FTPClient::receiveMsg()
{
    buffer[recv(getClient(), buffer, buffersize, 0)] = '\0';
    char *bufferPointer = buffer;
    cout << "Received from server:\t\t" << buffer;

    return bufferPointer;
}

char* FTPClient::retriveFile()
{
    buffer[recv(getClient(), buffer, buffersize, 0)] = '\0';
    char *bufferPointer = buffer;
    cout << "Retrived following file:\t" << buffer;

    return bufferPointer;
}

void FTPClient::sendMsg(char message[], unsigned int buffersize)
{
    if (send(client, message, buffersize, 0) == -1)
    {
        cout << "Could not send message";
        exit(1);
    }
    else
    {
        cout << "Send message:\t\t\t\t" << message;
    }
}

unsigned int FTPClient::calcNewPort(int a, int b)
{
    int multiplier = 256;
    return unsigned (a * multiplier) + b;
}

int FTPClient::getClient()
{
    return client;
}

void FTPClient::downloadFile(char *filename)
{
    ofstream myfile;

    myfile.open(filename);
    myfile << retriveFile();
    myfile.close();
}