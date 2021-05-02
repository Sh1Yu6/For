
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-23 14:41:20
# Last Modified: 2021-04-23 15:11:54
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
    mxml_node_t* root = mxmlNewXML("1.0");

    mxml_node_t* china = mxmlNewElement(root, "china");

    mxml_node_t* city = mxmlNewElement(china, "city");
    auto name = mxmlNewElement(city, "name");
    mxmlNewText(name, 0, "beijing");
    auto area = mxmlNewElement(city, "area");
    mxmlNewText(area, 0, "123123");
    auto population = mxmlNewElement(city, "population");
    mxmlNewText(population, 0, "124124124");

    city = mxmlNewElement(china, "city");
    name = mxmlNewElement(city, "name");
    mxmlNewText(name, 0, "nanjing");
    area = mxmlNewElement(city, "area");
    mxmlNewText(area, 0, "5231212513123");
    population = mxmlNewElement(city, "population");
    mxmlNewText(population, 0, "134524124124");

    int fd = open("xml.xml", O_RDWR | O_CREAT, 0666);
    if( fd < 0  ){
        perror("open error");
    }
    mxmlSaveFd(root, fd, MXML_NO_CALLBACK);

    mxmlDelete(root);
    close(fd);
    return 0;
}

