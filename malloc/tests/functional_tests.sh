#!/bin/sh

export LD_PRELOAD=./libmalloc.so

set -v

ls
tree
ip a
ls -l
less Makefile
find
