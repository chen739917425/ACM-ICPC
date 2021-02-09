// 哈希表 
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
cc_hash_table<string,int> mp1;//拉链法 (不容易被卡 ) 
gp_hash_table<string,int> mp2;//查探法
// 平衡树 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
/*
第一个参数代表key的类型
第二个参数表示value的类型.这里不需要映射值,也就填null_type.在老版本G++中这个需要替换为null_mapped_type（如BZOJ）.
第三个参数表示key的排序方式,从小到大
第四个参数表示使用哪种数据结构,rb_tree_tag表示红黑树
第五个参数表示如何更新保存节点信息,填写tree_order_statistics_node_update会额外获得order_of_key()和find_by_order()两个功能
插入:	t.insert()
删除:	t.erase()
求k在树中是第几大:	t.order_of_key();
求树中的第k大:		t.find_by_order();
>=x的min的迭代器:	t.lower_bound();
>x的min的迭代器:	t.upper_bound();
b并入a 前提是两棵树的 key 的取值范围不相交:	a.join(b)
key小于等于v的元素属于a，其余的属于b:		a.split(v,b)
*/
