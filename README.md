# IPC in C++

- [x] Pipe
- [] Shared memory
- [] Message queue

The main idea:
one object called sender executing sending file function;
another object called receiver executing receiving file function.

Use bazel as a build tool:
build the target(output will be in /bazel-out/k8-fastbuild/bin):
bazel build //src/main:sender
bazel build //src/main:receiver

remove the bazel output:
bazel clean

run the specified target:
bazel run


