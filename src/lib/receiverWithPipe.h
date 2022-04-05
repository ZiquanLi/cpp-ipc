#include <string>
#ifndef LIB_RECEIVER_WITH_PIPE_H_
#define LIB_RECEIVER_WITH_PIPE_H_

class ReceiverWithPipe
{
private:
    std::string fifoPath;
    int BUF_SIZE = 80;

public:
    ReceiverWithPipe(std::string fifoPath = "/tmp/myfifo");
    ~ReceiverWithPipe();
    void receiveFile(std::string filePath);
};

#endif