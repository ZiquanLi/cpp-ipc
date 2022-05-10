#include <gtest/gtest.h>
#include "../src/lib/senderWithPipe.hpp"
#include "../src/lib/senderWithMsgq.hpp"
#include "../src/lib/senderWithShmem.hpp"
#include "../src/lib/receiverWithPipe.hpp"
#include "../src/lib/receiverWithMsgq.hpp"
#include "../src/lib/receiverWithShmem.hpp"
#include <string>
#include <thread>

//learn testing

void createFile(std::string fileName, std::string fileSize){
    std::system(("truncate -s "+fileSize+" "+fileName).c_str());
}
void deleteFile(std::string fileName){
    std::system(("rm "+fileName).c_str());
}

bool compareFile(std::string file1,std::string file2){
    int rv = std::system(("diff "+file1+" "+file2).c_str());
    return WEXITSTATUS(rv) == 0;
}

TEST(TestIPC, Pipe)
{
    std::string sendFileName = "test1k.txt";
    std::string sendFileSize = "1k";
    std::string receiveFileName = "hello";
    createFile(sendFileName,sendFileSize);
    SenderWithPipe sender;
    ReceiverWithPipe receiver;

    auto senderSendFile = [&](){
        sender.sendFile(sendFileName);
    };

    auto receiverReceiveFile = [&](){
        receiver.receiveFile(receiveFileName);
    };

    std::thread s_thread(senderSendFile);
    std::thread r_thread(receiverReceiveFile);
    s_thread.join();
    r_thread.join();
    EXPECT_TRUE(compareFile(sendFileName, receiveFileName));
    deleteFile(sendFileName);
    deleteFile(receiveFileName);
}

TEST(TestIPC, Msgq)
{
    std::string sendFileName = "test1k.txt";
    std::string sendFileSize = "1k";
    std::string receiveFileName = "hello";
    createFile(sendFileName,sendFileSize);
    SenderWithMsgq sender;
    ReceiverWithMsgq receiver;

    auto senderSendFile = [&](){
        sender.sendFile(sendFileName);
    };

    auto receiverReceiveFile = [&](){
        receiver.receiveFile(receiveFileName);
    };

    std::thread s_thread(senderSendFile);
    std::thread r_thread(receiverReceiveFile);
    s_thread.join();
    r_thread.join();
    EXPECT_TRUE(compareFile(sendFileName, receiveFileName));
    deleteFile(sendFileName);
    deleteFile(receiveFileName);
}

TEST(TestIPC, Shmem)
{
    std::string sendFileName = "test1k.txt";
    std::string sendFileSize = "1k";
    std::string receiveFileName = "hello";
    createFile(sendFileName,sendFileSize);
    SenderWithShmem sender;
    ReceiverWithShmem receiver;

    auto senderSendFile = [&](){
        sender.sendFile(sendFileName);
    };

    auto receiverReceiveFile = [&](){
        receiver.receiveFile(receiveFileName);
    };

    std::thread s_thread(senderSendFile);
    std::thread r_thread(receiverReceiveFile);
    s_thread.join();
    r_thread.join();
    EXPECT_TRUE(compareFile(sendFileName, receiveFileName));
    deleteFile(sendFileName);
    deleteFile(receiveFileName);
}

//Just try testing different things
TEST(TestPipeSender, Constructor)
{
    SenderWithPipe sender1;
    EXPECT_EQ(sender1.fifoPath_,"/tmp/myfifo");
    //it seems that it should start with /tmp or something?
    SenderWithPipe sender2("/tmp/testFifo");
    EXPECT_EQ(sender2.fifoPath_,"/tmp/testFifo");
}

TEST(TestPipeReceiver, PrivateMemberVariableWithDefaultValue)
{
    ReceiverWithPipe receiver;
    EXPECT_EQ(receiver.bufSize_,80);
}

TEST(TestMsgqSender, CheckMqd)
{
    SenderWithMsgq sender;
    EXPECT_NE(sender.mqd_,0);
}

TEST(TestMsgqReceiver, InvalidName)
{
    EXPECT_ANY_THROW( 
        ReceiverWithMsgq receiver("/mq/Example");
    );
    EXPECT_ANY_THROW( 
        ReceiverWithMsgq receiver("mqExample");
    );
}

TEST(TestShmemSender, PrivateMemberVariable)
{
    SenderWithShmem sender;
    EXPECT_NE(sender.memptr, nullptr);
}
//I am thinking how to test destructor
//TEST(TestShmemReceiver)