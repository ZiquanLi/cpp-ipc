#include "src/lib/receiverWithPipe.h"
#include "src/lib/receiverWithMsgq.h"
#include "src/lib/receiverWithShmem.h"
#include "src/lib/argsParser.h"

int main(int argc, char **argv)
{
    ArgsParser argsParser(argc,argv);
    std::string fileName = argsParser.getFileName();
    ipcType method = argsParser.getMethod();
    std::cout << "File Used To Receive:" << fileName << std::endl;
    switch (method)
    {
    case Pipe:
    {
        std::cout << "Pipe Is Used:" << std::endl;
        ReceiverWithPipe receiver;
        receiver.receiveFile(fileName);
        break;
    }
    case SharedMemory:
    {
        std::cout << "Shared Memory Is Used:" << std::endl;
        ReceiverWithShmem receiver;
        receiver.receiveFile(fileName);
        break;
    }
    case Queue:
    {
        std::cout << "Message Queue Is Used:" << std::endl;
        ReceiverWithMsgq receiver;
        receiver.receiveFile(fileName);
        break;
    }
    case OtherSituation:
        return -1;
    default:
        return -1;
    }

    return 0;
}
