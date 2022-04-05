#include "receiverWithPipe.h"
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

ReceiverWithPipe::ReceiverWithPipe(std::string /*fifoPath="/tmp/myfifo"*/)
{
    this->fifoPath = fifoPath;
    mkfifo(fifoPath.c_str(), 0666);
}

ReceiverWithPipe::~ReceiverWithPipe()
{
}

void ReceiverWithPipe::receiveFile(std::string filePath)
{
    std::ifstream in(fifoPath, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(filePath, std::ios_base::out | std::ios_base::binary);
    char buf[BUF_SIZE];

    int length = 0;
    int receivedLength = 0;
    while (length == 0)
    {
        in.read(&buf[0], BUF_SIZE);
        length = atoi(buf);
        std::cout << "length" << length << std::endl;
    }

    do
    {
        in.read(&buf[0], BUF_SIZE);
        std::cout << "in.gcount()" << in.gcount() << std::endl;
        out.write(&buf[0], in.gcount());
        receivedLength += in.gcount();
        std::cout << "length" << length << std::endl;
        std::cout << "receivedLength" << receivedLength << std::endl;
    } while (receivedLength < length);

    in.close();
    out.close();
}