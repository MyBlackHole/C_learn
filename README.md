# C_learn
# 构建
```bash
gn gen out
ninja -C out
```

# 索引
ninja -C out -t compdb cxx cc > compile_commands.json 
