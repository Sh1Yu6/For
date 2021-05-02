
/************************************************
#
#      Filename: create_json.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-23 19:03:24
# Last Modified: 2021-04-23 19:39:36
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

    cJSON* obj = cJSON_CreateObject();
    cJSON* subObj = cJSON_CreateObject();

    cJSON_AddItemToObject(subObj, "factory", 
                        cJSON_CreateString("一汽大众"));
    cJSON_AddItemToObject(subObj, "last", cJSON_CreateNumber(31));
    cJSON_AddItemToObject(subObj, "price", cJSON_CreateNumber(3891));
    cJSON_AddItemToObject(subObj, "sell", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(subObj, "sum", cJSON_CreateNumber(2));

    cJSON* array = cJSON_CreateArray();

    cJSON_AddItemToArray(array, cJSON_CreateNumber(123));
    cJSON_AddItemToArray(array, cJSON_CreateNumber(1));
    cJSON_AddItemToArray(array, cJSON_CreateString("hello, world!"));

    cJSON* subsubObj = cJSON_CreateObject();
    cJSON_AddItemToObject(subsubObj, "梅赛德斯奔驰", 
            cJSON_CreateString("xin suo xiang, chi yi heng"));

    cJSON_AddItemToArray(array, subsubObj);

    cJSON_AddItemToObject(subObj, "other", array);

    cJSON_AddItemToObject(obj, "奔驰", subObj);
    

    char* data = cJSON_Print(obj);

    int fd = open("json.json", O_RDWR | O_CREAT | O_APPEND, 0666);
    write( fd, data, strlen(data) + 1);
    close(fd);
    cout << data << endl;
    return 0;
}

