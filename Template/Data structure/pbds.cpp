// ��ϣ�� 
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
cc_hash_table<string,int> mp1;//������ (�����ױ��� ) 
gp_hash_table<string,int> mp2;//��̽��
// ƽ���� 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
/*
��һ����������key������
�ڶ���������ʾvalue������.���ﲻ��Ҫӳ��ֵ,Ҳ����null_type.���ϰ汾G++�������Ҫ�滻Ϊnull_mapped_type����BZOJ��.
������������ʾkey������ʽ,��С����
���ĸ�������ʾʹ���������ݽṹ,rb_tree_tag��ʾ�����
�����������ʾ��θ��±���ڵ���Ϣ,��дtree_order_statistics_node_update�������order_of_key()��find_by_order()��������
����:	t.insert()
ɾ��:	t.erase()
��k�������ǵڼ���:	t.order_of_key();
�����еĵ�k��:		t.find_by_order();
>=x��min�ĵ�����:	t.lower_bound();
>x��min�ĵ�����:	t.upper_bound();
b����a ǰ������������ key ��ȡֵ��Χ���ཻ:	a.join(b)
keyС�ڵ���v��Ԫ������a�����������b:		a.split(v,b)
*/
