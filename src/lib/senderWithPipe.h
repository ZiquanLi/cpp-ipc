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
class SenderWithPipe
{
private:
    std::string fifoPath;
    size_t BUF_SIZE = 80;

public:
    SenderWithPipe(std::string fifoPath = "/tmp/myfifo");
    ~SenderWithPipe();
    void sendFile(std::string filePath);
};

#endif
