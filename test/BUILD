cc_test(
  name = "test",
  size = "small",
  srcs = ["tests.cpp"],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//src/lib:senderWithPipe",
    "//src/lib:senderWithMsgq",
    "//src/lib:senderWithShmem",
    "//src/lib:receiverWithPipe",
    "//src/lib:receiverWithMsgq",
    "//src/lib:receiverWithShmem",

  ],
  linkopts = ["-lrt","-lpthread"],
)

cc_test(
  name = "test2",
  size = "small",
  srcs = ["tests2.cpp"],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//src/lib:senderWithPipe",
    "//src/lib:senderWithMsgq",
    "//src/lib:senderWithShmem",
    "//src/lib:receiverWithPipe",
    "//src/lib:receiverWithMsgq",
    "//src/lib:receiverWithShmem",

  ],
  linkopts = ["-lrt","-lpthread"],
)