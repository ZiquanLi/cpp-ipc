#ifndef LIB_RECEIVER_WITH_SHMEM_H_
#define LIB_RECEIVER_WITH_SHMEM_H_
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <cstdio>
#include <semaphore.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <vector>
#include <cstring>
class ReceiverWithShmem
{
private:
    //do not want to change these names into ones with a trailing underscore, I am lazy
    std::string shmPath;
    std::string semProdName;
    std::string semConsName;
    int shmfd;
    void * memptr = nullptr;
    sem_t *semHandleProd = nullptr;
    sem_t *semHandleCons = nullptr;
    size_t BUF_SIZE = 80;
    struct Shmem_control
    {
        size_t bytes_send;
    };
    Shmem_control *shm_ctrl = nullptr;

public:
    ReceiverWithShmem(const std::string &shmPath = "/shmExample",const std::string &semProdName = "semProd",const std::string &semConsName = "semCons");
    ~ReceiverWithShmem();
    void receiveFile(std::string filePath);
};

#endif