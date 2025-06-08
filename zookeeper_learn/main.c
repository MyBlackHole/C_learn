#include <stdio.h>
#include <zookeeper.h>
#include <zookeeper.jute.h>
#include <zookeeper_log.h>

// 伪分布式部署 host list最好以配置文件形式，此处为测试程序，暂时写死
const char *host_list = "127.0.0.1:12181,127.0.0.1:12182,127.0.0.1:12183";
void zk_watcher(zhandle_t *zh, int type, int state, const char *path,
		void *watcherCtx)
{
	printf("zk_watcher: [type=%d] [state=%d] [path=%s] [watcher_ctx=%p]\n",
	       type, state, path, watcherCtx);
}

void zk_exists(zhandle_t *zkhandle, const char *path)
{
	struct Stat stat;
	printf("zk_exists: ==========BEGIN============\n");
	int ret_code = zoo_exists(zkhandle, path, 0, &stat);
	printf("zk_exists: [ret=%d]\n", ret_code);
	if (ZOK == ret_code) {
		printf("zk_exists: [path=%s] [czxid=%ld] [mzxid=%ld] [version=%d] "
		       "[cversion=%d] [child_num=%d]\n",
		       path, stat.czxid, stat.mzxid, stat.version, stat);
	}
	printf("zk_exists: ==========END============\n");
}

int main()
{
	int time_out = 50000;
	zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);
	zhandle_t *zkhandle =
		zookeeper_init(host_list, zk_watcher, time_out, 0, NULL, 0);
	if (NULL == zkhandle) {
		printf("main: connect to zk fail.\n");
		return -1;
	}
	zk_exists(zkhandle, "/");

	zookeeper_close(zkhandle);

	return 0;
}
