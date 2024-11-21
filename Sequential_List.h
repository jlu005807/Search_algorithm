#pragma once
//�ڲ��ұ����֯��ʽ�У����Ա�����򵥵�һ��
//��˳����У���������������������

#include<iostream>
#include<functional>
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
class bsearch
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

//����
//�Ƚ�key���κ��������и����ؼ��ֽ��бȽϣ�ȷ�������¼���ڵĿ飨�ӱ�
//�Ӹÿ��ָ���ָʾ���ӱ�ĵ�һ����¼�ڱ���λ�ã�˳�����
//������ʵ��