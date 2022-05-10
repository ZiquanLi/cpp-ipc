load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "argsParser",
    hdrs = ["argsParser.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "senderWithPipe",
    srcs = ["senderWithPipe.cpp"],
    hdrs = ["senderWithPipe.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "receiverWithPipe",
    srcs = ["receiverWithPipe.cpp"],
    hdrs = ["receiverWithPipe.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "senderWithMsgq",
    srcs = ["senderWithMsgq.cpp"],
    hdrs = ["senderWithMsgq.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "receiverWithMsgq",
    srcs = ["receiverWithMsgq.cpp"],
    hdrs = ["receiverWithMsgq.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "senderWithShmem",
    srcs = ["senderWithShmem.cpp"],
    hdrs = ["senderWithShmem.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "receiverWithShmem",
    srcs = ["receiverWithShmem.cpp"],
    hdrs = ["receiverWithShmem.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)