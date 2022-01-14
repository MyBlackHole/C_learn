/* DO NOT EDIT, automatically generated by update_ev_wrap */
#ifndef EV_WRAP_H
#define EV_WRAP_H
#define acquire_cb ((loop)->acquire_cb)
/* 活跃的事件数 */
#define activecnt ((loop)->activecnt)
/* 待监控的fd数组，及大小；fd即数组索引 */
#define anfdmax ((loop)->anfdmax)
#define anfds ((loop)->anfds)
#define async_pending ((loop)->async_pending)
#define asynccnt ((loop)->asynccnt)
#define asyncmax ((loop)->asyncmax)
#define asyncs ((loop)->asyncs)
/* 底层事件模块儿标识，如EVBACKEND_EPOLL */
#define backend ((loop)->backend)
/* 底层事件模块儿的fd，如epoll_create()返回值 */
#define backend_fd ((loop)->backend_fd)
#define backend_mintime ((loop)->backend_mintime)
/* 对应底层事件的操控，如epoll_modify */
#define backend_modify ((loop)->backend_modify)
/* 对应底层事件的查询，如epoll_poll */
#define backend_poll ((loop)->backend_poll)
#define checkcnt ((loop)->checkcnt)
#define checkmax ((loop)->checkmax)
#define checks ((loop)->checks)
#define cleanupcnt ((loop)->cleanupcnt)
#define cleanupmax ((loop)->cleanupmax)
#define cleanups ((loop)->cleanups)
/* 当前进程的PID */
#define curpid ((loop)->curpid)
/* 不适于EPOLL系统处理的fd数组 */    
#define epoll_epermcnt ((loop)->epoll_epermcnt)
#define epoll_epermmax ((loop)->epoll_epermmax)
#define epoll_eperms ((loop)->epoll_eperms)
/* EPOLL系统的监控事件数组，及容量大小 */
#define epoll_eventmax ((loop)->epoll_eventmax)
#define epoll_events ((loop)->epoll_events)
#define evpipe ((loop)->evpipe)
/* 待处理的IO事件改动队列 */
#define fdchangecnt ((loop)->fdchangecnt)
#define fdchangemax ((loop)->fdchangemax)
#define fdchanges ((loop)->fdchanges)
/* fork操作数组 */    
#define forkcnt ((loop)->forkcnt)
#define forkmax ((loop)->forkmax)
#define forks ((loop)->forks)
#define fs_2625 ((loop)->fs_2625)
#define fs_fd ((loop)->fs_fd)
#define fs_hash ((loop)->fs_hash)
#define fs_w ((loop)->fs_w)
#define idleall ((loop)->idleall)
#define idlecnt ((loop)->idlecnt)
#define idlemax ((loop)->idlemax)
#define idles ((loop)->idles)
/* 处理pendings队列的回调函数，初始化为ev_invoke_pending() */
#define invoke_cb ((loop)->invoke_cb)
#define io_blocktime ((loop)->io_blocktime)
#define iocp ((loop)->iocp)
#define kqueue_changecnt ((loop)->kqueue_changecnt)
#define kqueue_changemax ((loop)->kqueue_changemax)
#define kqueue_changes ((loop)->kqueue_changes)
#define kqueue_eventmax ((loop)->kqueue_eventmax)
#define kqueue_events ((loop)->kqueue_events)
#define kqueue_fd_pid ((loop)->kqueue_fd_pid)
/* 事件循环相关的控制变量，如深度 */    
#define loop_count ((loop)->loop_count)
#define loop_depth ((loop)->loop_depth)
#define loop_done ((loop)->loop_done)
/* monotonic time: 从某个固定的时间点开始的绝对的逝去时间 */
#define mn_now ((loop)->mn_now)
/* mn_now的取整时间 */
#define now_floor ((loop)->now_floor)
#define origflags ((loop)->origflags)
/* dummy事件；删除悬挂事件列表时，被当作哨兵，以防止更改数组带来的高代价 */
#define pending_w ((loop)->pending_w)
/* 等待客户端处理到事件数组，二维，第一维代表优先级 */
#define pendingcnt ((loop)->pendingcnt)
#define pendingmax ((loop)->pendingmax)
#define pendingpri ((loop)->pendingpri)
#define pendings ((loop)->pendings)
#define periodiccnt ((loop)->periodiccnt)
#define periodicmax ((loop)->periodicmax)
#define periodics ((loop)->periodics)
#define pipe_w ((loop)->pipe_w)
#define pipe_write_skipped ((loop)->pipe_write_skipped)
#define pipe_write_wanted ((loop)->pipe_write_wanted)
#define pollcnt ((loop)->pollcnt)
#define pollidxmax ((loop)->pollidxmax)
#define pollidxs ((loop)->pollidxs)
#define pollmax ((loop)->pollmax)
#define polls ((loop)->polls)
#define port_eventmax ((loop)->port_eventmax)
#define port_events ((loop)->port_events)
/* 是否经历过fork() */
#define postfork ((loop)->postfork)
#define preparecnt ((loop)->preparecnt)
#define preparemax ((loop)->preparemax)
#define prepares ((loop)->prepares)
#define release_cb ((loop)->release_cb)
#define rfeedcnt ((loop)->rfeedcnt)
#define rfeedmax ((loop)->rfeedmax)
#define rfeeds ((loop)->rfeeds)
/* ev_rt_now与mn_now的差值 */
#define rtmn_diff ((loop)->rtmn_diff)
#define sig_pending ((loop)->sig_pending)
#define sigfd ((loop)->sigfd)
#define sigfd_set ((loop)->sigfd_set)
#define sigfd_w ((loop)->sigfd_w)
#define timeout_blocktime ((loop)->timeout_blocktime)
/* 定时器堆 */
#define timercnt ((loop)->timercnt)
#define timermax ((loop)->timermax)
#define timers ((loop)->timers)
#define userdata ((loop)->userdata)
#define vec_eo ((loop)->vec_eo)
#define vec_max ((loop)->vec_max)
#define vec_ri ((loop)->vec_ri)
#define vec_ro ((loop)->vec_ro)
#define vec_wi ((loop)->vec_wi)
#define vec_wo ((loop)->vec_wo)
#else
#undef EV_WRAP_H
#undef acquire_cb
#undef activecnt
#undef anfdmax
#undef anfds
#undef async_pending
#undef asynccnt
#undef asyncmax
#undef asyncs
#undef backend
#undef backend_fd
#undef backend_mintime
#undef backend_modify
#undef backend_poll
#undef checkcnt
#undef checkmax
#undef checks
#undef cleanupcnt
#undef cleanupmax
#undef cleanups
#undef curpid
#undef epoll_epermcnt
#undef epoll_epermmax
#undef epoll_eperms
#undef epoll_eventmax
#undef epoll_events
#undef evpipe
#undef fdchangecnt
#undef fdchangemax
#undef fdchanges
#undef forkcnt
#undef forkmax
#undef forks
#undef fs_2625
#undef fs_fd
#undef fs_hash
#undef fs_w
#undef idleall
#undef idlecnt
#undef idlemax
#undef idles
#undef invoke_cb
#undef io_blocktime
#undef iocp
#undef kqueue_changecnt
#undef kqueue_changemax
#undef kqueue_changes
#undef kqueue_eventmax
#undef kqueue_events
#undef kqueue_fd_pid
#undef loop_count
#undef loop_depth
#undef loop_done
#undef mn_now
#undef now_floor
#undef origflags
#undef pending_w
#undef pendingcnt
#undef pendingmax
#undef pendingpri
#undef pendings
#undef periodiccnt
#undef periodicmax
#undef periodics
#undef pipe_w
#undef pipe_write_skipped
#undef pipe_write_wanted
#undef pollcnt
#undef pollidxmax
#undef pollidxs
#undef pollmax
#undef polls
#undef port_eventmax
#undef port_events
#undef postfork
#undef preparecnt
#undef preparemax
#undef prepares
#undef release_cb
#undef rfeedcnt
#undef rfeedmax
#undef rfeeds
#undef rtmn_diff
#undef sig_pending
#undef sigfd
#undef sigfd_set
#undef sigfd_w
#undef timeout_blocktime
#undef timercnt
#undef timermax
#undef timers
#undef userdata
#undef vec_eo
#undef vec_max
#undef vec_ri
#undef vec_ro
#undef vec_wi
#undef vec_wo
#endif
