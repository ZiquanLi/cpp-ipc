
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
#include <gtest/gtest_prod.h>
class ReceiverWithMsgq
{
private:
    //with a trailing underscore means private
    std::string mqName_;
    mqd_t mqd_;
    size_t bufSize_ = 80;

public:
    ReceiverWithMsgq(const std::string &mqName = "/mqExample");
    ~ReceiverWithMsgq();
    void receiveFile(std::string filePath);
};

#endif