#include "TreeNode.h"

/// <summary>
/// Initializes a new instance of the <see cref="TreeNode"/> class.
/// </summary>
template<typename T>
TreeNode<T>::TreeNode() { }

/// <summary>
/// Initializes a new instance of the <see cref="TreeNode"/> class.
/// </summary>
/// <param name="pData">The data (which is generic so it can be of any type) for the node.</param>
/// <param name="pParent">The parent for the node.</param>
template<typename T>
TreeNode<T>::TreeNode(T pData, TreeNode<T>* pParent) : _data(pData), _parent(pParent) { }

/// <summary>
/// Finalizes an instance of the <see cref="TreeNode"/> class.
/// </summary>
template<typename T>
TreeNode<T>::~TreeNode() { }

/// <summary>
/// Sets the children.
/// </summary>
/// <param name="pNodes">The nodes to child to this node.</param>
template<typename T>
void TreeNode<T>::setChildren(std::vector<TreeNode<T>*> pNodes) {
	// if we already have children, remove them
	if (_children.size() != 0) { removeChildren(); }

	// set the children to the given nodes
	_children = pNodes;
}

/// <summary>
/// Adds the children.
/// </summary>
/// <param name="pNodes">The nodes to child to this node.</param>
template<typename T>
void TreeNode<T>::addChildren(std::vector<TreeNode<T>*> pNodes) {
	// for each node to add, push it to the children vector
	for (int i = 0; i < pNodes.size(); ++i) {
		_children.push_back(pNodes[i]);
	}
}

/// <summary>
/// Inserts the child.
/// </summary>
/// <param name="pNode">The new child node.</param>
/// <param name="pIndex">The index the child will be placed.</param>
/// <returns></returns>
template<typename T>
int TreeNode<T>::insertChild(TreeNode<T>* pNode, int pIndex) {
	// the index at which the new node ended up, by default at the end
	int resultingIndex = _children.size();

	// if the given index is to big, push the new node the the back
	if (_children.size() >= pIndex) {
		_children.push_back(pNode);
	}
	// else, add it to the given index
	else {
		// declare an iterator and inset the node
		std::vector<TreeNode<T>*>::iterator it;
		it = _children.begin();
		_children.insert(it + pIndex, pNode);
		resultingIndex = pIndex;
	}

	// return the index the node ended up
	return resultingIndex;
}

/// <summary>
/// Removes all children.
/// </summary>
template<typename T>
int TreeNode<T>::removeChildren() {
	int removedChildren = 0;

	// destroy each child
	while(_children.size() > 0){
		removedChildren += _children[0]->destroy();
	}

	// erase the children from the list
	_children.erase(_children.begin(), _children.end());

	return removedChildren;
}

/// <summary>
/// Removes one child.
/// </summary>
/// <param name="pIndex">Index of the child to remove.</param>
template<typename T>
void TreeNode<T>::removeChild(int pIndex) {
	// if the index is greater than the amount of childs, return false
	if (_children.size() <= pIndex) return;

	// call destory on the given child node
	_children[pIndex]->destroy();

	// declare an iterator and remove the child from the vector
	std::vector<TreeNode<T>*>::iterator it;
	it = _children.begin();
	_children.erase(it + pIndex);
}

/// <summary>
/// Destroys this instance.
/// </summary>
template<typename T>
int TreeNode<T>::destroy() {
	// if this node is going to be destroyed, but it still has children,
	// remove the children first
	int removedNodes = 1;

	if (_children.size() > 0) removedNodes += removeChildren();

	// find the index of this node in the children of this parent
	if(_parent != nullptr) {
		int index;
		for (int i = 0; i < _parent->getChildren().size(); ++i) {
			if (_parent->getChildren()[i] == this) {
				index = i;
				break;
			}
		}

		// remove this node from its parent
		_parent->removeChildFromDestroy(index);
	}

	//TODO: find a way to delete the data in a generic way
	//delete _data;

	return removedNodes;
}

/// <summary>
/// Removes a given child only from the children list,
/// called when a node destorys itself.
/// </summary>
/// <param name="pIndex">Index of the node to remove.</param>
template<typename T>
void TreeNode<T>::removeChildFromDestroy(int pIndex) {
	// if the given index 
	if (_children.size() <= pIndex) return;

	// declare an iterator and remove the child from the vector
	std::vector<TreeNode<T>*>::iterator it;
	it = _children.begin();
	_children.erase(it + pIndex);
}

template class TreeNode < int >;
template class TreeNode < char >;
template class TreeNode < float >;
template class TreeNode < bool >;
template class TreeNode < double >;