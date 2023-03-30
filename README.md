# C_learn
学习语法与第三方库测试

## 构建
```bash
gn gen out
ninja -C out
```

## 生成索引 compile_commands.json
```shell
# 针对不同项目
# ninja
ninja -C out -t compdb cxx cc > compile_commands.json 

# bear (注意关闭 http_proxy 代理)
bear -- make

# compiledb
compiledb make

# cmake
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

## 宏展开
```shell
nohup rtags-rdm &

# 在 compile_commands.json 所在目录执行
rtags-rc -J .
```

## lib 库检查
```shell
ldconfig -p | grep uv
```
