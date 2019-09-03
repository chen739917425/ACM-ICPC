/*
	bit的位置从0开始，且从右往左数，即从低位开始
*/ 
bitset<100> bit(string("100101")) 	// 用string初始化
bit=x 							  	// 用整数x的二进制直接赋值
bit.size() 						  	// 返回大小（位数）
bit.count() 						// 返回1的个数
bit.any() 							// 返回是否有1
bit.none() 							// 返回是否没有1
bit.set() 							// 全都变成1
bit.set(p) 							// 将第p + 1位变成1
bit.set(p, x) 						// 将第p + 1位变成x
bit.reset() 						// 全都变成0
bit.reset(p) 						// 将第p + 1位变成0
bit.flip() 							// 全都取反
bit.flip(p) 						// 将第p + 1位取反
bit.to_ulong() 						// 返回它转换为unsigned long的结果，如果超出范围则报错
bit.to_ullong() 					// 返回它转换为unsigned long long的结果，如果超出范围则报错
bit.to_string() 					// 返回它转换为string的结果
