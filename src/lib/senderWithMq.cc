#include "senderWithMq.h"
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
//#include <mqueue.h>

SenderWithMq::SenderWithMq(std::string /*mqName="/tmp/mq"*/)
{
    this->mqName = mqName;
    this->mqd = mq_open(mqName.c_str(), O_WRONLY);
}

SenderWithMq::~SenderWithMq()
{
}
void SenderWithMq::sendFile(std::string filePath)
{
    // Use binary mode so we can handle all kinds of file content.
    std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
    //std::ofstream out(fifoPath, std::ios_base::out | std::ios_base::binary);
    char buf[BUF_SIZE];

    // get length of file:
    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);

    std::cout << length << std::endl;
    sprintf(buf, "%d", length);
    //out.write(buf, BUF_SIZE);
    mq_send(mqd,buf,BUF_SIZE,0);
    do
    {
        in.read(&buf[0], BUF_SIZE);      // Read at most n bytes into
        //out.write(&buf[0], in.gcount()); // buf, then write the buf to
        mq_send(mqd,&buf[0],in.gcount(),0);
        std::cout << in.gcount() << std::endl;
    } while (in.gcount() > 0); // the output.

    in.close();
    //out.close();
}

std::string SenderWithMq::getMqName()
{
    return mqName;
}