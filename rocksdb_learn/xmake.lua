local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
-- g++ rocksdb_client_test.cc -o simple ../librocksdb.a -I../include -lpthread -ldl -lrt -lsnappy -lgflags -lz -lbz2 -llz4 -lzstd -luring
-- target(dir_path)
--     set_kind("binary")
--     add_files("*.c")
--     add_links("rt", "dl", "snappy", "gflags", "z", "bz2", "lz4", "zstd", "uring", "pthread", "rocksdb")
