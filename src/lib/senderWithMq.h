#include <string>
#include <mqueue.h>
#ifndef LIB_SENDER_WITH_MQ_H_
#define LIB_SENDER_WITH_MQ_H_

class SenderWithMq
{
private:
    std::string mqName;
    mqd_t mqd;
    int BUF_SIZE = 80;

public:
    SenderWithMq(std::string mqName = "/tmp/mq");
    ~SenderWithMq();
    void sendFile(std::string filePath);
    std::string getMqName();
};

#endif
