#!/usr/bin/env bash

gcc -shared -o libworm.so -fPIC worm_wrapper.cpp wh.c kv.c lib.c
