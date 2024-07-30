# C_learn

学习语法与第三方库测试

- 构建
```shell
paru -S paho-mqtt-c raft

xmake
```

- compile_commands.json
```bash
xmake project -k compile_commands --lsp=clangd
```

- xmakefile	
```shell
xmake project -k makefile
```

- lib 库检查
```shell
ldconfig - p | grep uv
```

- 测试
```shell
xmake run algorithms_learn
```
