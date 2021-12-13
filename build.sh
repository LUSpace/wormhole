#!/usr/bin/env bash

g++ -shared -o libworm.so -fPIC lib.c kv.c wh.c worm_wrapper.cpp 