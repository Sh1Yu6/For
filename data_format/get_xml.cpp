
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-23 14:41:20
# Last Modified: 2021-04-23 15:38:16
#***********************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mxml.h>
using namespace std;

int main(int argc, char *argv[])
{

    int fd = open("xml.xml", O_RDONLY);
    if( fd < 0  ){
        perror("open error");
    }
    auto root = mxmlLoadFd(nullptr, fd, MXML_NO_CALLBACK);

    auto node = mxmlFindElement(root, root, "city", nullptr, nullptr, MXML_DESCEND);

    while(node){
        node = mxmlWalkNext(node, root, MXML_DESCEND);
        node = mxmlWalkNext(node, root, MXML_DESCEND);
        node = mxmlWalkNext(node, root, MXML_DESCEND);
    }

    mxmlDelete(root);
    close(fd);
    return 0;
}

