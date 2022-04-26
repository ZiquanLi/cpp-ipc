#include "src/lib/senderWithPipe.h"
#include "src/lib/senderWithMsgq.h"
#include "src/lib/senderWithShmem.h"
#include "src/lib/argsParser.h"
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



int main(int argc, char **argv)
{
    try{
        ArgsParser argsParser(argc,argv);
        std::string fileName = argsParser.getFileName();
        ipcType method = argsParser.getMethod();
        std::cout << "Send File:" << fileName << std::endl;
        switch (method)
        {
        case ipcType::Pipe:
        {
            std::cout << "Pipe Is Used:" << std::endl;
            SenderWithPipe sender;
            sender.sendFile(fileName);
            break;
        }
        case ipcType::SharedMemory:
        {
            std::cout << "Shared Memory Is Used:" << std::endl;
            SenderWithShmem sender;
            sender.sendFile(fileName);
            break;
        }
        case ipcType::Queue:
        {
            std::cout << "Message Queue Is Used:" << std::endl;
            SenderWithMsgq sender;
            sender.sendFile(fileName);
            break;
        }
        case ipcType::OtherSituation:
            return -1;
        default:
            return -1;
        }
    }
    catch(const std::exception &e){
        std::rethrow_exception(std::current_exception());
    }
    return 0;
}