#!/usr/bin/bash
#[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

DIR="sender_and_receiver"
if [ -d $DIR ] ; then
    echo "sender_and_receiver directory exists; remove it first"
    exit 1
fi

if [ -f "test.log" ] ; then
    echo "test.log exists; remove it first"
    exit 1
fi

echo "start building sender and receiver"
bazel build //src/main:sender
bazel build //src/main:receiver
echo "finish building"
mkdir $DIR
cp ./bazel-bin/src/main/sender $DIR
cp ./bazel-bin/src/main/receiver $DIR
echo "sender and receiver are in sender_and_receiver directory now!"

bazel test //test:test
cp ./bazel-testlogs/test/test/test.log .
echo "test log is in current directory!"
bazel clean