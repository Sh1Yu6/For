
/************************************************
#
#      Filename: tcpServerClass.h
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 21:52:50
# Last Modified: 2021-03-07 21:52:50
#***********************************************/
#ifndef __TCPSERVERCLASS_H__
#define __TCPSERVERCLASS_H__

#include <netinet/in.h>
namespace Sh1Yu6{

class Server{
    public:
        Server();
        ~Server();

        void run();
        void setSig(int sig);

    private:
        int sockFd;
        struct sockaddr_in serverAddr;

        void init();
        void daemonize();

};

} // namespace Sh1Yu6
#endif // __TCPSERVERCLASS_H__
