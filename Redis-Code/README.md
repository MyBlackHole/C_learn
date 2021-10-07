# Redis-Code

# redis 键值数据库源码分析

## test:（测试）

- memtest.c 内存检测
- redis_benchmark.c 用于 redis 性能测试的实现。
- redis_check_aof.c 用于更新日志检查的实现。
- redis_check_dump.c 用于本地数据库检查的实现。
- testhelp.c 一个 C 风格的小型测试框架。

# struct:（结构体）

- adlist.c 用于对 list 的定义，它是个双向链表结构
- dict.c 主要对于内存中的 hash 进行管理
- sds.c 用于对字符串的定义
- sparkline.c 一个拥有 sample 列表的序列
- t_hash.c hash 在 Server/Client 中的应答操作。主要通过 redisObject 进行类型转换。
- t_list.c list 在 Server/Client 中的应答操作。主要通过 redisObject 进行类型转换。
- t_set.c set 在 Server/Client 中的应答操作。主要通过 redisObject 进行类型转换。
- t_string.c string 在 Server/Client 中的应答操作。主要通过 redisObject 进行类型转换。
- t_zset.c zset 在 Server/Client 中的应答操作。主要通过 redisObject 进行类型转换。
- ziplist.c ziplist 是一个类似于 list 的存储对象。它的原理类似于 zipmap。
- zipmap.c zipmap 是一个类似于 hash 的存储对象。

# data:（数据操作）

- aof.c 全称为 append only file，作用就是记录每次的写操作,在遇到断电等问题时可以用它来恢复数据库状态。
- config.c 用于将配置文件 redis.conf 文件中的配置读取出来的属性通过程序放到 server 对象中。
- db.c 对于 Redis 内存数据库的相关操作。
- multi.c 用于事务处理操作。
- rdb.c 对于 Redis 本地数据库的相关操作，默认文件是 dump.rdb（通过配置文件获得），包括的操作包括保存，移除，查询等等。
- replication.c 用于主从数据库的复制操作的实现。

# tool:（工具）

- bitops.c 位操作相关类
- debug.c 用于调试时使用
- endianconv.c 高低位转换，不同系统，高低位顺序不同
- help.h 辅助于命令的提示信息
- lzf_c.c 压缩算法系列
- lzf_d.c 压缩算法系列
- rand.c 用于产生随机数
- release.c 用于发步时使用
- sha1.c sha 加密算法的实现
- util.c 通用工具方法
- crc64.c 循环冗余校验

# event:（事件）

- ae.c 用于 Redis 的事件处理，包括句柄事件和超时事件。
- ae_epoll.c 实现了 epoll 系统调用的接口
- ae_evport.c 实现了 evport 系统调用的接口
- ae_kqueue.c 实现了 kqueuex 系统调用的接口
- ae_select.c 实现了 select 系统调用的接口

# baseinfo:（基本信息）

- asciilogo,c redis 的 logo 显示
- version.h 定有 Redis 的版本号

# compatible:（兼容）

- fmacros.h 兼容 Mac 系统下的问题
- solarisfixes.h 兼容 solary 下的问题

# main:（主程序）

- redis.c redis 服务端程序
- redis_cli.c redis 客户端程序

# net:（网络）

- anet.c 作为 Server/Client 通信的基础封装
- networking.c 网络协议传输方法定义相关的都放在这个文件里面了。

# wrapper:（封装类）

- bio.c background I/O 的意思，开启后台线程用的
- hyperloglog.c 一种用于大数据处理的，基数统计算法
- intset.c 整数范围内的使用 set，并包含相关 set 操作。
- latency.c 延迟类
- migrate.c 命令迁移类，包括命令的还原迁移等
- notify.c 通知类
- object.c 用于创建和释放 redisObject 对象
- pqsort.c 排序算法类
- pubsub.c 用于订阅模式的实现，有点类似于 Client 广播发送的方式。
- rio.c redis 定义的一个 I/O 类
- slowlog.c 一种日志类型的，记录超时查询记录
- sort.c 排序算法类，与 pqsort.c 使用的场景不同
- syncio.c 用于同步 Socket 和文件 I/O 操作。
- zmalloc.c 关于 Redis 的内存分配的封装实现

# others:（存放了一些我暂时还不是很清楚的类,所以没有解释了）

- scripting.c
- sentinel.c
- setproctitle.c
- valgrind.sh
- redisassert.h

## Redis 中的 11 大优秀设计:

- [hyperloglog 基量统计算法的实现](http://blog.csdn.net/androidlushangderen/article/details/40683763)
- [zmalloc 内存分配的重新实现](http://blog.csdn.net/androidlushangderen/article/details/40659331)
- [multi 事务操作](http://blog.csdn.net/androidlushangderen/article/details/40392209)
- [redis-benchmark 性能测试](http://blog.csdn.net/androidlushangderen/article/details/40211907)
- [zipmap 压缩结构的设计](http://blog.csdn.net/androidlushangderen/article/details/39994599)
- [sparkline 微线图的重新设计](http://blog.csdn.net/androidlushangderen/article/details/39964591)
- [对象引用计数实现内存管理](http://blog.csdn.net/androidlushangderen/article/details/40716469)
- [fork 子进程实现后台程序](http://blog.csdn.net/androidlushangderen/article/details/40266579)
- [long long 类型转为 String 类型方法](http://blog.csdn.net/androidlushangderen/article/details/40649623)
- [正则表达式的实现算法](http://blog.csdn.net/androidlushangderen/article/details/40649623)
- [Redis 的 drand48()随机算法重实现](http://blog.csdn.net/androidlushangderen/article/details/40582189)
