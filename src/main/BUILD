load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_binary(
    name = "sender",
    srcs = ["sender.cc"],
    deps = [
        "//src/lib:senderWithPipe"
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "receiver",
    srcs = ["receiver.cc"],
    deps = [
        "//src/lib:receiverWithPipe"
    ],
    visibility = ["//visibility:public"],
)
