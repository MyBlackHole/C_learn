# zlib

```shell
关键的函数有那么几个:
1. int compress2 (Bytef *dest,   uLongf *destLen,const Bytef *source, uLong sourceLen,int level);
    功能和上一个函数一样,都一个参数可以指定压缩质量和压缩数度之间的关系(0-9)不敢肯定这个参数的话不用太在意它,明白一个道理就好了: 要想得到高的压缩比就要多花时间
2. uLong compressBound (uLong sourceLen);
    计算需要的缓冲区长度. 假设你在压缩之前就想知道你的产度为 sourcelen 的数据压缩后有多大, 可调用这个函数计算一下,这个函数并不能得到精确的结果,但是它可以保证实际输出长度肯定小于它计算出来的长度
3. deflateInit() + deflate() + deflateEnd()；
    3个函数结合使用完成压缩功能,具体用法看 example.c 的 test_deflate()函数. 其实 compress() 函数内部就是用这3个函数实现的(工程 zlib 的 compress.c 文件)
4. inflateInit() + inflate() + inflateEnd()
    和(5)类似,完成解压缩功能.
5. gz开头的函数. 
    用来操作*.gz的文件,和文件stdio调用方式类似. 想知道怎么用的话看example.c 的 test_gzio() 函数,很easy.
```
