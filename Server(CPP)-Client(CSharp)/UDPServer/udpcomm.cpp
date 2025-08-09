#include "udpcomm.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

bool UDPComm::server_select = false;
char UDPComm::ip[] = "192.168.1.2";

struct sockaddr_in server_addr, client_addr;
int sock_fd;

int UDPComm::Setup()
{
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed.");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    if (UDPComm::server_select)
        memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    if (UDPComm::server_select)
        server_addr.sin_addr.s_addr = INADDR_ANY;
    else
        server_addr.sin_addr.s_addr = inet_addr((const char *)UDPComm::ip);
    server_addr.sin_port = htons(PORT);

    if (UDPComm::server_select) {
        if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Socket bind failed.");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

int UDPComm::Send(vector<unsigned char> buf)
{
    char buffer[buf.size()];
    for (int i = 0; i < buf.size(); i++)
        buffer[i] = buf.at(i);

    if (UDPComm::server_select) {
        sendto(sock_fd, (const unsigned char *)buffer, strlen(buffer), MSG_CONFIRM,
               (const struct sockaddr *) &client_addr, sizeof(client_addr));
    } else {
        sendto(sock_fd, (const unsigned char *)buffer, strlen(buffer), MSG_CONFIRM,
               (const struct sockaddr *) &server_addr, sizeof(server_addr));
    }

    return 0;
}

vector<unsigned char> UDPComm::Receive()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    setsockopt(sock_fd, SOL_SOCKET,SO_RCVTIMEO, (const char *)&tv, sizeof(timeval));

    unsigned char buffer[MAX_LINE];
    int n = 0;
    if (UDPComm::server_select) {
        socklen_t len = sizeof(client_addr);
        n = recvfrom(sock_fd, (char *)buffer, MAX_LINE, MSG_WAITALL,
                     (struct sockaddr *)&client_addr, &len);
    } else {
        socklen_t len = sizeof(server_addr);
        n = recvfrom(sock_fd, (char *)buffer, MAX_LINE, MSG_WAITALL,
                     (struct sockaddr *)&server_addr, &len);
    }

    vector<unsigned char> recv;
    for (int i = 0; i < n; i++)
        recv.push_back(buffer[i]);

    return recv;
}

void UDPComm::Close()
{
    close(sock_fd);
}
