#ifndef TREE_H
#define TREE_H
#include <vector>
#include <iostream>
#include "TreeNode.h"

// TODO: possibly two templates needed (action and strat), but maybe solvable with super class or interface
template<typename T>
class Tree {
public:
	Tree<T>();
	~Tree();

	/// <summary>
	/// Returns the sizes of this instance.
	/// </summary>
	/// <returns></returns>
	int size() const { return _size; }

	/// <summary>
	/// Returns the root node.
	/// </summary>
	/// <returns></returns>
	TreeNode<T>* getRoot() { return _root; }

	/// <summary>
	/// Returns the root node's data.
	/// </summary>
	/// <returns></returns>
	T getRootData() { return _root->getData(); }

	void setRoot(T);
	void addNode(T pData, TreeNode<T>* pLeaf = nullptr);
	void addNodes(std::vector<T> pData, TreeNode<T>* pNode = nullptr);
	void removeNode(TreeNode<T>*);

	std::vector<TreeNode<T>*> preorder(TreeNode<T>* pNode = nullptr);
	std::vector<TreeNode<T>*> postorder(TreeNode<T>* pNode = nullptr);

private:
	TreeNode<T>* _root;
	int _size;
};

#endif