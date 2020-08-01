mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline double Rand(){
	return double(rng()%10000000)/10000000;
}
inline void nextSol(){
	/* 
		从当前解的邻域中获取一个解
	*/ 
}
inline int F(){
	/*
		解的评估函数
	*/ 
}
int simulateAnneal(){
	double t = 2851103;// t0 约取 ( max(F) - min(F) ) / ln(1/0.98) 
	/* 
		随机选一个初始解 ans
	*/ 
	while (t > 0.001){
		for (int k=0;k<1000;++k){	//某一温度内迭代若干次 
			nextSol();	//从 ans 的邻域获取一个解 next_ans 
			double delta=F(next_ans)-F(ans);	//若求最大值,则取个负号 
			if (delta<0||exp(-delta/t)>Rand())
			/*
				ans 替换为 next_ans
			*/ 
		}
		t *= 0.92;	// 温度下降,一般取 0.8 ~ 0.95 
	}
	for (int i = 1; i <= 1000; ++i){	//在解的邻域再随机几个解 
		nextSol();
		if (F(next_ans)<F(ans))
		/*
			ans替换为next_ans;
		*/ 
	}
	return F(ans);
}
