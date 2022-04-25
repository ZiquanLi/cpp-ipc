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
class ReceiverWithPipe
{
private:
    std::string fifoPath;
    size_t BUF_SIZE = 80;

public:
    ReceiverWithPipe(std::string fifoPath = "/tmp/myfifo");
    ~ReceiverWithPipe();
    void receiveFile(std::string filePath);
};

#endif