
// BinaryTree - �������� ������.

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T id;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
};

template <typename T>
class BinaryTree
{
	Node <T>* root = nullptr;
	int size = 0;

public:
	BinaryTree(){}
	BinaryTree(T data)
	{
		Node<T>* node = new Node<T>{ data };
		root = node;
		size++;
	}

	void add(T data)
	{
		if (!size) BinaryTree(data);

		else{
			Node<T>* iter = root;
			Node<T>* node = new Node<T>{ data };
			while (true)
			{
				if (node->id > iter->id)          // (node > root)
				{
					if (!iter->right)             // (==nullptr)
					{
						iter->right = node;
						break;
					}
					else iter = iter->right;      // ��������� �� ������.
				}
				else if (!iter->left)
				{
					iter->left = node;
					break;
				}
				else iter=iter->left;
			}
			node->parent = iter;
		}
		size++;
	}

	//����� (�����������)
	void print(Node<T>* node = nullptr)
	{
		if (!node) node = root;
		cout << node->id << " ";
		if (node->left) print(node->left);
		if (node->right) print(node->right);
	}
	
	//����� (�� ��������)
	Node<T>* search(T data)
	{
		Node<T>* iter = root;                            
		while (true)
		{
			if (iter->id == data) return iter;            

			if (data > iter->id)
			{
			    if (!iter->right) return nullptr;
			    else iter = iter->right;
			}
			else
			{
				if (!iter->left) return nullptr;
				else iter = iter->left;
			}
		}
	}

	//�������� node (�� ��������)
	void remove(T data)
	{
		Node<T>* node = search(data);

		//// ���� node - ����
		//if (!node->left and !node->right)         
		//{
		//	if (node->parent->left == node)
		//		node->parent->left = nullptr;
		//	else
		//		node->parent->right = nullptr;
		//	delete node;
		//}
		////���� ��� �������� ����������
		//else if (!node->left){            
		//	if (node->parent->left == node)
		//		 node->parent->left = node->right;
		//	else node->parent->right = node->right;
		//	delete node;
		//}
		////���� ��� �������� ����������
		//else if (!node->right){          
		//	if (node->parent->left == node)
		//		 node->parent->left = node->left;
		//	else node->parent->right = node->left;
		//	delete node;
		//}

        //���� ��������� node ����� ���� �����������
		//else
		//{
			//���� ��������� ���� root
			if (node == root)
			{
				Node<T>* iter = node->right;   //������ ��� ������.
				while (iter->left != nullptr)  //����� ��������� �����, �� �����.
				{
					iter = iter->left;
				}
				Node<T>* tmp = node;           //������� ��������� ������.
				node = iter;
				if (!node->right)              //���� ��� right ����������.
					node->parent->left = nullptr;
				else                           //���� ���� right ���������.
					node->parent->left = node->right;

				root = node;
				node->left = tmp->left;
				node->right = tmp->right;
				node->left->parent = node;
				node->right->parent = node;
				node->parent = nullptr;
				delete tmp;
			}
			//���� ��������� ���� �� root (�� ����� ���� �����������).
			//node ����� �� parent.
			else if (node->id < node->parent->id) 
			{
				Node<T>* iter = node->right;      //������ ��� ������.
				while (iter->left)                //����� ����� � �� �����. 
					iter = iter->left;
				Node<T>* tmp = node;
				node = iter;
				if (!node->right)
					node->parent->left = nullptr;
				else
					node->parent->left = node->right;

				node->parent = tmp->parent;
				node->left = tmp->left;
				node->right = tmp->right;
				node->parent->left = node;
				node->left->parent = node;
				node->right->parent = node;
				delete tmp;
			}
			// node ������ �� parent.	 
			else
			{
				Node<T>* iter = node->left;        //������ ��� �����. 
				while (iter->right)                //����� ������ � �� �����.
					iter = iter->right;
				Node<T>* tmp = node;
				node = iter;
				if (!node->left)
					node->parent->right = nullptr;
				else
					node->parent->right = node->left;

				node->parent = tmp->parent;
				node->left = tmp->left;
				node->right = tmp->right;
				node->parent->right = node;
				node->left->parent = node;
				node->right->parent = node;
				delete tmp;
			}
		//}
		size--;
	}
};












int main()
{
	setlocale(LC_ALL, "ru");

	BinaryTree <double> tree(15);
	tree.add(10);
	tree.add(8);
	tree.add(6);
	tree.add(12);
	tree.add(11);
	tree.add(11.5);
	tree.add(14);
	tree.add(13);
	tree.add(20);
	tree.add(24);
	tree.add(19);
	tree.add(18);
	tree.add(19.5);
	tree.print();
	cout << endl;
	tree.remove(15);
	tree.print();
	cout << endl;
	tree.remove(12);
	tree.print();
	cout << endl;
	tree.remove(20);
	tree.print();
	cout << endl;
	tree.add(20);
	tree.print();


	return 0;
}