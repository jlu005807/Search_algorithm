#pragma once
#include<iostream>
#include<vector>
//���ü�������Ķ�������Ϊ���ұ����֯��ʽ���ڴ˽�����ͳ��Ϊ����

//���������� (Binary Sort Tree) �ֳƶ��������
//���������գ��������������н���ֵ��Сǧ���ĸ�����ֵ
//���������գ��������������н���ֵ����ǧ���ĸ�����ֵ
//�� ������Ҳ�ֱ�Ϊ����������

//�������һ�ö�����ʱ���Եõ�һ�����ֵ��������������

template<class T=int>
class Tree
{
public:
	//������
	T data;//������==�������<�����
	//��������
	Tree* lchild;
	Tree* rchild;

	Tree() = default;
	Tree(T key,Tree* left=nullptr, Tree* right=nullptr):data(key),lchild(left),rchild(right){ }

};

//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
template<class T=int>
Tree<T>* SearchBiSortTree(Tree<T>* root, T key)
{
	//����������Ϊ�գ������ʧ�ܣ����ؿ�ָ��
	if (!root)return nullptr;

	//key��ǧT->data.key, ����ҳɹ������ظ�����ַ
	if (root->data == key)
	{
		return root;
	}
	else if(key<root->data)//keyСǧT->data.key, ��ݹ����������
	{
		return SearchBiTree(root->lchild,key)
	}
	else//key��ǧT->data.key, ��ݹ����������
	{
		return SearchBiTree(root->rchild, key)
	}
}


//��һ���ؼ���ֵΪkey�Ľ��*S���뵽����������
//ע�⴫�����ָ��
template<class T=int>
void InsertBiSortTree(Tree<T>*& root, T key)
{
	//������������T�в����ڹؼ��ֵ�ǧe.key������Ԫ��ʱ,������Ԫ��
	if (!root)
	{
		Tree<T>* temp = Tree<T>(key);
		root=temp
	}
	else if (key < root->data)//��*S����������
	{
		InsertBiSortTree(root->lchild, key);
	}
	else if (root->data < key)//��*S����������
	{
		InsertBiSortTree(root->rchild, key);
	}
	else//���˵��root������ͬ�ؼ��ֵĽ��
	{
		return;
	}
}

//�����������Ĵ���
template<class T=int>
Tree<T>* CreatBST(T STOP)
{
	//��ʼ��
	Tree<T>* tree = nullptr;

	T temp;
	std::cin >> temp;
	
	//���������������־
	while (temp != STOP)
	{
		//���ò��뺯��
		InsertBiSortTree(tree, temp);
		std::cin >> temp;
	}

	return tree;
}

//�����������Ĵ���
template<class T = int>
Tree<T>* CreatBST(std::vector<T> nums)
{
	//��ʼ��
	Tree<T>* tree = nullptr;

	for (const auto& key : nums)
	{
		InsertBiSortTree(root, key);
	}

	return tree;
}

//��������������ɵ�������
template<class T=int> 
std::vector<T> CreatSortArray(Tree<T>* root)
{
	//��ʼ��
	std::vector<T> a;

	//����,���ж�Ҳ����
	if (!root)return a;

	//��������ջ
	std::vector<Tree<T>*> stack;

	//��������ָ��
	Tree<T>* current = root;

	//��ջ���ջ��������нڵ�δ����
	while (current || !stack.empty())
	{
		//������ָ�뻹δ�գ���ջ
		if (current)
		{
			stack.push_back(current);

			//תΪ������
			current = current->lchild;
		}
		else//����ָ��Ϊ�գ�����
		{
			current = stack.back();
			stack.pop_back();

			//����ǰ�ڵ�
			std::cout << current->data << " ";
			a.push_back(current->data);

			//תΪ������
			current = current->rchild;
		}
	}

	return a;
}


//������������ɾ��
//��ɾ���Ľ������Ƕ����������е��κν��
// ɾ������Ҫ������λ�ò�ͬ�޸���˫�׽�㼰��ؽ���ָ�룬�Ա��ֶ���������������
template<class T=int>
void DeleteBST(Tree<T>*& root, T key)//��Ϊ����ɾ�����ڵ㣬���Դ������ָ��
{
	//����
	if (!root)return;

	//��ʼ��,Ŀ�����Ŀ��ڵ�ĸ��ڵ��Ա����
	Tree<T>* p = root;
	Tree<T>* pre = nullptr;
	
	//����
	while (p)
	{
		//�ҵ��ؼ��ֵ���key�Ľ��* p, ����ѭ��
		if (p->data == key)break;

		//ǰ��
		pre = p;
		//�ж������ƻ�������
		p = key < p->data ? p->lchild : p->rchild;

	}
	
	//�Ҳ���
	if (!p)return;

	//�����������

	//q��¼s��ǰ��
	Tree<T>* q = p;
	Tree<T>* s = p->rchild;

	//��ɾ���*p��������������
	if (p->lchild && p->rchild)
	{
		
		//��*p���������м���������ǰ����㣬�������½��Ҳ�ǵ�ǰ�ڵ�Ϊ�������ڵ�
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}

		//sָ��ɾ���� ��ǰ��",�����ڵ��滻��ɾ���
		p->data = s->data;

		//�ؽ�* q��������
		if (q != p)//����qδ�ƶ�
		{
			//s��������ֵ���ɴ�����ǰ��������s��Ϊ���ڵ�һ��û����������
			q->rchild = s->lchild;
		}
		else//�ؽ�*q��������,δ�ƶ���q���Ǳ�s�滻��p
		{
			q->lchild = s->lchild;
		}

		delete s;
		return;
	}
	else if (!p->rchild)//��ɾ���*p���������� ֻ���ؽ���������
	{
		q=p;
		p = p->lchild;
	}
	else if (p->lchild)//��ɾ���*p���������� ֻ���ؽ���������
	{
		q = p;
		p = p->rchild;
	}

	//��p��ָ�������ҽӵ���˫�׽��*f��Ӧ��λ��
	
	//��ɾ���Ϊ���ڵ�
	if (!pre)root = p;
	else if (q == pre->lchild)//��ɾ���Ϊǰ����������
	{
		//�ҽӵ�*f��������λ��
		pre->lchild = p;
	}
	else //��ɾ���Ϊǰ����������
	{
		pre->rchild = p;
	}

	delete q;

	return;
}

//�������������
template<class T=int>
void ClearBST(Tree<T>*& root)
{
	//�������ߵ�ĩβ
	if (!root)
	{
		return;
	}

	//�ݹ�����
	ClearBST(root->lchild);
	ClearBST(root->rchild);

	//�ͷſռ䲢�ÿ�
	delete root;
	root = nullptr;
}