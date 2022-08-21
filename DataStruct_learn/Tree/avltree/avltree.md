```
自平衡二叉查找树（AVL tree）: 首先也是二次查找树，其实
任何2个子树的高度差不大于1
在删除，插入的过程中不断调整子树的高度，保证平均和最坏情况下都是O(logn)

Adelson-Velskii 和 Landis 1962年 创造。

1） 平衡因子 -1 0 1 节点是正常的。平衡因子 = 左子树高度-右字数高度
2） 除此之外的节点是不平衡的，需要重新平衡这个树。也就是AVL旋转

插入节点：

a: 左旋转(RR型：节点x的右孩子的右孩子上插入新元素）平衡因子由-1 -》-2
时，需要绕节点x左旋转 b：右旋转(LL型：节点X的左孩子的左孩子上插入新元素）
平衡因子有1-》2，右旋转 c:
先左后右旋转:(LR型:树中节点X的左孩子的右孩子上插入新元素）
平衡因子从1变成2后，就需要 先绕X的左子节点Y左旋转，接着再绕X右旋转 d:
先右后左旋转：(RL型:节点X的右孩子的左孩子上插入新元素)


                6	  6                  6              6
           /		\           	/                \
          5          7	           3                  9
        /          	  \             \                 /
   3               8             5               7
    (LL型)     （RR）            (LR)            (RL)


删除节点：




可以看到，为了保证高度平衡，插入和删除操作代价增加

```