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

	// 维护其他信息，如高度，节点数量等

	int size;   // 当前节点为根的子树大小
	int count;  // 当前节点的重复数量

	Tree() = default;
	Tree(T key,Tree* left=nullptr, Tree* right=nullptr):size(1),count(1),data(key),lchild(left),rchild(right){ }

};


template<class T=int>
class BiSortTree
{
	//中序遍历
	void InOrderTraveral(Tree<T>* root)
	{
		if (!root)return;

		InOrderTraveral(root->lchild);

		std::cout << root->data << " ";

		InOrderTraveral(root->rchild);
	}

	//查找二叉搜索树中关键词最小的节点
	Tree<T>* findMin(Tree<T>* root)
	{
		if (root == nullptr)return nullptr;

		while (root->lchild != nullptr)
		{
			root = root->lchild;
		}

		return root;
	}

	//查找二叉搜索树中关键词最大的节点
	Tree<T>* findMax(Tree<T>* root)
	{
		if (root == nullptr)return nullptr;

		while (root->rchild != nullptr)
		{
			root = root->rchild;
		}

		return root;
	}



	//在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素
	Tree<T>* SearchBiSortTree(Tree<T>* root, T key)
	{
		//二叉排序树为空，则查找失败，返回空指针
		if (!root)return nullptr;

		//key等千T->data.key, 则查找成功，返回根结点地址
		if (root->data == key)
		{
			return root;
		}
		else if (key < root->data)//key小千T->data.key, 则递归查找左子树
		{
			return SearchBiSortTree(root->lchild, key);
		}
		else//key大千T->data.key, 则递归查找右子树
		{
			return SearchBiSortTree(root->rchild, key);
		}
	}


	//当二叉排序树T中不存在关键字等千e.key的数据元素时,则插入该元素
	//注意传入二级指针
	void InsertBiSortTree(Tree<T>*& root, T key)
	{
		//空树直接将其作为根节点
		if (!root)
		{
			Tree<T>* temp = new Tree<T>(key);
			root = temp;
		}
		else if (key < root->data)//将*S插入左子树
		{
			InsertBiSortTree(root->lchild, key);
		}
		else if (root->data < key)//将*S插入右子树
		{
			InsertBiSortTree(root->rchild, key);
		}
		else//相等说明root存在相同关键字的结点,个数++
		{
			root->count++;
			return;
		}

		//处理size,根的节点数等于左右子树和加上本身个数
		root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);  // 更新节点的子树大小
		return;
	}

	//二叉排序树的创建
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
	Tree<T>* CreatBST(std::vector<T> nums)
	{
		//初始化
		Tree<T>* tree = nullptr;

		for (const auto& key : nums)
		{
			InsertBiSortTree(tree, key);
		}

		return tree;
	}

	//利用中序遍历生成递增序列
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
	//删除结点后，要根据其位置不同修改其双亲结点及相关结点的指针，以保持二叉排序树的特性
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

		//count大于1
		if (p->count > 1)
		{
			p->count--;
		}
		else
		{
			//考虑三种情况

		    //q记录s的前驱
			Tree<T>* q = p;
			Tree<T>* s = p->rchild;

			//被删结点*p左右子树均不空
			if (p->lchild && p->rchild)
			{

				//在*p的左子树中继续查找其前驱结点，即最右下结点也是左子树最大节点用以代替被删除节点
				//或者找右子树最小节点代替
				while (s->rchild)
				{
					q = s;
					s = s->rchild;
				}

				//s指向被删结点的 “前驱",以最大节点替换被删结点
				p->data = s->data;

				//重接*q的右子树
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
				q = p;
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
		}
		
		//维护size
		root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);  // 更新节点的子树大小

		return;
	}

	//递归版本，注意传入二级指针
	void remove(Tree<T>*& root,T key)
	{
		//空树，或者找不到
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
		else//找到
		{
			if (root->count > 1) {
				root->count--;
			}
			else
			{
				//左子树为空
				if (root->lchild == nullptr)
				{
					Tree<T>* temp = root;
					root = root->rchild;
					delete temp;
					return;
				}
				//右子树为空
				else if (root->rchild == nullptr) 
				{
					Tree<T>* temp = root;
					root = root->lchild;
					delete temp;
					return;
				}
				else
				{
					//找到继承者，即左子树最大节点或者右子树最小节点
					Tree<T>* successor = findMax(root->lchild);
					root->data = successor->data;
					root->count = successor->count;

					// 当 successor->count > 1时，也应该删除该节点，否则
		            // 后续的删除只会减少重复数量
					successor->count = 1;
					remove(root->rchild, successor->data);
				}
			}
		}
		// 继续维护size，不写成 --root->size;
		// 是因为value可能不在树中，从而可能未发生删除
		root->size = root->count + (root->left ? root->left->size : 0) +(root->right ? root->right->size : 0);
		return;
	}

	//求树中元素的排名
	//排名定义为将数组元素升序排序后第一个相同元素之前的数的个数加一
	//查找一个元素的排名，首先从根节点跳到这个元素，
	int QueryRank(Tree<T>* root, T key)
	{
		if (root == nullptr)
		{
			return 0;//表示无此元素
		}
		
		if (root->data == key)//找到key
		{
			return (root->lchild ? root->lchild->size : 0) + 1;
		}
		else if (key < root->data)//往左子树找
		{
			return QueryRank(root->lchild, key);
		}
		//若向右跳，答案加上左儿子节点个数加当前节点重复的数个数，
        //最后答案加上终点的左儿子子树大小加一
		else
		{
			return QueryRank(root->rchild, key) + (root->lchild ? root->lchild->size : 0) + root->count;
		}
	}


	//清除二叉排序树
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
};