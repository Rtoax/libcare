#!/bin/bash 
#
make -C ../src
# 添加 环境变量
export PATH=$PATH:$PWD/../src/
