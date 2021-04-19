
/************************************************
#
#      Filename: raii.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 08:49:35
# Last Modified: 2021-04-15 08:55:41
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

class FileManagement{
    public:
        FileManagement(int fd): mFd{ fd }{

        }
        ~FileManagement(){
            close(mFd);
        }

        FileManagement(const FileManagement& rhs) = delete;
        FileManagement& operator=(const FileManagement& rhs) = delete;

        FileManagement(FileManagement&& rhs) = default;
        FileManagement& operator=(FileManagement&& rhs) = default;

    private:
        int mFd;
};
int main(int argc, char *argv[])
{
    return 0;
}

