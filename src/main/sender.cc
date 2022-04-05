#include "../lib/senderWithPipe.h"
#include "../lib/senderWithMq.h"
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <cstdio>
#include <cstring>

enum ipcTypes
{
    Pipe,
    Queue,
    SharedMemory,
    OtherSituation
};
int dealWithArg(int argc, char **argv, std::string &return_fileName, ipcTypes &return_method);

int main(int argc, char **argv)
{
    std::string fileName;
    ipcTypes method;
    int resultOfDealWithArg = dealWithArg(argc, argv, fileName, method);
    if (resultOfDealWithArg == -1)
    {
        std::cout << "dealWithArg error" << std::endl;
        return -1;
    }
    switch (method)
    {
    case Pipe:
    {
        SenderWithPipe sender;
        sender.sendFile(fileName);
        break;
    }
    case SharedMemory:
    {
        std::cout << "SharedMemory has not been implemented yet" << std::endl;
        break;
    }
    case Queue:
    {
//        SenderWithMq sender;
//        sender.sendFile(fileName);
        break;
    }
    case OtherSituation:
        break;
    default:
        return -1;
    }

    return 0;
}

int dealWithArg(int argc, char **argv, std::string &return_fileName, ipcTypes &return_method)
{
    int longindex;
    int ch;
    int fd = -1;
    static struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"queue", no_argument, NULL, 'q'},
        {"pipe", no_argument, NULL, 'p'},
        {"shm", no_argument, NULL, 's'},
        {"file", required_argument, NULL, 'f'},
        {NULL, 0, NULL, 0}};

    while ((ch = getopt_long(argc, argv, "hmqpsf:", longopts, &longindex)) != -1)
    {
        switch (ch)
        {
        case 'f':
            if ((fd = open(optarg, O_RDONLY)) == -1)
            {
                std::cout << "Unable to open the file" << optarg << std::endl;
                return -1;
            }
            return_fileName = optarg;
            break;
        case 'p':
            return_method = Pipe;
            break;
        case 's':
            return_method = SharedMemory;
            break;
        case 'q':
            return_method = Queue;
            break;
        case 'h':
            std::cout << "Usage: my_program [-m] for file transfer by message passing" << std::endl;
            std::cout << "                  [-p] for file transfer by named pipe" << std::endl;
            std::cout << "                  [-s] for file transfer by shared memory" << std::endl;
            std::cout << "                  [-f file_path] for choosing the target file" << std::endl;
            std::cout << "                  [-h] for this help command" << std::endl;
            return_method = OtherSituation;
            return 0;
        default:
            // fail
            return -1;
        }
    }
    if (fd == -1)
    {
        std::cout << "the file to send has not been provided or error happens!" << std::endl;
        return -1;
    }
    close(fd);
    return 0;
}