#include <string>
#ifndef LIB_SENDER_WITH_PIPE_H_
#define LIB_SENDER_WITH_PIPE_H_

class SenderWithPipe
{
private:
    std::string fifoPath;
    int BUF_SIZE = 80;

public:
    SenderWithPipe(std::string fifoPath = "/tmp/myfifo");
    ~SenderWithPipe();
    void sendFile(std::string filePath);
    std::string getFifoPath();
};

#endif
