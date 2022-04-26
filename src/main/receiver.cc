#include "src/lib/receiverWithPipe.h"
#include "src/lib/receiverWithMsgq.h"
#include "src/lib/receiverWithShmem.h"
#include "src/lib/argsParser.h"

int main(int argc, char **argv)
{
    try{
        ArgsParser argsParser(argc,argv);
        std::string fileName = argsParser.getFileName();
        ipcType method = argsParser.getMethod();
        std::cout << "File Used To Receive:" << fileName << std::endl;
        switch (method)
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
