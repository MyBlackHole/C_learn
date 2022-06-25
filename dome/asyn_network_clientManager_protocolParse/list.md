```
链表和链表节点的 API

表 3-1 列出了所有用于操作链表和链表节点的 API 。


表 3-1 链表和链表节点 API

函数                                                        作用                                                时间复杂度

listSetDupMethod    将给定的函数设置为链表的节点值复制函数。                                O(1) 。 
listGetDupMethod    返回链表当前正在使用的节点值复制函数。                  复制函数可以通过链表的 dup 属性直接获得， O(1) 
listSetFreeMethod   将给定的函数设置为链表的节点值释放函数。                 O(1) 。 
listGetFree         返回链表当前正在使用的节点值释放函数。                  释放函数可以通过链表的 free 属性直接获得， O(1) 
listSetMatchMethod  将给定的函数设置为链表的节点值对比函数。                 O(1) 
listGetMatchMethod  返回链表当前正在使用的节点值对比函数。                  对比函数可以通过链表的 match 属性直接获得， O(1) 
listLength          返回链表的长度（包含了多少个节点）。                    链表长度可以通过链表的 len 属性直接获得， O(1) 。 
listFirst           返回链表的表头节点。                                    表头节点可以通过链表的 head 属性直接获得， O(1) 。 
listLast            返回链表的表尾节点。                                    表尾节点可以通过链表的 tail 属性直接获得， O(1) 。 
listPrevNode        返回给定节点的前置节点。                                前置节点可以通过节点的 prev 属性直接获得， O(1) 。 
listNextNode        返回给定节点的后置节点。                                后置节点可以通过节点的 next 属性直接获得， O(1) 。 
listNodeValue       返回给定节点目前正在保存的值。                          节点值可以通过节点的 value 属性直接获得， O(1) 。 
listCreate          创建一个不包含任何节点的新链表。                         O(1) 
listAddNodeHead     将一个包含给定值的新节点添加到给定链表的表头。           O(1) 
listAddNodeTail     将一个包含给定值的新节点添加到给定链表的表尾。           O(1) 
listInsertNode      将一个包含给定值的新节点添加到给定节点的之前或者之后。   O(1) 
listSearchKey       查找并返回链表中包含给定值的节点。                       O(N) ， N 为链表长度。 
listIndex           返回链表在给定索引上的节点。                             O(N) ， N 为链表长度。 
listDelNode         从链表中删除给定节点。                                   O(1) 。 
listRotate          将链表的表尾节点弹出，然后将被弹出的节点插入到链表
                    的表头， 成为新的表头节点。                              O(1) 
listDup             复制一个给定链表的副本。                                 O(N) ， N 为链表长度。 
listRelease         释放给定链表，以及链表中的所有节点。                      O(N) ， N 为链表长度。
*/

/*
 dup 函数用于复制链表节点所保存的值；
 free 函数用于释放链表节点所保存的值；
 match 函数则用于对比链表节点所保存的值和另一个输入值是否相等。

 Redis 的链表实现的特性可以总结如下：
 ?双端： 链表节点带有 prev 和 next 指针， 获取某个节点的前置节点和后置节点的复杂度都是 O(
 ) 。 ?无环： 表头节点的 prev 指针和表尾节点的 next 指
 都指向 NULL ， 对链表的访问以 NULL 为终点。
 ?带表头指针和表尾指针： 通过 list 结构的 head 指针和 tail 指针， 程序获取链表的表头节点和表尾节点的复杂度为 O(1) 。 ?带链表长度计数器： 程序使
  list 结构的 len 属性来对 list 持有
 链表节点进行计数，
 程序获取链表中节点数量的复杂度为 O(1) 。 ?多态： 链表节点使用 void*
 指针来保存节点值， 并且可以通过 ist 结构的 dup 、 free 、 match
 三个属性为节点值设置类型特定函数， 所以链表可以用于保存各种不同类型的值。

/
// listCreate创建链表
```
