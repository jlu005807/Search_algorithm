#pragma once
//在查找表的组织方式中，线性表是最简单的一种
//在顺序表中，例如数组或者链表里查找

#include<iostream>
#include<functional>
#include<cmath>
#include<climits>
#include<vector>

//顺序查找
//从表的一端开始，依次将记录的关键字和给定值进行比较，寻找关键字
//既适用于线性表的顺序存储结构，又适用千线性表的链式存储结构
//实现简单，仅实现其中数组查找

//返回元素所在下标,默认T重载了==运算符
template<class T=int>
int Search_Seq(std::vector<T> ST, T key)
{
	for (int i = 0; i < ST.size(); i++)
	{
		//比较
		if(ST[i]==key)
		{
			//直接返回
			return i;
		}
	}

	//查找失败返回-1
	return -1;
}

template<class T = int>
int Search_Seq(T* ST,int n, T key)
{
	for (int i = 0; i < n; i++)
	{
		//比较
		if (ST[i] == key)
		{
			//直接返回
			return i;
		}
	}
	//查找失败返回-1
	return -1;
}

//通过为表引入一个“虚拟＂记录key，并且每次前进步长为二
//通过减少比较次数，能提高算法S的查找效率
template<class T = int>
int Search_Seq_modify(std::vector<T> ST, T key)
{
	//放入虚拟记录
	ST.push_back(key);

	int i = 0;
	while (1)
	{
		if (ST[i] == key)return i;
		if (ST[i + 1] != key)
		{
			i = i + 2;
		}
		else
		{
			i++;
		}
	}

	if(i==ST.size())
	{
		//查找失败返回-1
		return -1;
	}
	else
	{
		return i;
	}
}



//二分查找（英语：binary search），也称折半搜索（英语：half-interval search）,O(logn)
//折半查找要求线性表必须采用顺序存储结构， 而且表中元素按关键字有序排列
//假设有序表是递增有序，并且不是链式结构

// target 是在一个在左闭右闭的区间里，也就是[left, right] 
//闭区间里，while (left <= right) 要使用 <= ，因为left == right是有意义的
//if (nums[middle] > target) right 要赋值为 middle - 1，因为当前这个nums[middle]一定不是target
template<class T=int>
int Binary_Search(T* a, int left,int right, T key)
{
	int mid;
	
	//循坏搜索
	while (left <= right)
	{
		//防止溢出 等同于(left + right) / 2
		mid = left + ((right - left) >> 1);
	
		if (key < a[mid])//大于转为右区间
		{

			right = mid - 1;
		}
		else if (a[mid] < key)//小于转为左区间
		{
			left = mid + 1;
		}
		else//找到键值
		{
			return mid;
		}
	}

	//未找到
	return -1;
}


//定义 target 是在一个在左闭右开的区间里，也就是[left, right) ，那么二分法的边界处理方式则截然不同。
//while (left < right)，这里使用 < , 因为left == right在区间[left, right)是没有意义的
//if (nums[middle] > target) right 更新为 middle，因为当前nums[middle]不等于target
template<class T=int>
int Binary_Search(T* a, int n, T key)
{
	int left = 0;
	int right = n;

	//循坏搜索
	while (left < right)
	{
		int mid = left + ((right - left) >> 1);
		
		if (key < a[mid])//大于转为右区间
		{

			right = mid;
		}
		else if (a[mid] < key)//小于转为左区间
		{
			left = mid + 1;
		}
		else//找到键值
		{
			return mid;
		}
	}

	// 未找到目标值
	return -1;
}

//闭区间递归实现二分查找
template<class T = int>
int Binary_Search_Recursive(T* a, int left, int right, T key)
{
	if (left > right) {
		return -1; // 区间为空，未找到
	}

	int mid = left + ((right - left) >> 1); // 计算中间索引，防止溢出

	if (key < a[mid]) {
		// 在左区间查找
		return Binary_Search_Recursive(a, left, mid - 1, key);
	}
	else if (a[mid] < key) {
		// 在右区间查找
		return Binary_Search_Recursive(a, mid + 1, right, key);
	}
	else {
		// 找到目标值
		return mid;
	}
}

// 左闭右开递归实现 [left, right)
template<class T = int>
int Binary_Search_Recursive_Open(T* a, int left, int right, T key)
{
	if (left >= right) {
		return -1; // 区间为空，未找到
	}

	int mid = left + ((right - left) >> 1); // 防止溢出

	if (key < a[mid]) {
		return Binary_Search_Recursive_Open(a, left, mid, key); // 在左区间查找
	}
	else if (a[mid] < key) {
		return Binary_Search_Recursive_Open(a, mid + 1, right, key); // 在右区间查找
	}
	else {
		return mid; // 找到目标值
	}
}

//拓展，理解
template<class T=int>
class BinarySearcher
{
private:
	const T* arrayStart; // 数组起始位置
	std::function<int(const T*, const T*)> compare; // 比较函数

public:
	// 构造函数，初始化数组和比较函数
	BinarySearcher(const T* start, std::function<int(const T*, const T*)> comp = nullptr): arrayStart(start), compare(comp) 
	{
		if (!compare)
		{
			// 默认比较函数：按值比较
			compare = [](const T* a, const T* b) {
				return (*a < *b) ? -1 : ((*a > *b) ? 1 : 0);
			};
		}
	}

	// 查找首个不小于目标值的元素地址
	int lower(const T* target, const T* current) const 
	{
		// 如果当前元素的前一个值比目标值小，且当前值也比目标值小，则继续向右查找
		if ((current == arrayStart || compare(target, current - 1) > 0) && compare(target, current) > 0) 
		{
			return 1; // 指示继续向右查找
		}
		// 如果当前元素的前一个值不大于目标值，则继续向左查找
		else if (current != arrayStart && compare(target, current - 1) <= 0) 
		{
			return -1; // 指示继续向左查找
		}
		// 当前值是首个不小于目标值的元素
		else 
		{
			return 0; // 查找成功
		}
	}

	// 查找首个大于目标值的元素地址
	int upper(const T* target, const T* current) const 
	{
		// 如果当前元素的前一个值不小于目标值，且当前值也不小于目标值，则继续向右查找
		if ((current == arrayStart || compare(target, current - 1) >= 0) && compare(target, current) >= 0) 
		{
			return 1; // 指示继续向右查找
		}
		// 如果当前元素的前一个值小于目标值，则继续向左查找
		else if (current != arrayStart && compare(target, current - 1) < 0) 
		{
			return -1; // 指示继续向左查找
		}
		// 当前值是首个大于目标值的元素
		else {
			return 0; // 查找成功
		}
	}
};

//分块查找，又称为索引顺序查找
//在此查找法中，除表本身以外，尚需建立一个 “索引表”。
//对每个子表（或称块）建立一个索引项，其中包括两项内容：
//关键字项（其值为该子表内的最大关键字）和指针项（指示该子表的第一个记录在表中位置）。
//索引表按关键字有序，则表或者有序或者分块有序
//由于块内是无序的，故插入和删除比较容易，无需进行大量移动。

//过程
//先将key依次和索引表中各最大关键字进行比较，确定待查记录所在的块（子表）
//从该块的指针项（指示该子表的第一个记录在表中位置）顺序查找
//默认无序
//不考虑实现



//一致对半查找，
//譬如仅使用三个指针(s、门和e)中的两个。
//其具体思路是，使用当前位置i和它的变化率x,在每次不相等的比较之后，可置i<-i土x和x<-x/2(近似地）。
// 算法U之所以被称为是一致的，
//其原因是在第K层上的一个结点的编号与在第K - l层上其父结点的编号之差的绝对值，
//对于第k层上的所有结点均有一致的常数x。

//构建辅助数组DELTA记录每次区间数量m的值
std::vector<int> cal_delta(int n)
{
	std::vector<int> delta; // 保存步长
	int k = int(log2(n)) + 1; // 计算层数
	int temp = 1;

	for (int i = 0; i < k; i++)
	{
		delta.push_back((n + temp) / (temp * 2)); // 计算步长
		temp *= 2; // 更新 temp
	}

	/*for (const auto i : delta)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	return delta; // 返回步长数组
}

template<class T = int>
int cbiSearch(T* a, int n, int key)
{
	if (n < 1)return -1; // 空数组，直接返回

	if (a[0] == key)return 0; // 特殊情况：第一个元素就是目标

	std::vector<int> Delta = cal_delta(n); // 生成步长数组
	int i = n / 2;
	int j = 1;        // 当前步长索引

	while (key != a[i]) // 循环直到找到 key
	{
		if (key < a[i]) // key 在当前元素左侧
		{
			if ( j >= Delta.size()|| Delta[j] == 0 ) return -1; // 步长为 0，无法再分割
			else
			{
				i -= Delta[j]; // 左移
				j++;           // 步长递减
			}
		}
		if (a[i] < key) // key 在当前元素右侧
		{
			if (j >= Delta.size() || Delta[j] == 0)return -1; // 步长为 0，无法再分割
			else
			{
				i += Delta[j]; // 右移
				j++;           // 步长递减
			}
		}
	}
	return i; // 找到目标，返回下标
}

//斐波那契(黄金分割法）搜索（Fibonacci Search)（,又称为斐波那契查找
//在二分搜索的基础上，根据斐波那契数列分割，而不是简单的二分
//前提是待查找的查找表必须顺序存储并且有序

//数列从坐标1开始计数
//构造辅助数组，即斐波那契数列，数列生成到大于等于n
std::vector<int> Fib_arr(int n)
{
	std::vector<int> Fib;
	//初始化
	Fib.push_back(0);
	Fib.push_back(1);

	for (int i = 2;; i++)
	{
		int next = Fib[i - 1] + Fib[i - 2];
		Fib.push_back(next);
		if (next - 1 >= n) break;
	}

	return Fib;
}

template<class T=int>
int Fibonacci_Search(T* a,int n,T key)
{
	//空表
	if (n < 1)return -1;

	//初始化
	int left = 0;
	int right = n - 1;

	//得到辅助数列
	std::vector<int> F = Fib_arr(n);
	int k = F.size()-1;

	//如果a数组不足F[k]-1，则重复增加a的最后一个数直到长度等于F[k]-1
	std::vector<T> temp{ a,a+n };

	//一次性调整 temp 的大小来提高效率
	temp.resize(F[k] - 1, temp[n - 1]);


	//查找，注意这里实现查找区间左边比右边大
	//即如果当前区间为F[k]-1=F[k-1]-1 + F[k-2]-1 + 1;最后一个1的位置给mid
	//左区间为F[k-1]-1, 右区间为F[k-2]-1
	while (left <= right)
	{
		// mid 由左边界和 F[k-1] 决定，确保不越界,但是正常情况下不会越界 
		int mid = std::min(left + F[k - 1] - 1, right);

		if (key < temp[mid])  // 如果 key 在左区间
		{
			right = mid - 1;  // 更新右边界
			k -= 1;          // 更新斐波那契索引，左区间长度为 F[k-1]
		}
		else if (temp[mid] < key)  // 如果 key 在右区间
		{
			left = mid + 1;  // 更新左边界
			k -= 2;          // 更新斐波那契索引，右区间长度为 F[k-2]
		}
		else  // 找到目标值
		{
			// 如果是补充值，则返回原数组最后一个元素
			return mid < n ? mid : n - 1;  
		}
	}

	//未找到
	return -1;
}


//插值查找
//基本原理是根据要查找的值在有序数组中的大致位置进行估计，以此来缩小搜索范围
//通过数据的分布情况来预测目标值的位置，特别适用于有序且均匀分布的数据集
template<class T=int>
int InterPolation_Search(T* a, int n, T key)
{
	if (n < 1)return -1;

	//初始化
	int left = 0;
	int right = n - 1;
	//插值
	int pos = INT_MAX;
	//迭代
	while (left <= right&&a[left]!=a[right])//防止除以零
	{
		// 使用插值公式计算估计位置,此处和二分查找不同
		pos = left + (((key - a[left]) * (right - left)) / (a[right] - a[left]));

		// 越界检查
		if (pos < left || pos > right) return -1;
		
		if (key < a[pos])
		{
			right = pos - 1;
		}
		else if (a[pos] < key)
		{
			left = pos + 1;
		}
		else
		{
			return pos;
		}

	}

	// 特殊情况：剩余单个元素时检查是否匹配
	return (a[left] == key) ? left : -1;
}