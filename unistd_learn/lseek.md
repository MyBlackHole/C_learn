```

<!-- 对 a+ 无效 -->
<!-- a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留 -->

所有打开的文件都有一个当前文件偏移量

SEEK_SET 参数offset 即为新的读写位置.
SEEK_CUR 以目前的读写位置往后增加offset 个位移量.
SEEK_END 将读写位置指向文件尾后再增加offset 个位移量. 当whence 值为SEEK_CUR
或 SEEK_END 时, 参数offet 允许负值的出现.
 1) 欲将读写位置移到文件开头时:lseek(int fildes, 0, SEEK_SET);
 2) 欲将读写位置移到文件尾时:lseek(int fildes, 0, SEEK_END);
 3) 想要取得目前文件位置时:lseek(int fildes, 0, SEEK_CUR);
返回结果是当前文件偏移量
返回值等于 -1 失败

```
