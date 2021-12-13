#!/usr/bin/env bash

g++ -shared -o libworm.so -fPIC worm_wrapper.cpp wh.c kv.c lib.c