#ifndef LIB_ARGS_PARSER_H_
#define LIB_ARGS_PARSER_H_
#include <iostream>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
enum class ipcType
{
    Pipe,
    Queue,
    SharedMemory,
    OtherSituation
};

class ArgsParser
{
private:
    std::string fileName;
    ipcType method;
    static struct option longopts[];
public:
    ArgsParser(int argc, char **argv){
        int longindex;
        int ch;
        int fd = -1;
        while ((ch = getopt_long(argc, argv, "hmqpsf:", longopts, &longindex)) != -1)
        {
            switch (ch)
            {
            case 'f':
                if ((fd = open(optarg, O_WRONLY | O_CREAT, 0666)) == -1)
                    throw std::runtime_error("argsParser:Unable to open the file");   
                fileName = optarg;
                break;
            case 'p':
                method = ipcType::Pipe;
                break;
            case 's':
                method = ipcType::SharedMemory;
                break;
            case 'q':
                method = ipcType::Queue;
                break;
            case 'h':
                std::cout << "Usage: my_program [-p] for file transfer by named pipe" << std::endl;
                std::cout << "                  [-q] for file transfer by message queue" << std::endl;
                std::cout << "                  [-s] for file transfer by shared memory" << std::endl;
                std::cout << "                  [-f file_path] for choosing the target file" << std::endl;
                std::cout << "                  [-h] for this help command" << std::endl;
                std::cout << "                  note: Please be careful about the file permissions" << std::endl;
                method = ipcType::OtherSituation;
                break;
            default:
                // fail
                throw std::runtime_error("argsParser:args from command line  error");
            }
        }
        if (fd == -1)
            throw std::runtime_error("argsParser:the file name has not been provided or error happens!");
        close(fd);
    }
    ~ArgsParser(){}
    std::string getFileName(){
        return fileName;
    };
    ipcType getMethod(){
        return method;
    };
};

struct option ArgsParser::longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"queue", no_argument, NULL, 'q'},
    {"pipe", no_argument, NULL, 'p'},
    {"shm", no_argument, NULL, 's'},
    {"file", required_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}
};

#endif