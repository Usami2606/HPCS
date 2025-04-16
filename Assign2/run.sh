#!/bin/bash

# 引数でスレッド数を指定し、デフォルトは 4
OMP_NUM_THREADS=${1:-4}

# OMP_NUM_THREADS を設定
export OMP_NUM_THREADS

# 実行
echo "Using $OMP_NUM_THREADS threads"
./bin/ompsum "$@"
