#!/bin/sh
cmd='gcc -Wall -Wextra -std=c99'

if [ $# -gt 1 ]; then
    cmd="$cmd -DPART1"
fi

cmd="$cmd $1.c"

echo "$cmd"
$cmd
