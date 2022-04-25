#include "receiverWithShmem.h"

ReceiverWithShmem::ReceiverWithShmem(std::string shmPath, std::string semProdName, std::string semConsName)
{
    this->shmPath = shmPath;
    this->semProdName = semProdName;
    this->semConsName = semConsName;
    this->shmfd = shm_open(shmPath.c_str(), O_RDWR | O_CREAT, 0666);
    if (shmfd == -1)
    {
        throw std::runtime_error("shm_open():" + std::string(strerror(errno)));
    }
    this->memptr = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (memptr == (void *)-1)
    {
        throw std::runtime_error("mmap():" + std::string(strerror(errno)));
    }
    shm_ctrl = reinterpret_cast<Shmem_control *>(static_cast<char *>(memptr) + BUF_SIZE);
    semHandleProd = sem_open(semProdName.data(), O_RDWR);
    // try solving the problem of running receiver earlier that sender here
    while (semHandleProd == SEM_FAILED)
    {
        //    throw std::runtime_error("sem_open() for producer:"+std::string(strerror(errno)));
        std::cout << "Waiting for the sender to run..." << std::endl;
        std::cout << "If you have run the sender, sem_open() for producer fails" << std::endl;
        sleep(2);
        semHandleProd = sem_open(semProdName.data(), O_RDWR);
    }

    semHandleCons = sem_open(semConsName.data(), O_RDWR);
    if (semHandleCons == SEM_FAILED)
    {
        throw std::runtime_error("sem_open() for consumer:" + std::string(strerror(errno)));
    }
}

ReceiverWithShmem::~ReceiverWithShmem()
{
    munmap(memptr, BUF_SIZE);
    close(shmfd);
    sem_close(semHandleCons);
    sem_close(semHandleProd);
    shm_unlink(shmPath.data());
}

void ReceiverWithShmem::receiveFile(std::string filePath)
{
    // Use binary mode so we can handle all kinds of file content.
    std::ofstream out(filePath, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buf(BUF_SIZE);
    size_t receive_size = 0;
    do
    {
        sem_wait(semHandleProd);
        receive_size = shm_ctrl->bytes_send;
        memcpy(buf.data(), memptr, receive_size);
        out.write(buf.data(), receive_size);
        sem_post(semHandleCons);
        std::cout << "Receive:" << receive_size << std::endl;
    } while (receive_size > 0);

    out.close();
}
