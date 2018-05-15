# libv4l2

A simple video4linux2 library.

## Features

* Internal continuous grabbing.
* Loopback frame replication.

## License

LGPLv2

## Dependencies

[libcollections](https://github.com/rsfreitas/libcollections): for thread independent error code and reference count.

## Compiling

In order to compile the project you must have at least the following programs
installed;

* C compiler
* CMake, at least version 2.8

After installing them you can compile the project using the commands:

* mkdir build
* cd build
* cmake ..
* make

