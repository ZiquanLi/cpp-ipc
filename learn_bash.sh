#!/usr/bin/bash
#[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

DIR="sender_and_receiver"
if [ -d "$DIR" ]; then
    echo "directory exist"
    rm -r $DIR
fi

mkdir $DIR