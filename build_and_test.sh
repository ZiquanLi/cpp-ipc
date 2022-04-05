#!/usr/bin/bash
#[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

bazel build //src/main:receiver
bazel build //src/main:sender

bazel test //tests:senderWithPipe_test