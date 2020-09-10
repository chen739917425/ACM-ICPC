// 可删堆 
struct Heap{
	priority_queue<int> h,d;
	inline void push(int x){h.push(x);}
	inline void del(int x){d.push(x);} 
	inline void clr(){
		while (sz(d)&&h.top()==d.top())
			h.pop(),d.pop();
	}
	inline int top(){clr();return h.top();}
	inline void pop(){clr();h.pop();}
	inline int size(){return sz(h)-sz(d);}
};
