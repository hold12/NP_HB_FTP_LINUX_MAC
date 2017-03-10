#include <iostream>
#include "FTPClient.h"

using namespace std;

int main()
{
    char ip[] = "130.226.195.126"; //Asigning ip as character array
    unsigned int port = 21; //Asigning port as unsigned int can't go into negative values

    FTPClient client; //Creating object of FTPClient
    client.connectSocket(ip, port); //Connects the client to FTP server using ip and port
    cout << endl; //Line spacing
    client.receiveMsg(); //Recevies message from FTP server
    client.sendMsg("HELLO\r\n", 7); //Sends message HELLO to FTP server
    client.receiveMsg();
    client.sendMsg("USER anonymous\r\n", 16);
    client.receiveMsg();
    client.sendMsg("PASS abc\r\n", 10);
    client.receiveMsg();
    client.sendMsg("PASV\r\n", 6);

    int num[6];
    //Gets the last two numbers in that variate
    sscanf(client.receiveMsg(),
           "227 Entering Passive Mode (%i,%i,%i,%i,%i,%i).\r\n",
           &num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);

    FTPClient secondClient;
    cout << endl;
    secondClient.connectSocket(ip, secondClient.calcNewPort(num[4], num[5]));
    cout << endl;
    client.sendMsg("RETR file.txt\r\n", 15);
    secondClient.downloadFile("Test.txt"); //Retrives file.txt and downloads file, as Test.txt
    client.receiveMsg();
    client.receiveMsg();
    client.sendMsg("CWD pub\r\n", 9); //Changes working directory
    client.receiveMsg();
    client.sendMsg("CWD 62501\r\n", 11);
    client.receiveMsg();
    client.sendMsg("PASV\r\n", 6);

    sscanf(client.receiveMsg(),
           "227 Entering Passive Mode (%i,%i,%i,%i,%i,%i).\r\n",
           &num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);

    close(secondClient.getClient()); //Closes socket

    FTPClient thirdClient;
    cout << endl;
    thirdClient.connectSocket(ip, thirdClient.calcNewPort(num[4], num[5]));
    cout << endl;
    client.sendMsg("RETR linuxchecklist.pdf\r\n", 25);
    thirdClient.downloadFile("file2.pdf");
    cout << endl;
    client.receiveMsg();
    client.receiveMsg();
    client.sendMsg("PASV\r\n", 6);

    sscanf(client.receiveMsg(),
           "227 Entering Passive Mode (%i,%i,%i,%i,%i,%i).\r\n",
           &num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);

    close(thirdClient.getClient());

    cout << endl;
    client.sendMsg("STOR /home/leiszner/SMTP.txt\r\n", 30); //TODO change filepath to the file you want to upload
    client.receiveMsg();

    client.sendMsg("Quit\r\n", 6);
    client.receiveMsg();

    close(client.getClient());

    return 0;
}