#ifndef UDPCOMM_H
#define UDPCOMM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

#define PORT        65432
#define MAX_LINE    1024

using namespace std;

class UDPComm
{
public:
    static int Setup();
    static int Send(vector<unsigned char> buffer);
    static vector<unsigned char> Receive();
    static void Close();

    static bool server_select;
    static char ip[];
};

#endif // UDPCOMM_H
