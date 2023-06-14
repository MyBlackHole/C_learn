# 修改配置
lvim /etc/sysctl.conf
net.core.somaxconn = 5
# 使配置生效
sudo sysctl -p
net.core.somaxconn = 5

./out/obj/debug/conn_queue_full/server
ss -ln4
tcp          LISTEN        0             4                          0.0.0.0:8000                     0.0.0.0:*

./out/obj/debug/conn_queue_full/client 127.0.0.1 8000
ss -ln4
tcp          LISTEN        5             4                          0.0.0.0:8000                     0.0.0.0:*

ss -n4 |grep 8000
tcp   ESTAB    9      0                127.0.0.1:8000        127.0.0.1:36726
tcp   ESTAB    0      0                127.0.0.1:36756       127.0.0.1:8000
tcp   ESTAB    0      0                127.0.0.1:36724       127.0.0.1:8000
tcp   SYN-SENT 0      1                127.0.0.1:36764       127.0.0.1:8000
tcp   ESTAB    9      0                127.0.0.1:8000        127.0.0.1:36724
tcp   ESTAB    9      0                127.0.0.1:8000        127.0.0.1:36756
tcp   ESTAB    0      0                127.0.0.1:36746       127.0.0.1:8000
tcp   ESTAB    0      0                127.0.0.1:36740       127.0.0.1:8000
tcp   ESTAB    0      0                127.0.0.1:36726       127.0.0.1:8000
tcp   ESTAB    9      0                127.0.0.1:8000        127.0.0.1:36746
tcp   ESTAB    9      0                127.0.0.1:8000        127.0.0.1:36740


out:
start conn!
start write!
Message from server : BLACK HOLE
start conn!
start write!
Message from server : BLACK HOLE
start conn!
start write!
Message from server : BLACK HOLE
start conn!
start write!
Message from server : BLACK HOLE
start conn!
start write!
Message from server : BLACK HOLE
start conn!
connect() error!


