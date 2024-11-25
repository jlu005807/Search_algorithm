#pragma once
#include<iostream>
#include<vector>
//采用几种特殊的二叉树作为查找表的组织形式，在此将它们统称为树表。

//二叉排序树 (Binary Sort Tree) 又称二叉查找树
//左子树不空，则左子树上所有结点的值均小千它的根结点的值
//右子树不空，则右子树上所有结点的值均大千它的根结点的值
//左、 右子树也分别为二叉排序树

//中序遍历一棵二叉树时可以得到一个结点值递增的有序序列

template<class T=int>
class Tree
{
public:
	//数据项
	T data;//重载了==运算符和<运算符
	//左右子树
	Tree* lchild;
	Tree* rchild;

	Tree() = default;
	Tree(T key,Tree* left=nullptr, Tree* right=nullptr):data(key),lchild(left),rchild(right){ }

};

//在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素
template<class T=int>
Tree<T>* SearchBiSortTree(Tree<T>* root, T key)
{
	//二叉排序树为空，则查找失败，返回空指针
	if (!root)return nullptr;

	//key等千T->data.key, 则查找成功，返回根结点地址
	if (root->data == key)
	{
		return root;
	}
	else if(key<root->data)//key小千T->data.key, 则递归查找左子树
	{
		return SearchBiTree(root->lchild,key)
	}
	else//key大千T->data.key, 则递归查找右子树
	{
		return SearchBiTree(root->rchild, key)
	}
}


//将一个关键字值为key的结点*S插入到二叉排序树
//注意传入二级指针
template<class T=int>
void InsertBiSortTree(Tree<T>*& root, T key)
{
	//当二叉排序树T中不存在关键字等千e.key的数据元素时,则插入该元素
	if (!root)
	{
		Tree<T>* temp = Tree<T>(key);
		root=temp
	}
	else if (key < root->data)//将*S插入左子树
	{
		InsertBiSortTree(root->lchild, key);
	}
	else if (root->data < key)//将*S插入右子树
	{
		InsertBiSortTree(root->rchild, key);
	}
	else//相等说明root存在相同关键字的结点
	{
		return;
	}
}

//二叉排序树的创建
template<class T=int>
Tree<T>* CreatBST(T STOP)
{
	//初始化
	Tree<T>* tree = nullptr;

	T temp;
	std::cin >> temp;
	
	//不等于输入结束标志
	while (temp != STOP)
	{
		//利用插入函数
		InsertBiSortTree(tree, temp);
		std::cin >> temp;
	}

	return tree;
}

//二叉排序树的创建
template<class T = int>
Tree<T>* CreatBST(std::vector<T> nums)
{
	//初始化
	Tree<T>* tree = nullptr;

	for (const auto& key : nums)
	{
		InsertBiSortTree(root, key);
	}

	return tree;
}

//利用中序遍历生成递增序列
template<class T=int> 
std::vector<T> CreatSortArray(Tree<T>* root)
{
	//初始化
	std::vector<T> a;

	//空树,不判断也可以
	if (!root)return a;

	//建立工作栈
	std::vector<Tree<T>*> stack;

	//建立工作指针
	Tree<T>* current = root;

	//当栈不空或者依旧有节点未访问
	while (current || !stack.empty())
	{
		//当工作指针还未空，入栈
		if (current)
		{
			stack.push_back(current);

			//转为左子树
			current = current->lchild;
		}
		else//工作指针为空，回溯
		{
			current = stack.back();
			stack.pop_back();

			//处理当前节点
			std::cout << current->data << " ";
			a.push_back(current->data);

			//转为右子树
			current = current->rchild;
		}
	}

	return a;
}


//二叉排序树的删除
//被删除的结点可能是二叉排序树中的任何结点
// 删除结点后，要根据其位置不同修改其双亲结点及相关结点的指针，以保持二叉排序树的特性
template<class T=int>
void DeleteBST(Tree<T>*& root, T key)//因为可能删除根节点，所以传入二级指针
{
	//空树
	if (!root)return;

	//初始化,目标结点和目标节点的父节点以便查找
	Tree<T>* p = root;
	Tree<T>* pre = nullptr;
	
	//查找
	while (p)
	{
		//找到关键字等于key的结点* p, 结束循环
		if (p->data == key)break;

		//前移
		pre = p;
		//判断往左移还是右移
		p = key < p->data ? p->lchild : p->rchild;

	}
	
	//找不到
	if (!p)return;

	//考虑三种情况

	//q记录s的前驱
	Tree<T>* q = p;
	Tree<T>* s = p->rchild;

	//被删结点*p左右子树均不空
	if (p->lchild && p->rchild)
	{
		
		//在*p的左子树中继续查找其前驱结点，即最右下结点也是当前节点为根的最大节点
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}

		//s指向被删结点的 “前驱",以最大节点替换被删结点
		p->data = s->data;

		//重接* q的右子树
		if (q != p)//避免q未移动
		{
			//s左子树的值依旧大于其前驱，并且s作为最大节点一定没有右子树了
			q->rchild = s->lchild;
		}
		else//重接*q的左子树,未移动则q即是被s替换的p
		{
			q->lchild = s->lchild;
		}

		delete s;
		return;
	}
	else if (!p->rchild)//被删结点*p无右子树， 只需重接其左子树
	{
		q=p;
		p = p->lchild;
	}
	else if (p->lchild)//被删结点*p无左子树， 只需重接其右子树
	{
		q = p;
		p = p->rchild;
	}

	//将p所指的子树挂接到其双亲结点*f相应的位置
	
	//被删结点为根节点
	if (!pre)root = p;
	else if (q == pre->lchild)//被删结点为前驱的左子树
	{
		//挂接到*f的左子树位置
		pre->lchild = p;
	}
	else //被删结点为前驱的左子树
	{
		pre->rchild = p;
	}

	delete q;

	return;
}

//清除二叉排序树
template<class T=int>
void ClearBST(Tree<T>*& root)
{
	//空树或者到末尾
	if (!root)
	{
		return;
	}

	//递归清理
	ClearBST(root->lchild);
	ClearBST(root->rchild);

	//释放空间并置空
	delete root;
	root = nullptr;
}