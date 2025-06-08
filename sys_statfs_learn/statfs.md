### 描述
```
struct statfs {
long f_type; /* 文件系统类型 */
long f_bsize; /* 经过优化的传输块大小 */
long f_blocks; /* 文件系统数据块总数 */
long f_bfree; /* 可用块数 */
long f_bavail; /* 非超级用户可获取的块数 */
long f_files; /* 文件结点总数 */
long f_ffree; /* 可用文件结点数 */
fsid_t f_fsid; /* 文件系统标识 */
long f_namelen; /* 文件名的最大长度 */
};

#include <sys/statfs.h> 

int statfs(const char *path, struct statfs *buf);
返回值：
成功执行时，返回0。失败返回-1，errno被设为以下的某个值  

EACCES： (statfs())文件或路径名中包含的目录不可访问
EBADF ： (fstatfs()) 文件描述词无效
EFAULT： 内存地址无效
EINTR ： 操作由信号中断
EIO    ： 读写出错
ELOOP ： (statfs())解释路径名过程中存在太多的符号连接
ENAMETOOLONG：(statfs()) 路径名太长
ENOENT：(statfs()) 文件不存在
ENOMEM： 核心内存不足
ENOSYS： 文件系统不支持调用
ENOTDIR：(statfs())路径名中当作目录的组件并非目录
EOVERFLOW：信息溢出
```
