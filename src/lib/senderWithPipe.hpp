#ifndef LIB_SENDER_WITH_PIPE_H_
#define LIB_SENDER_WITH_PIPE_H_
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
class SenderWithPipe
{
private:
    //with a trailing underscore means private
    std::string fifoPath_;
    size_t bufSize_ = 80;

    FRIEND_TEST(TestPipeSender, Constructor);
public:
    SenderWithPipe(const std::string &fifoPath = "/tmp/myfifo");
    ~SenderWithPipe();
    void sendFile(std::string filePath);

};

#endif
