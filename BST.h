#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>
#include <queue>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>

template<typename T>
class BST
{
	class TreeNode
	{
	public:
		T data;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;

		TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, T dt) : parent(p), left(l), right(r), data(dt) {}

		bool isLeaf()
		{
			if (this == nullptr)
				throw std::out_of_range("Node is nullptr!");
			return (left == nullptr) && (right == nullptr);
		}

		~TreeNode() {}
	};

	TreeNode* root;

public:
	BST() : root(nullptr) {}

	BST(T value) : root(new TreeNode(nullptr, nullptr, nullptr, value)) {}

	TreeNode*& getRoot()
	{
		return root;
	}

	bool empty() const
	{
		return root == nullptr;
	}

	void add(T elem)
	{
		if (empty())
			root = new TreeNode(nullptr, nullptr, nullptr, elem);
		else
			private_add(elem, root);
	}

	TreeNode* search(T value) const
	{
		return private_search(value, root);
	}

	T max() const
	{
		if (empty())
			std::cout << "Tree is empty" << std::endl;
		else
			return getMax(root);
	}

	T min() const
	{
		if (empty())
			std::cout << "Tree is empty" << std::endl;
		else
			return getMin(root);
	}

	TreeNode* FirstLessEqual(TreeNode* node) const
	{
		return prv_FirstLessEqual(node);
	}

	TreeNode* FirstGreaterEqual(TreeNode* node) const
	{
		return prv_FirstGreaterEqual(node);
	}

	void del_elem(T x)
	{
		TreeNode* node_to_del = search(x);
		if (node_to_del == nullptr)
			return;
		TreeNode* p = node_to_del->parent;
		// CASE 1
		if ((node_to_del->left == nullptr) && (node_to_del->right == nullptr))
		{
			if (node_to_del->data < p->data)
				p->left = nullptr;
			else
				p->right = nullptr;
			delete node_to_del;
			return;
		}
		// CASE 2
		if ((node_to_del->left == nullptr) || (node_to_del->right == nullptr))
		{
			if (node_to_del->left == nullptr)
			{
				if (p->left == node_to_del)
					p->left = node_to_del->right;
				else
					p->right = node_to_del->right;
				node_to_del->right->parent = p;
			}
			else
			{
				if (p->left == node_to_del)
					p->left = node_to_del->left;
				else
					p->right = node_to_del->left;
				node_to_del->left->parent = p;
			}
			delete node_to_del;
			return;
		}
		// CASE 3
		TreeNode* successor = next(node_to_del->data);
		node_to_del->data = successor->data;
		if (successor->parent->left == successor)
		{
			successor->parent->left = successor->right;
			if (successor->right != nullptr)
				successor->right->parent = successor->parent;
		}
		else
		{
			successor->parent->right = successor->right;
			if (successor->right != nullptr)
				successor->right->parent = successor->parent;
		}
		node_to_del = nullptr;
		delete node_to_del;
	}

	void ordered_print()
	{
		prv_ordered_print(root);
		std::cout << std::endl;
	}

	void stack_print()
	{
		std::stack<TreeNode*> st;
		TreeNode* cur = root;
		while (!st.empty() || (cur != nullptr))
		{
			if (cur != nullptr)
			{
				st.push(cur);
				cur = cur->right;
			}
			else
			{
				cur = st.top();
				st.pop();
				std::cout << cur->data << " ";
				cur = cur->left;
			}
		}
		std::cout << std::endl;
	}

	void print_lays()
	{
		std::queue<std::pair<int, int>> q;
		RRL(root, 0, [&q](int x, int cnt){\
			q.emplace(x, cnt);
		});
		while (!q.empty())
		{
			std::pair<int, int> p = q.front();
			for (int i = 0; i < p.second; i++)
				std::cout << "     ";
			std::cout << p.first << std::endl;
			q.pop();
		}
		std::cout << std::endl;
	}

	friend bool trees_are_equal(const BST& t1, const BST& t2)
	{
		TreeNode* cur1 = t1.root;
		TreeNode* cur2 = t2.root;
		std::stack<TreeNode*> s1;
		std::stack<TreeNode*> s2;
		while ((!s1.empty() && !s2.empty()) || ((cur1 != nullptr) && (cur2 != nullptr)))
		{
			if (cur1 != nullptr)
			{
				if ((cur2 == nullptr) || (cur1->data != cur2->data))
					return false;
				if (cur1->parent != nullptr)
				{
					if ((cur2->parent == nullptr) || (cur1->parent->data != cur2->parent->data))
						return false;
				}
				else
				{
					if (cur2->parent != nullptr)
						return false;
				}
				s1.push(cur1);
				s2.push(cur2);
				cur1 = cur1->left;
				cur2 = cur2->left;
			}
			else
			{
				if (cur2 != nullptr)
					return false;
				cur2 = s2.top();
				cur1 = s1.top();
				s1.pop();
				s2.pop();
				cur1 = cur1->right;
				cur2 = cur2->right;
			}
		}
		if (cur1 == nullptr)
		{
			if (cur2 == nullptr)
				return true;
			else
				return false;
		}
		else
		{
			if ((cur2 != nullptr) && (cur1->data == cur2->data))
				return true;
			else
				return false;
		}
	}

private:

	void private_add(T elem, TreeNode* node)
	{
		if (elem < node->data)
		{
			if (node->left != nullptr)
				private_add(elem, node->left);
			else
			{
				node->left = new TreeNode(node, nullptr, nullptr, elem);
				return;
			}
		}
		else if (elem > node->data)
		{
			if (node->right != nullptr)
			{
				private_add(elem, node->right);
				return;
			}
			else
			{
				node->right = new TreeNode(node, nullptr, nullptr, elem);
				return;
			}
		}
		else
			return;
	}

	TreeNode* private_search(T value, TreeNode* node) const
	{
		if (node == nullptr)
			return nullptr;
		else if (node->data == value)
			return node;
		else if (node->data > value)
			return private_search(value, node->left);
		else
			return private_search(value, node->right);
	}

	T getMax(TreeNode* node) const
	{
		if (node->right == nullptr)
			return node->data;
		else
			return getMax(node->right);
	}

	T getMin(TreeNode* node) const
	{
		if (node->left == nullptr)
			return node->data;
		else
			return getMin(node->left);
	}

	TreeNode* getMinNode(TreeNode* node) const
	{
		if (node->left == nullptr)
			return node;
		else
			return getMinNode(node->left);
	}

	TreeNode* getMaxNode(TreeNode* node) const
	{
		if (node->right == nullptr)
			return node;
		else
			return getMaxNode(node->right);
	}

	TreeNode* prv_FirstLessEqual(TreeNode* node) const
	{
		return (node->left != nullptr) ? getMaxNode(node->left) : nullptr;
	}

	TreeNode* prv_FirstGreaterEqual(TreeNode* node) const
	{
		return (node->right != nullptr) ? getMinNode(node->right) : nullptr;
	}

	TreeNode* next(T x)
	{
		TreeNode* cur = root;
		TreeNode* successor = nullptr;
		while (cur != nullptr)
		{
			if (cur->data > x)
			{
				successor = cur;
				cur = cur->left;
			}
			else
				cur = cur->right;
		}
		return successor;
	}

	void prv_ordered_print(TreeNode* rt)
	{
		if (rt != nullptr)
		{
			prv_ordered_print(rt->left);
			std::cout << rt->data << " ";
			prv_ordered_print(rt->right);
		}
	}

	// Right Root Left
	template<typename Func>
	void RRL(TreeNode* node, Func f)
	{
		if (node != nullptr)
		{
			RRL(node->right, f);
			f(node->data);
			RRL(node->left, f);
		}
	}

	// Right Root Left
	template<typename Func>
	void RRL(TreeNode* node, int cnt, Func f)
	{
		if (node != nullptr)
		{
			RRL(node->right, cnt + 1, f);
			f(node->data, cnt);
			RRL(node->left, cnt + 1, f);
		}
	}
};

template<typename T>
class Set
{
private:
	BST<T> data;
public:
	Set() = default;

	bool includes(T value)
	{
		return data.search(value) != nullptr;
	}

	void add(T value)
	{
		data.add(value);
	}

	void remove(T value)
	{
		data.del_elem(value);
	}

	void print()
	{
		data.ordered_print();
	}

	void printLs() const
	{
		data.printLays();
		std::cout << std::endl << std::endl << std::endl;
	}

};

Set<int> primes(const int n)
{
	assert(n >= 0);
	Set<int> result;

	int* arr = new int[n + 1];
	const int size = n + 1;

	for (int i = 2; i < size; ++i)
		arr[i] = i;

	std::random_shuffle(arr + 2, arr + size);
	for (int i = 2; i < size; ++i)
		result.add(arr[i]);

	int upperBound = static_cast<int>(std::sqrt(n)) + 1;
	for (int i = 2; i < upperBound; ++i)
	{
		if (!result.includes(i))
			continue;
		int value = i + i;
		while (value <= n)
		{
			result.remove(value);
			value += i;
		}
	}
	return result;
}

std::vector<int> primesVector(const int n)
{
	assert(n >= 0);
	std::vector<int> result;
	for (int i = 2; i < n; ++i)
		result.push_back(i);

	int upperBound = static_cast<int>(std::sqrt(n)) + 1;
	for (int i = 2; i < upperBound; ++i)
	{
		if (std::find(result.begin(), result.end(), i) == result.end())
			continue;
		int value = i + i;
		while (value < n)
		{
			auto iter = std::find(result.begin(), result.end(), value);
			if (iter != result.end())
				result.erase(std::find(result.begin(), result.end(), value));
			value += i;
		}
	}
	return result;
}

#endif
