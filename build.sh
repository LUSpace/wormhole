#!/usr/bin/env bash

#gcc -shared -o libworm.so -fPIC worm_wrapper.cpp wh.c kv.c lib.c
gcc -c -fPIC wh.c -o wh.o
gcc -c -fPIC kv.c -o kv.o
gcc -c -fPIC lib.c -o lib.o
gcc -c -fPIC worm_wrapper.cpp -o libwh.o
gcc wh.o kv.o lib.o libwh.o -shared -o libwh.so
