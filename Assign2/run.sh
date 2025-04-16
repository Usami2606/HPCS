#!/bin/bash

# Initial number of threads
threads=4

# 最大スレッド数（1024）
max_threads=1024

# スレッド数が最大を超えるまで繰り返す
while [ $threads -le $max_threads ]; do
    # OMP_NUM_THREADS を設定
    export OMP_NUM_THREADS=$threads

    # 実行
    echo "Running with $OMP_NUM_THREADS threads"
    ./bin/ompsum

    # 次のスレッド数を倍にする
    threads=$((threads * 2))
done
