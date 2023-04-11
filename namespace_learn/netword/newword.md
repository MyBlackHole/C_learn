## 先增加一个网桥lxcbr0，模仿docker0
brctl addbr lxcbr0
brctl stp lxcbr0 off
# 为网桥设置IP地址
ip addr add 192.168.10.1/24 dev lxcbr0 
ip link set dev lxcbr0 up

## 创建一个 network namespace - ns1
# 增加一个 namesapce 命令为 ns1
ip netns add ns1 

# 激活namespace中的loopback，即127.0.0.1（使用ip netns exec ns1来操作ns1中的命令）
ip netns exec ns1 ip link set dev lo up 

## 然后，我们需要增加一对虚拟网卡
# 增加一个对虚拟网卡，注意其中的veth类型，其中一个网卡要放到容器（命名空间）中
ip link add veth-ns1 type veth peer name lxcbr0.1

# 把 veth-ns1 放入 namespace ns1中，这样容器中就会有一个新的网卡了，并且宿主机的 veth-ns1 网卡会消失
ip link set veth-ns1 netns ns1

# 把容器里的 veth-ns1改名为 eth0 （容器外会冲突，容器内就不会了）
ip netns exec ns1  ip link set dev veth-ns1 name eth0 

# 为容器中的网卡分配一个IP地址，并激活它
ip netns exec ns1 ip addr add 192.168.10.11/24 dev eth0
ip netns exec ns1 ip link set dev eth0 up

# 上面我们把veth-ns1这个网卡放入容器中，这里我们把lxcbr0.1添加上网桥上
brctl addif lxcbr0 lxcbr0.1

# 这步激活不能忘了, 否则会因 lxcbr0 网桥这边的 veth 为启用导致命名空间内检测不到另外一端
# 谢谢向磊哥帮忙看了下，一开始没加这句，导致网络一直不通，自己排查了挺久没发现
ip link set dev lxcbr0.1 up

# 为容器增加一个路由规则，让容器可以访问外面的网络
ip netns exec ns1 ip route add default via 192.168.10.1

# 在/etc/netns下创建network namespce名称为ns1的目录，
# 然后为这个namespace设置resolv.conf，这样，容器内就可以访问域名了
mkdir -p /etc/netns/ns1
echo "nameserver 8.8.8.8" > /etc/netns/ns1/resolv.conf
