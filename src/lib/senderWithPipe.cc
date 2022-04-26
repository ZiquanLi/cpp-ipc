#include "senderWithPipe.h"

SenderWithPipe::SenderWithPipe(const std::string &fifoPath/*fifoPath="/tmp/myfifo"*/)
:fifoPath_(fifoPath)
{
    //not sure this is the best way to deal with the EEXIST
    if(mkfifo(fifoPath_.c_str(), 0666)!=0&& errno!=EEXIST){
        throw std::runtime_error("mkfifo():"+std::string(strerror(errno)));
    }
}

SenderWithPipe::~SenderWithPipe()
{
}

void SenderWithPipe::sendFile(std::string filePath)
{
    // Use binary mode so we can handle all kinds of file content.
    std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(fifoPath_, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buf(bufSize_);

    do
    {
        in.read(buf.data(), buf.size());      
        out.write(buf.data(), in.gcount()); 
        //std::cout <<"Send:"<< in.gcount() << std::endl;
    } while (in.gcount() > 0); 

    in.close();
    out.close();
}