#include "senderWithPipe.h"
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

SenderWithPipe::SenderWithPipe(std::string /*fifoPath="/tmp/myfifo"*/)
{
    this->fifoPath = fifoPath;
    mkfifo(fifoPath.c_str(), 0666);
}

SenderWithPipe::~SenderWithPipe()
{
}
void SenderWithPipe::sendFile(std::string filePath)
{
    // Use binary mode so we can handle all kinds of file content.
    std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(fifoPath, std::ios_base::out | std::ios_base::binary);
    char buf[BUF_SIZE];

    // get length of file:
    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);

    std::cout << length << std::endl;
    sprintf(buf, "%d", length);
    out.write(buf, BUF_SIZE);

    do
    {
        in.read(&buf[0], BUF_SIZE);      // Read at most n bytes into
        out.write(&buf[0], in.gcount()); // buf, then write the buf to
        std::cout << in.gcount() << std::endl;

    } while (in.gcount() > 0); // the output.

    in.close();
    out.close();
}

std::string SenderWithPipe::getFifoPath()
{
    return fifoPath;
}