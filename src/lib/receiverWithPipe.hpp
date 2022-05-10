#ifndef LIB_RECEIVER_WITH_PIPE_H_
#define LIB_RECEIVER_WITH_PIPE_H_
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
#include <vector>
#include <errno.h>
#include <string.h>
#include <gtest/gtest_prod.h>
class ReceiverWithPipe
{
private:
    //with a trailing underscore means private
    std::string fifoPath_;
    size_t bufSize_ = 80;

    FRIEND_TEST(TestPipeReceiver, PrivateMemberVariableWithDefaultValue);
public:
    ReceiverWithPipe(const std::string &fifoPath = "/tmp/myfifo");
    ~ReceiverWithPipe();
    void receiveFile(std::string filePath);

};

#endif