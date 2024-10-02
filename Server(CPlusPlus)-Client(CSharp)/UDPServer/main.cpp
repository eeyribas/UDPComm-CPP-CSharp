#include <QCoreApplication>
#include <vector>
#include <unistd.h>
#include "udpcomm.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UDPComm::server_select = true; // client = 0
    UDPComm::Setup();
    printf("UDP initialized.\n");

    vector<unsigned char> send_data;
    send_data.push_back(1);
    int send_data_state = UDPComm::Send(send_data);
    printf("UDP Send Data State = %d\n", send_data_state);

    for (;;) {
        vector<unsigned char> receive_data = UDPComm::Receive();

        if (receive_data.size() > 0) {
            printf("UDP Receive Data = ");
            for (int i = 0; i < receive_data.size(); i++)
                printf("%u ", receive_data.at(i));
            printf("\n");

            receive_data.clear();
        }
        usleep(1000);
    }

    UDPComm::Close();

    return a.exec();
}
