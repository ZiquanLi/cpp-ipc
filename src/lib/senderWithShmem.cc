#include "senderWithShmem.h"

SenderWithShmem::SenderWithShmem(std::string shmPath,std::string semProdName ,std::string semConsName )
{
    this->shmPath = shmPath;
    this->semProdName = semProdName;
    this->semConsName = semConsName;
    this->shmfd = shm_open(shmPath.c_str(), O_RDWR | O_CREAT, 0666);
    if(shmfd==-1){
        throw std::runtime_error("shm_open():"+std::string(strerror(errno)));
    }
    if(ftruncate(shmfd, BUF_SIZE+sizeof(Shmem_control))!=0){
        throw std::runtime_error("ftruncate():"+std::string(strerror(errno)));
    }
    
    this->memptr = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if(memptr==(void*)-1){
        throw std::runtime_error("mmap():"+std::string(strerror(errno)));
    }

    shm_ctrl = reinterpret_cast<Shmem_control *>(static_cast<char*>(memptr) + BUF_SIZE);

    sem_unlink(semProdName.data());
    sem_unlink(semConsName.data());

    semHandleProd = sem_open(semProdName.data(), O_RDWR | O_CREAT, 0666, 0);
    if(semHandleProd == SEM_FAILED)
    {
        throw std::runtime_error("sem_open() for producer:"+std::string(strerror(errno)));
    }

    semHandleCons = sem_open(semConsName.data(), O_RDWR | O_CREAT, 0666, 1);
    if(semHandleCons == SEM_FAILED)
    {
        throw std::runtime_error("sem_open() for consumer:"+std::string(strerror(errno)));
    }
}

SenderWithShmem::~SenderWithShmem()
{
    munmap(memptr, BUF_SIZE);
    close(shmfd);
    sem_close(semHandleCons);
    sem_close(semHandleProd);
    sem_unlink(semProdName.data());
    sem_unlink(semConsName.data());
    shm_unlink(shmPath.data());
}

void SenderWithShmem::sendFile(std::string filePath)
{
    std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
    std::vector<char> buf(BUF_SIZE);

    do
    {
        sem_wait(semHandleCons);
        in.read(buf.data(), buf.size());
        memcpy(memptr,buf.data(),in.gcount());
        shm_ctrl->bytes_send = in.gcount();
        sem_post(semHandleProd);
        std::cout <<"Send:"<< in.gcount() << std::endl;
    } while (in.gcount() > 0); 

    in.close();
}