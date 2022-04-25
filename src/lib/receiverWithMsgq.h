
#ifndef LIB_RECEIVER_WITH_MSGQ_H_
#define LIB_RECEIVER_WITH_MSGQ_H_
#include <string>
#include <mqueue.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <cstdio>
#include <string.h>
#include <errno.h>
#include <vector>
#include <cstring>
class ReceiverWithMsgq
{
private:
    std::string mqName;
    mqd_t mqd;
    size_t BUF_SIZE = 80;

public:
    ReceiverWithMsgq(std::string mqName = "/mqExample");
    ~ReceiverWithMsgq();
    void receiveFile(std::string filePath);
};

#endif