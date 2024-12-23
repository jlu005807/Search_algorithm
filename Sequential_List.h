#pragma once
//�ڲ��ұ����֯��ʽ�У����Ա�����򵥵�һ��
//��˳����У���������������������

#include<iostream>
#include<functional>
#include<cmath>
#include<climits>
#include<vector>

//˳�����
//�ӱ��һ�˿�ʼ�����ν���¼�Ĺؼ��ֺ͸���ֵ���бȽϣ�Ѱ�ҹؼ���
//�����������Ա��˳��洢�ṹ��������ǧ���Ա����ʽ�洢�ṹ
//ʵ�ּ򵥣���ʵ�������������

//����Ԫ�������±�,Ĭ��T������==�����
template<class T=int>
int Search_Seq(std::vector<T> ST, T key)
{
	for (int i = 0; i < ST.size(); i++)
	{
		//�Ƚ�
		if(ST[i]==key)
		{
			//ֱ�ӷ���
			return i;
		}
	}

	//����ʧ�ܷ���-1
	return -1;
}

template<class T = int>
int Search_Seq(T* ST,int n, T key)
{
	for (int i = 0; i < n; i++)
	{
		//�Ƚ�
		if (ST[i] == key)
		{
			//ֱ�ӷ���
			return i;
		}
	}
	//����ʧ�ܷ���-1
	return -1;
}

//ͨ��Ϊ������һ�������⣢��¼key������ÿ��ǰ������Ϊ��
//ͨ�����ٱȽϴ�����������㷨S�Ĳ���Ч��
template<class T = int>
int Search_Seq_modify(std::vector<T> ST, T key)
{
	//���������¼
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
		//����ʧ�ܷ���-1
		return -1;
	}
	else
	{
		return i;
	}
}



//���ֲ��ң�Ӣ�binary search����Ҳ���۰�������Ӣ�half-interval search��,O(logn)
//�۰����Ҫ�����Ա�������˳��洢�ṹ�� ���ұ���Ԫ�ذ��ؼ�����������
//����������ǵ������򣬲��Ҳ�����ʽ�ṹ

// target ����һ��������ұյ������Ҳ����[left, right] 
//�������while (left <= right) Ҫʹ�� <= ����Ϊleft == right���������
//if (nums[middle] > target) right Ҫ��ֵΪ middle - 1����Ϊ��ǰ���nums[middle]һ������target
template<class T=int>
int Binary_Search(T* a, int left,int right, T key)
{
	int mid;
	
	//ѭ������
	while (left <= right)
	{
		//��ֹ��� ��ͬ��(left + right) / 2
		mid = left + ((right - left) >> 1);
	
		if (key < a[mid])//����תΪ������
		{

			right = mid - 1;
		}
		else if (a[mid] < key)//С��תΪ������
		{
			left = mid + 1;
		}
		else//�ҵ���ֵ
		{
			return mid;
		}
	}

	//δ�ҵ�
	return -1;
}


//���� target ����һ��������ҿ��������Ҳ����[left, right) ����ô���ַ��ı߽紦��ʽ���Ȼ��ͬ��
//while (left < right)������ʹ�� < , ��Ϊleft == right������[left, right)��û�������
//if (nums[middle] > target) right ����Ϊ middle����Ϊ��ǰnums[middle]������target
template<class T=int>
int Binary_Search(T* a, int n, T key)
{
	int left = 0;
	int right = n;

	//ѭ������
	while (left < right)
	{
		int mid = left + ((right - left) >> 1);
		
		if (key < a[mid])//����תΪ������
		{

			right = mid;
		}
		else if (a[mid] < key)//С��תΪ������
		{
			left = mid + 1;
		}
		else//�ҵ���ֵ
		{
			return mid;
		}
	}

	// δ�ҵ�Ŀ��ֵ
	return -1;
}

//������ݹ�ʵ�ֶ��ֲ���
template<class T = int>
int Binary_Search_Recursive(T* a, int left, int right, T key)
{
	if (left > right) {
		return -1; // ����Ϊ�գ�δ�ҵ�
	}

	int mid = left + ((right - left) >> 1); // �����м���������ֹ���

	if (key < a[mid]) {
		// �����������
		return Binary_Search_Recursive(a, left, mid - 1, key);
	}
	else if (a[mid] < key) {
		// �����������
		return Binary_Search_Recursive(a, mid + 1, right, key);
	}
	else {
		// �ҵ�Ŀ��ֵ
		return mid;
	}
}

// ����ҿ��ݹ�ʵ�� [left, right)
template<class T = int>
int Binary_Search_Recursive_Open(T* a, int left, int right, T key)
{
	if (left >= right) {
		return -1; // ����Ϊ�գ�δ�ҵ�
	}

	int mid = left + ((right - left) >> 1); // ��ֹ���

	if (key < a[mid]) {
		return Binary_Search_Recursive_Open(a, left, mid, key); // �����������
	}
	else if (a[mid] < key) {
		return Binary_Search_Recursive_Open(a, mid + 1, right, key); // �����������
	}
	else {
		return mid; // �ҵ�Ŀ��ֵ
	}
}

//��չ�����
template<class T=int>
class BinarySearcher
{
private:
	const T* arrayStart; // ������ʼλ��
	std::function<int(const T*, const T*)> compare; // �ȽϺ���

public:
	// ���캯������ʼ������ͱȽϺ���
	BinarySearcher(const T* start, std::function<int(const T*, const T*)> comp = nullptr): arrayStart(start), compare(comp) 
	{
		if (!compare)
		{
			// Ĭ�ϱȽϺ�������ֵ�Ƚ�
			compare = [](const T* a, const T* b) {
				return (*a < *b) ? -1 : ((*a > *b) ? 1 : 0);
			};
		}
	}

	// �����׸���С��Ŀ��ֵ��Ԫ�ص�ַ
	int lower(const T* target, const T* current) const 
	{
		// �����ǰԪ�ص�ǰһ��ֵ��Ŀ��ֵС���ҵ�ǰֵҲ��Ŀ��ֵС����������Ҳ���
		if ((current == arrayStart || compare(target, current - 1) > 0) && compare(target, current) > 0) 
		{
			return 1; // ָʾ�������Ҳ���
		}
		// �����ǰԪ�ص�ǰһ��ֵ������Ŀ��ֵ��������������
		else if (current != arrayStart && compare(target, current - 1) <= 0) 
		{
			return -1; // ָʾ�����������
		}
		// ��ǰֵ���׸���С��Ŀ��ֵ��Ԫ��
		else 
		{
			return 0; // ���ҳɹ�
		}
	}

	// �����׸�����Ŀ��ֵ��Ԫ�ص�ַ
	int upper(const T* target, const T* current) const 
	{
		// �����ǰԪ�ص�ǰһ��ֵ��С��Ŀ��ֵ���ҵ�ǰֵҲ��С��Ŀ��ֵ����������Ҳ���
		if ((current == arrayStart || compare(target, current - 1) >= 0) && compare(target, current) >= 0) 
		{
			return 1; // ָʾ�������Ҳ���
		}
		// �����ǰԪ�ص�ǰһ��ֵС��Ŀ��ֵ��������������
		else if (current != arrayStart && compare(target, current - 1) < 0) 
		{
			return -1; // ָʾ�����������
		}
		// ��ǰֵ���׸�����Ŀ��ֵ��Ԫ��
		else {
			return 0; // ���ҳɹ�
		}
	}
};

//�ֿ���ң��ֳ�Ϊ����˳�����
//�ڴ˲��ҷ��У����������⣬���轨��һ�� ����������
//��ÿ���ӱ���ƿ飩����һ����������а����������ݣ�
//�ؼ������ֵΪ���ӱ��ڵ����ؼ��֣���ָ���ָʾ���ӱ�ĵ�һ����¼�ڱ���λ�ã���
//�������ؼ�������������������߷ֿ�����
//���ڿ���������ģ��ʲ����ɾ���Ƚ����ף�������д����ƶ���

//����
//�Ƚ�key���κ��������и����ؼ��ֽ��бȽϣ�ȷ�������¼���ڵĿ飨�ӱ�
//�Ӹÿ��ָ���ָʾ���ӱ�ĵ�һ����¼�ڱ���λ�ã�˳�����
//Ĭ������
//������ʵ��



//һ�¶԰���ң�
//Ʃ���ʹ������ָ��(s���ź�e)�е�������
//�����˼·�ǣ�ʹ�õ�ǰλ��i�����ı仯��x,��ÿ�β���ȵıȽ�֮�󣬿���i<-i��x��x<-x/2(���Ƶأ���
// �㷨U֮���Ա���Ϊ��һ�µģ�
//��ԭ�����ڵ�K���ϵ�һ�����ı�����ڵ�K - l�����丸���ı��֮��ľ���ֵ��
//���ڵ�k���ϵ����н�����һ�µĳ���x��

//������������DELTA��¼ÿ����������m��ֵ
std::vector<int> cal_delta(int n)
{
	std::vector<int> delta; // ���沽��
	int k = int(log2(n)) + 1; // �������
	int temp = 1;

	for (int i = 0; i < k; i++)
	{
		delta.push_back((n + temp) / (temp * 2)); // ���㲽��
		temp *= 2; // ���� temp
	}

	/*for (const auto i : delta)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	return delta; // ���ز�������
}

template<class T = int>
int cbiSearch(T* a, int n, int key)
{
	if (n < 1)return -1; // �����飬ֱ�ӷ���

	if (a[0] == key)return 0; // �����������һ��Ԫ�ؾ���Ŀ��

	std::vector<int> Delta = cal_delta(n); // ���ɲ�������
	int i = n / 2;
	int j = 1;        // ��ǰ��������

	while (key != a[i]) // ѭ��ֱ���ҵ� key
	{
		if (key < a[i]) // key �ڵ�ǰԪ�����
		{
			if ( j >= Delta.size()|| Delta[j] == 0 ) return -1; // ����Ϊ 0���޷��ٷָ�
			else
			{
				i -= Delta[j]; // ����
				j++;           // �����ݼ�
			}
		}
		if (a[i] < key) // key �ڵ�ǰԪ���Ҳ�
		{
			if (j >= Delta.size() || Delta[j] == 0)return -1; // ����Ϊ 0���޷��ٷָ�
			else
			{
				i += Delta[j]; // ����
				j++;           // �����ݼ�
			}
		}
	}
	return i; // �ҵ�Ŀ�꣬�����±�
}

//쳲�����(�ƽ�ָ��������Fibonacci Search)��,�ֳ�Ϊ쳲���������
//�ڶ��������Ļ����ϣ�����쳲��������зָ�����Ǽ򵥵Ķ���
//ǰ���Ǵ����ҵĲ��ұ����˳��洢��������

//���д�����1��ʼ����
//���츨�����飬��쳲��������У��������ɵ����ڵ���n
std::vector<int> Fib_arr(int n)
{
	std::vector<int> Fib;
	//��ʼ��
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
	//�ձ�
	if (n < 1)return -1;

	//��ʼ��
	int left = 0;
	int right = n - 1;

	//�õ���������
	std::vector<int> F = Fib_arr(n);
	int k = F.size()-1;

	//���a���鲻��F[k]-1�����ظ�����a�����һ����ֱ�����ȵ���F[k]-1
	std::vector<T> temp{ a,a+n };

	//һ���Ե��� temp �Ĵ�С�����Ч��
	temp.resize(F[k] - 1, temp[n - 1]);


	//���ң�ע������ʵ�ֲ���������߱��ұߴ�
	//�������ǰ����ΪF[k]-1=F[k-1]-1 + F[k-2]-1 + 1;���һ��1��λ�ø�mid
	//������ΪF[k-1]-1, ������ΪF[k-2]-1
	while (left <= right)
	{
		// mid ����߽�� F[k-1] ������ȷ����Խ��,������������²���Խ�� 
		int mid = std::min(left + F[k - 1] - 1, right);

		if (key < temp[mid])  // ��� key ��������
		{
			right = mid - 1;  // �����ұ߽�
			k -= 1;          // ����쳲����������������䳤��Ϊ F[k-1]
		}
		else if (temp[mid] < key)  // ��� key ��������
		{
			left = mid + 1;  // ������߽�
			k -= 2;          // ����쳲����������������䳤��Ϊ F[k-2]
		}
		else  // �ҵ�Ŀ��ֵ
		{
			// ����ǲ���ֵ���򷵻�ԭ�������һ��Ԫ��
			return mid < n ? mid : n - 1;  
		}
	}

	//δ�ҵ�
	return -1;
}


//��ֵ����
//����ԭ���Ǹ���Ҫ���ҵ�ֵ�����������еĴ���λ�ý��й��ƣ��Դ�����С������Χ
//ͨ�����ݵķֲ������Ԥ��Ŀ��ֵ��λ�ã��ر������������Ҿ��ȷֲ������ݼ�
template<class T=int>
int InterPolation_Search(T* a, int n, T key)
{
	if (n < 1)return -1;

	//��ʼ��
	int left = 0;
	int right = n - 1;
	//��ֵ
	int pos = INT_MAX;
	//����
	while (left <= right&&a[left]!=a[right])//��ֹ������
	{
		// ʹ�ò�ֵ��ʽ�������λ��,�˴��Ͷ��ֲ��Ҳ�ͬ
		pos = left + (((key - a[left]) * (right - left)) / (a[right] - a[left]));

		// Խ����
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

	// ���������ʣ�൥��Ԫ��ʱ����Ƿ�ƥ��
	return (a[left] == key) ? left : -1;
}