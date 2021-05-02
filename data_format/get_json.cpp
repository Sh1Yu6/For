
/************************************************
#
#      Filename: create_json.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-23 19:03:24
# Last Modified: 2021-04-23 19:53:36
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <cjson/cJSON.h>
using namespace std;

int main(int argc, char *argv[])
{
    int fd = open("json.json", O_RDWR | O_CREAT | O_APPEND, 0666);
    char buf[1024];
    read( fd, buf, 1024 );
    cJSON* root = cJSON_Parse(buf);

    cJSON* subobj = cJSON_GetObjectItem(root, "奔驰");
    cout << cJSON_Print(subobj) << endl;
    return 0;
}

