#ifndef TREENODE_H
#define TREENODE_H

#include <vector>


template<typename T>
class TreeNode {
public:
	TreeNode<T>();
	TreeNode<T>(T, TreeNode<T>*);
	~TreeNode();

	/// <summary>
	/// Returns all children.
	/// </summary>
	/// <returns></returns>
	std::vector<TreeNode<T>*> getChildren() { return _children; }

	/// <summary>
	/// Returns the child at given index.
	/// </summary>
	/// <param name="pIndex">Index of the child.</param>
	/// <returns></returns>
	TreeNode<T>* getChildAt(int pIndex) { return _children.size() > pIndex ? _children[pIndex] : nullptr; }

	/// <summary>
	/// Returns the parent of this node.
	/// </summary>
	/// <returns></returns>
	TreeNode<T>* getParent() { return _parent; }

	/// <summary>
	/// Determines whether this node [is leaf node].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is leaf node]; otherwise, <c>false</c>.
	/// </returns>
	bool isLeafNode() { return _children.size() == 0; }

	/// <summary>
	/// Returns the data of this node.
	/// </summary>
	/// <returns></returns>
	T getData() { return _data; }

	void setChildren(std::vector<TreeNode<T>*>);
	void addChildren(std::vector<TreeNode<T>*>);
	int insertChild(TreeNode<T>*, int);

	int removeChildren();
	void removeChild(int);

	int destroy();

protected:
	std::vector<TreeNode<T>*> _children;
	TreeNode<T>* _parent;
	T _data;

	void removeChildFromDestroy(int);
};

#endif  