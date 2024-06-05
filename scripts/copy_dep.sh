#!/bin/sh

deplist=$( ldd $1 | awk '{if (match($3,"/")){ print $3}}' )  
cp -L -n $deplist $2

# 检查参数是否传递正确
if [ $# -ne 2 ]; then
    echo "Usage: $0 <program_path> <target_dir>"
    exit 1
fi

# 获取程序的依赖项
deplist=$(readelf -d "$1" | grep "NEEDED" | awk '{print $5}' | tr -d '[]')

# 遍历依赖项并拷贝到目标目录
for lib in $deplist; do
    # 检查库文件是否存在
    if [ -e "$lib" ]; then
        # 拷贝库文件到目标目录
        cp -L -n "$lib" "$2"
        echo "Copied $lib to $2"
    # else
    #     echo "Error: $lib not found."
    fi
done