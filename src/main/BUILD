load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_binary(
    name = "sender",
    srcs = ["sender.cpp"],
    deps = [
        "//src/lib:senderWithPipe",
        "//src/lib:senderWithMsgq",
        "//src/lib:senderWithShmem",
        "//src/lib:argsParser"
    ],
    visibility = ["//visibility:public"],
    linkopts= ["-lrt","-pthread"],

)

cc_binary(
    name = "receiver",
    srcs = ["receiver.cpp"],
    deps = [
        "//src/lib:receiverWithPipe",
        "//src/lib:receiverWithMsgq",
        "//src/lib:receiverWithShmem",
        "//src/lib:argsParser",
    ],
    visibility = ["//visibility:public"],
    linkopts= ["-lrt","-pthread"],
)
