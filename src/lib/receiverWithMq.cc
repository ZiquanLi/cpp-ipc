#include "receiverWithMq.h"
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
#include <string.h>
ReceiverWithMq::ReceiverWithMq(std::string /*fifoPath="/tmp/myfifo"*/)
{
    this->mqName = mqName;
    this->mqd = mq_open(mqName.c_str(), O_RDONLY | O_CREAT);
}

ReceiverWithMq::~ReceiverWithMq()
{
}

void ReceiverWithMq::receiveFile(std::string filePath)
{
    //std::ifstream in(fifoPath, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(filePath, std::ios_base::out | std::ios_base::binary);
    char buf[BUF_SIZE];

    int length = 0;
    int receivedLength = 0;
    while (length == 0)
    {
    //    in.read(&buf[0], BUF_SIZE);
        mq_receive(mqd,buf,BUF_SIZE,NULL);
        length = atoi(buf);
        std::cout << "length" << length << std::endl;
    }

    do
    {
        //in.read(&buf[0], BUF_SIZE);
        mq_receive(mqd,buf,BUF_SIZE,NULL);
        //std::cout << "in.gcount()" << in.gcount() << std::endl;
        out.write(&buf[0], strlen(buf));
        receivedLength += strlen(buf);
        //std::cout << "length" << length << std::endl;
        std::cout << "receivedLength" << receivedLength << std::endl;
    } while (receivedLength < length);

    //in.close();
    out.close();
}
