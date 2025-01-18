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

	// ά��������Ϣ����߶ȣ��ڵ�������

	int size;   // ��ǰ�ڵ�Ϊ����������С
	int count;  // ��ǰ�ڵ���ظ�����

	Tree() = default;
	Tree(T key,Tree* left=nullptr, Tree* right=nullptr):size(1),count(1),data(key),lchild(left),rchild(right){ }

};


template<class T=int>
class BiSortTree
{
	//�������
	void InOrderTraveral(Tree<T>* root)
	{
		if (!root)return;

		InOrderTraveral(root->lchild);

		std::cout << root->data << " ";

		InOrderTraveral(root->rchild);
	}

	//���Ҷ����������йؼ�����С�Ľڵ�
	Tree<T>* findMin(Tree<T>* root)
	{
		if (root == nullptr)return nullptr;

		while (root->lchild != nullptr)
		{
			root = root->lchild;
		}

		return root;
	}

	//���Ҷ����������йؼ������Ľڵ�
	Tree<T>* findMax(Tree<T>* root)
	{
		if (root == nullptr)return nullptr;

		while (root->rchild != nullptr)
		{
			root = root->rchild;
		}

		return root;
	}



	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
	Tree<T>* SearchBiSortTree(Tree<T>* root, T key)
	{
		//����������Ϊ�գ������ʧ�ܣ����ؿ�ָ��
		if (!root)return nullptr;

		//key��ǧT->data.key, ����ҳɹ������ظ�����ַ
		if (root->data == key)
		{
			return root;
		}
		else if (key < root->data)//keyСǧT->data.key, ��ݹ����������
		{
			return SearchBiSortTree(root->lchild, key);
		}
		else//key��ǧT->data.key, ��ݹ����������
		{
			return SearchBiSortTree(root->rchild, key);
		}
	}


	//������������T�в����ڹؼ��ֵ�ǧe.key������Ԫ��ʱ,������Ԫ��
	//ע�⴫�����ָ��
	void InsertBiSortTree(Tree<T>*& root, T key)
	{
		//����ֱ�ӽ�����Ϊ���ڵ�
		if (!root)
		{
			Tree<T>* temp = new Tree<T>(key);
			root = temp;
		}
		else if (key < root->data)//��*S����������
		{
			InsertBiSortTree(root->lchild, key);
		}
		else if (root->data < key)//��*S����������
		{
			InsertBiSortTree(root->rchild, key);
		}
		else//���˵��root������ͬ�ؼ��ֵĽ��,����++
		{
			root->count++;
			return;
		}

		//����size,���Ľڵ����������������ͼ��ϱ������
		root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);  // ���½ڵ��������С
		return;
	}

	//�����������Ĵ���
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
	Tree<T>* CreatBST(std::vector<T> nums)
	{
		//��ʼ��
		Tree<T>* tree = nullptr;

		for (const auto& key : nums)
		{
			InsertBiSortTree(tree, key);
		}

		return tree;
	}

	//��������������ɵ�������
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
	//ɾ������Ҫ������λ�ò�ͬ�޸���˫�׽�㼰��ؽ���ָ�룬�Ա��ֶ���������������
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

		//count����1
		if (p->count > 1)
		{
			p->count--;
		}
		else
		{
			//�����������

		    //q��¼s��ǰ��
			Tree<T>* q = p;
			Tree<T>* s = p->rchild;

			//��ɾ���*p��������������
			if (p->lchild && p->rchild)
			{

				//��*p���������м���������ǰ����㣬�������½��Ҳ�����������ڵ����Դ��汻ɾ���ڵ�
				//��������������С�ڵ����
				while (s->rchild)
				{
					q = s;
					s = s->rchild;
				}

				//sָ��ɾ���� ��ǰ��",�����ڵ��滻��ɾ���
				p->data = s->data;

				//�ؽ�*q��������
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
				q = p;
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
		}
		
		//ά��size
		root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);  // ���½ڵ��������С

		return;
	}

	//�ݹ�汾��ע�⴫�����ָ��
	void remove(Tree<T>*& root,T key)
	{
		//�����������Ҳ���
		if (root == nullptr)
		{
			return;
		}

		if (root->data < key)
		{
			remove(root->rchild, key);
		}
		else if (key < root->data)
		{
			remove(root->lchild, key);
		}
		else//�ҵ�
		{
			if (root->count > 1) {
				root->count--;
			}
			else
			{
				//������Ϊ��
				if (root->lchild == nullptr)
				{
					Tree<T>* temp = root;
					root = root->rchild;
					delete temp;
					return;
				}
				//������Ϊ��
				else if (root->rchild == nullptr) 
				{
					Tree<T>* temp = root;
					root = root->lchild;
					delete temp;
					return;
				}
				else
				{
					//�ҵ��̳��ߣ������������ڵ������������С�ڵ�
					Tree<T>* successor = findMax(root->lchild);
					root->data = successor->data;
					root->count = successor->count;

					// �� successor->count > 1ʱ��ҲӦ��ɾ���ýڵ㣬����
		            // ������ɾ��ֻ������ظ�����
					successor->count = 1;
					remove(root->rchild, successor->data);
				}
			}
		}
		// ����ά��size����д�� --root->size;
		// ����Ϊvalue���ܲ������У��Ӷ�����δ����ɾ��
		root->size = root->count + (root->left ? root->left->size : 0) +(root->right ? root->right->size : 0);
		return;
	}

	//������Ԫ�ص�����
	//��������Ϊ������Ԫ������������һ����ͬԪ��֮ǰ�����ĸ�����һ
	//����һ��Ԫ�ص����������ȴӸ��ڵ��������Ԫ�أ�
	int QueryRank(Tree<T>* root, T key)
	{
		if (root == nullptr)
		{
			return 0;//��ʾ�޴�Ԫ��
		}
		
		if (root->data == key)//�ҵ�key
		{
			return (root->lchild ? root->lchild->size : 0) + 1;
		}
		else if (key < root->data)//����������
		{
			return QueryRank(root->lchild, key);
		}
		//�����������𰸼�������ӽڵ�����ӵ�ǰ�ڵ��ظ�����������
        //���𰸼����յ�������������С��һ
		else
		{
			return QueryRank(root->rchild, key) + (root->lchild ? root->lchild->size : 0) + root->count;
		}
	}


	//�������������
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
};