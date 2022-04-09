```
// 非系统调用，初始化io_uring，entries：队列深度 queue depth
extern int io_uring_queue_init(unsigned entries, struct io_uring *ring, unsigned flags);

// 非系统调用，清理io_uring
extern void io_uring_queue_exit(struct io_uring *ring);

// 非系统调用，获取一个可用的 submit_queue_entry，用来提交IO
extern struct io_uring_sqe *io_uring_get_sqe(struct io_uring *ring);

// 非系统调用，准备阶段，和libaio封装的io_prep_writev一样
static inline void io_uring_prep_writev(struct io_uring_sqe *sqe, int fd,const struct iovec *iovecs, unsigned nr_vecs, off_t offset)

// 非系统调用，准备阶段，和libaio封装的io_prep_readv一样
static inline void io_uring_prep_readv(struct io_uring_sqe *sqe, int fd, const struct iovec *iovecs, unsigned nr_vecs, off_t offset)
 
// 非系统调用，把准备阶段准备的data放进 submit_queue_entry
static inline void io_uring_sqe_set_data(struct io_uring_sqe *sqe, void *data)
 
// 非系统调用，设置submit_queue_entry的flag
static inline void io_uring_sqe_set_flags(struct io_uring_sqe *sqe, unsigned flags)
 
// 非系统调用，提交sq的entry，不会阻塞等到其完成，内核在其完成后会自动将sqe的偏移信息加入到cq，在提交时需要加锁
extern int io_uring_submit(struct io_uring *ring);

// 非系统调用，提交sq的entry，阻塞等到其完成，在提交时需要加锁。
extern int io_uring_submit_and_wait(struct io_uring *ring, unsigned wait_nr);

// 非系统调用 宏定义，会遍历cq从head到tail，来处理完成的IO
#define io_uring_for_each_cqe(ring, head, cqe)

// 非系统调用 遍历时，可以获取cqe的data
static inline void *io_uring_cqe_get_data(const struct io_uring_cqe *cqe)

// 非系统调用 遍历完成时，需要调整head往后移nr
static inline void io_uring_cq_advance(struct io_uring *ring, unsigned nr)
```
