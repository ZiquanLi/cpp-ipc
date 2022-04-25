#include "senderWithMsgq.h"

SenderWithMsgq::SenderWithMsgq(std::string mqName/*mqName="/mqExample"*/)
{
    this->mqName = mqName;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;//Not sure about the requirement of mq_maxmsg
    attr.mq_msgsize = 80;
    attr.mq_curmsgs = 0;
    this->mqd = mq_open(mqName.c_str(), O_WRONLY| O_CREAT, 0666, &attr);
    if(mqd==-1){
        throw std::runtime_error("mq_open():"+std::string(strerror(errno)));
    }
}

SenderWithMsgq::~SenderWithMsgq()
{
    mq_close(mqd);
    mq_unlink(mqName.c_str());
}
void SenderWithMsgq::sendFile(std::string filePath)
{
    // Use binary mode so we can handle all kinds of file content.
    std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
    std::vector<char> buf(BUF_SIZE);

    do
    {
        in.read(buf.data(), BUF_SIZE);      
        if(mq_send(mqd,buf.data(),in.gcount(),0) != 0){
            throw std::runtime_error("mq_send():"+std::string(strerror(errno)));
        }
        std::cout <<"Send:"<< in.gcount() << std::endl;
    } while (in.gcount() > 0); 
    in.close();
}

