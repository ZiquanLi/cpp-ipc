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

//these functions should be tested before being used, I think.
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

class IPCTest1k : public testing::Test {
 protected:  
  void SetUp() override {
    createFile(sendFileName,sendFileSize);
  }

  void TearDown() override {
    deleteFile(sendFileName);
  }

  std::string sendFileName = "test1k.txt";
  std::string sendFileSize = "1k";
  std::string receiveFileName = "hello";

};

class IPCTest1m : public testing::Test {
 protected:  
  void SetUp() override {
    createFile(sendFileName,sendFileSize);
  }

  void TearDown() override {
    deleteFile(sendFileName);
  }

  std::string sendFileName = "test1m.txt";
  std::string sendFileSize = "1m";
  std::string receiveFileName = "hello";
};

//the testing of other file with bigger size is similar, so do not repeat here 

TEST_F(IPCTest1k, Pipe)
{

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
    deleteFile(receiveFileName);
}

TEST_F(IPCTest1m, Pipe)
{

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
    deleteFile(receiveFileName);
}

//want to use value-parameterized tests actually, but I am not sure whether it is good to pass class as parameter
//the testing of other methods, so do not repeat here 