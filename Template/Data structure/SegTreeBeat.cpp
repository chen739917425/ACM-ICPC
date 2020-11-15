#include<bits/stdc++.h>
#define dd(x) cout<<#x<<" = "<<x<<" "
#define de(x) cout<<#x<<" = "<<x<<endl
#define de_arr(a,s,t) cout<<#a<<": ";for (int z=(s);z<=(t);++z)cout<<a[z]<<" ";cout<<endl;
#define sz(x) int(x.size())
#define All(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
const double eps=1e-8;
inline int sign(double x){return (x>eps)-(x<-eps);}
inline int add(int a,int b){a+=b;return a<0?a+mod:a>=mod?a-mod:a;}
inline int mul(ll a,ll b){return a*b%mod;}
const int maxn=5e3+10,mod=998244353,INF=0x3f3f3f3f;
struct node{
	int mx,mx2,cmx,mn,mn2,cmn,tmx,tmn;
	ll s;
}t[maxn<<2];
inline void pushup(int u) {  // 向上更新标记
	int ls=u<<1, rs=u<<1|1;
	t[u].sum = t[ls].sum + t[rs].sum;
	if (t[ls].mx == t[rs].mx){
		t[u].mx = t[ls].mx, t[u].cmx = t[ls].cmx + t[rs].cmx;
		t[u].mx2 = max(t[ls].mx2, t[rs].mx2);
	} 
	else if (t[ls].mx > t[rs].mx){
		t[u].mx = t[ls].mx, t[u].cmx = t[ls].cmx;
		t[u].mx2 = max(t[ls].mx2, t[rs].mx);
	} 
	else{
		t[u].mx = t[rs].mx, t[u].cmx = t[rs].cmx;
		t[u].mx2 = max(t[ls].mx, t[rs].mx2);
	}
	if (t[ls].mn == t[rs].mn){
		t[u].mn = t[ls].mn, t[u].cmn = t[ls].cmn + t[rs].cmn;
		t[u].mn2 = min(t[ls].mn2, t[rs].mn2);
	}
	else if (t[ls].mn < t[rs].mn){
		t[u].mn = t[ls].mn, t[u].cmn = t[ls].cmn;
		t[u].mn2 = min(t[ls].mn2, t[rs].mn);
	}
	else{
		t[u].mn = t[rs].mn, t[u].cmn = t[rs].cmn;
		t[u].mn2 = min(t[ls].mn, t[rs].mn2);
	}
}
}
int main()
{

	return 0;
}

