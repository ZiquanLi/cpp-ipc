#include "receiverWithMsgq.h"

ReceiverWithMsgq::ReceiverWithMsgq(std::string mqName/*mqName="/mqExample"*/)
{
    this->mqName = mqName;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;//Not sure about the requirement of mq_maxmsg
    attr.mq_msgsize = 80;
    attr.mq_curmsgs = 0;
    this->mqd = mq_open(mqName.c_str(), O_RDONLY | O_CREAT, 0666, &attr);
    if(mqd==-1){
        throw std::runtime_error("mq_open():"+std::string(strerror(errno)));
    }
}

ReceiverWithMsgq::~ReceiverWithMsgq()
{
    mq_close(mqd);
    mq_unlink(mqName.c_str());
}

void ReceiverWithMsgq::receiveFile(std::string filePath)
{
    std::ofstream out(filePath, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buf(BUF_SIZE);
    int received_size = 0;
    do
    {
        received_size = mq_receive(mqd,buf.data(),BUF_SIZE,NULL);    
        if(received_size==-1){
            throw std::runtime_error("mq_receive():"+std::string(strerror(errno)));
        }
        out.write(buf.data(), received_size);
        std::cout << "Receive:" << received_size << std::endl;
    } while (received_size > 0);

    out.close();
    
}
