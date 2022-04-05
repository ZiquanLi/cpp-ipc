#include <string>
#include <mqueue.h>
#ifndef LIB_RECEIVER_WITH_MQ_H_
#define LIB_RECEIVER_WITH_MQ_H_

class ReceiverWithMq
{
private:
    std::string mqName;
    mqd_t mqd;
    int BUF_SIZE = 80;

public:
    ReceiverWithMq(std::string mqName = "/tmp/mq");
    ~ReceiverWithMq();
    void receiveFile(std::string filePath);
};

#endif