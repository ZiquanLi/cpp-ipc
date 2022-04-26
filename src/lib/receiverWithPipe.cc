#include "receiverWithPipe.h"

ReceiverWithPipe::ReceiverWithPipe(const std::string &fifoPath/*fifoPath="/tmp/myfifo"*/)
:fifoPath_(fifoPath)
{
    //not sure this is the best way to deal with the EEXIST
    if(mkfifo(fifoPath_.c_str(), 0666)!=0 && errno!=EEXIST){
        throw std::runtime_error("mkfifo():"+std::string(strerror(errno)));
    }
}

ReceiverWithPipe::~ReceiverWithPipe()
{
}

void ReceiverWithPipe::receiveFile(std::string filePath)
{
    std::ifstream in(fifoPath_, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(filePath, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buf(bufSize_);

    do
    {
        in.read(buf.data(), buf.size());
        out.write(buf.data(), in.gcount());
        //std::cout << "Receive:" << in.gcount() << std::endl;
    } while (in.gcount()>0);

    in.close();
    out.close();
}