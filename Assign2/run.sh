# #!/bin/bash

# # Initial number of threads
# threads=1

# # 最大スレッド数（1024）
# max_threads=512

# # スレッド数が最大を超えるまで繰り返す
# while [ $threads -le $max_threads ]; do
#     # OMP_NUM_THREADS を設定
#     export OMP_NUM_THREADS=$threads

#     # 実行
#     echo "Running with $OMP_NUM_THREADS threads"
#     ./bin/runprog

#     # 次のスレッド数を倍にする
#     threads=$((threads * 2))
# done

#!/bin/bash

# 引数チェック
if [ -z "$1" ]; then
    echo "Usage: $0 <num_threads>"
    exit 1
fi

# 引数でスレッド数を設定
export OMP_NUM_THREADS=$1

# 実行
echo "Running with $OMP_NUM_THREADS threads"
./bin/runprog

