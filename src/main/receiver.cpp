#include "src/lib/receiverWithPipe.hpp"
#include "src/lib/receiverWithMsgq.hpp"
#include "src/lib/receiverWithShmem.hpp"
#include "src/lib/argsParser.hpp"

int main(int argc, char **argv)
{
    try{
        ArgsParser argsParser(argc,argv);
        std::string fileName = argsParser.getFileName();
        //ipcType method = argsParser.getMethod();
        std::cout << "File Used To Receive:" << fileName << std::endl;
        switch (argsParser.getMethod())
        {
        case ipcType::Pipe:
        {
            std::cout << "Pipe Is Used:" << std::endl;
            ReceiverWithPipe receiver;
            receiver.receiveFile(fileName);
            break;
        }
        case ipcType::SharedMemory:
        {
            std::cout << "Shared Memory Is Used:" << std::endl;
            ReceiverWithShmem receiver;
            receiver.receiveFile(fileName);
            break;
        }
        case ipcType::Queue:
        {
            std::cout << "Message Queue Is Used:" << std::endl;
            ReceiverWithMsgq receiver;
            receiver.receiveFile(fileName);
            break;
        }
        case ipcType::OtherSituation:
            return -1;
        default:
            return -1;
        }
    }
    catch(const std::exception &e){
        std::rethrow_exception(std::current_exception());
    }
    return 0;
}
