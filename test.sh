#!/usr/bin/bash
#[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

if [ -f "test.log" ] ; then
    echo "test.log exists; remove it first"
    exit 1
fi

bazel test //test:test
bazel test //test:test2
chmod +w ./bazel-testlogs/test/test/test.log
cat ./bazel-testlogs/test/test2/test.log >> ./bazel-testlogs/test/test/test.log
cp ./bazel-testlogs/test/test/test.log .
echo "test log is in current directory!"
#bazel clean