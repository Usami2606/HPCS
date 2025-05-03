module load openmpi/3.1.6-gcc4.8.5
module list

export PS1='-bash-4.2:\w\$ '

# sh script.sh → サブシェルで実行（環境は引き継がれない）
# source script.sh or . script.sh → 現在のシェルで実行（環境が引き継がれる）