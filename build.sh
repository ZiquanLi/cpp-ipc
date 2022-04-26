#!/usr/bin/bash
echo "start building sender"
bazel build //src/main:sender
echo "start building receiver"
bazel build //src/main:receiver
