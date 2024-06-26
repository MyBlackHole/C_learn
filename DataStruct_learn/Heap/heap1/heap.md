# heap

## 基本概念

堆分为小根堆和大根堆，对于一个小根堆，它是具有如下特性的一棵完全二叉树：
1. 若树根结点存在左孩子或右孩子，则根结点的值（或某个域的值）小于等于左右孩子结点的值（或某个域的值）
2. 以左、右孩子为根的子树又各是一个堆。

大根堆的定义将上面的小于等于改成大于等于即可。
根据根的定义，
小根堆的堆顶结点具有最小值，
大根堆的堆顶结点具有最大值。

## 堆的存储结构

由于堆是一棵完全二叉树，所以适宜采用顺序存储结构，这样能够充分利用存储空间。

顺序存储结构：
对堆中所有结点进行编号，
作为下标存储到指定数组的对应元素中，下标从0开始。
按照从上到下，同一层从左到右进行。
设堆中有 n 个结点，则编号为 0 ~ n-1，
则有如下性质：

1.
    编号为 0 至 n/2-1 的结点为分支结点，
    编号为 n/2 至 n-1 的结点为叶子结点；
2.
    当 n 为奇数则每分支结点既有左孩子又有右孩子，
    当 n 为偶数则每个分支结点只有左孩子没有右孩子
3.
    对于每个编号为 i 的分支结点，
    其左孩子结点的编号 2i + 1，
    右孩子结点的编号为 2i + 2
4.
    除编号为 0 的堆顶结点外，
    对于其余编号为 i 的结点，
    其父结点的编号为 (i-1)/2
