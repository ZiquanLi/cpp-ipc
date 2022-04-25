#ifndef LIB_SENDER_WITH_MSGQ_H_
#define LIB_SENDER_WITH_MSGQ_H_
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
#include <errno.h>
#include <vector>
#include <cstring>
#include <mqueue.h>

class SenderWithMsgq
{
private:
    std::string mqName;
    mqd_t mqd;
    size_t BUF_SIZE = 80;

public:
    SenderWithMsgq(std::string mqName = "/mqExample");
    ~SenderWithMsgq();
    void sendFile(std::string filePath);

};

#endif
