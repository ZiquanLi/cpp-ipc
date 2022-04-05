#include <gtest/gtest.h>
#include "src/lib/senderWithPipe.h"
#include "src/lib/receiverWithPipe.h"
#include "src/lib/senderWithPipe.h"
#include "src/lib/receiverWithPipe.h"
#include <string>

TEST(senderWithPipeTest, ConstructorWithoutInput)
{
  SenderWithPipe sender;
  std::string fifoPath = sender.getFifoPath();
  EXPECT_EQ(fifoPath, "/tmp/myfifo");
}

TEST(senderWithPipeTest, ConstructorWithInput)
{
  SenderWithPipe sender("/tmp/myfifo2");
  std::string fifoPath = sender.getFifoPath();
  EXPECT_EQ(fifoPath, "/tmp/myfifo2");
}

