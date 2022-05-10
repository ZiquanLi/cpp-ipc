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
#include <gtest/gtest_prod.h>
class SenderWithMsgq
{
private:
    //with a trailing underscore means private
    std::string mqName_;
    mqd_t mqd_;
    size_t bufSize_ = 80;

    FRIEND_TEST(TestMsgqSender, CheckMqd);
public:
    SenderWithMsgq(const std::string &mqName = "/mqExample");
    ~SenderWithMsgq();
    void sendFile(std::string filePath);

};

#endif
