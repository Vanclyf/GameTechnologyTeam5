#include "Tree.h"

/// <summary>
/// Initializes a new instance of the <see cref="Tree"/> class.
/// </summary>
template<typename T>
Tree<T>::Tree() : _size(0) { }

/// <summary>
/// Finalizes an instance of the <see cref="Tree"/> class.
/// </summary>
template<typename T>
Tree<T>::~Tree() { }

/// <summary>
/// Sets the root node.
/// </summary>
/// <param name="pData">The data for the root node.</param>
/// <returns>Whether the root is succesfully added.</returns>
template<typename T>
void Tree<T>::setRoot(T pData) {
	// increase the size of the tree
	++_size;

	// create the node 
	TreeNode<T>* node = new TreeNode<T>(pData, nullptr);

	// set the root node to the created node 
	_root = node;
}

/// <summary>
/// Adds a node to the tree.
/// </summary>
/// <param name="pData">The data for the new node.</param>
/// <param name="pLeaf">The leaf that will be the parent.</param>
template<typename T>
void Tree<T>::addNode(T pData, TreeNode<T>* pLeaf = nullptr) {
	// if no leaf is given, add it to the root
	if (!pLeaf) pLeaf = _root;

	// increase the size of the tree
	++_size;

	// if the root doesnt exist, set the new node to be the root
	if (_root == NULL) {
		// create the new node and set the root
		TreeNode<T>* node = new TreeNode<T>(pData, nullptr);
		_root = node;
	}
	else {
		// create the node 
		std::vector<TreeNode<T>*> nodes;
		TreeNode<T>* node = new TreeNode<T>(pData, pLeaf);
		nodes.push_back(node);

		// either set it as the parents only node or add it to the others
		if (pLeaf->getChildren().size() == 0) {
			pLeaf->setChildren(nodes);
		}
		else {
			pLeaf->addChildren(nodes);
		}
	}
}

/// <summary>
/// Adds the nodes.
/// </summary>
/// <param name="pData">The p data.</param>
/// <param name="pNode">The p node.</param>
/// <returns></returns>
template<typename T>
void Tree<T>::addNodes(std::vector<T> pData, TreeNode<T>* pNode = nullptr) {
	// if no leaf is given, add it to the root
	if (!pNode) pNode = _root;

	// increase the size of the tree
	_size += pData.size();

	// as long as the root is null you cant add multiple children
	if (_root == NULL) {
		// error occured
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		std::cout << "ERROR occured, as long as the root is null you cant add multiple children." << std::endl;
		fclose(fp);
#endif
		return;
	}

	// create the nodes
	std::vector<TreeNode<T>*> nodes;
	for (int i = 0; i < pData.size(); ++i) {
		TreeNode<T>* node = new TreeNode<T>(pData[i], pNode);
		nodes.push_back(node);
	}

	// either set it as the parents only node or add it to the others
	if (pNode->getChildren().size() == 0) {
		pNode->setChildren(nodes);
	}
	else {
		pNode->addChildren(nodes);
	}
}

/// <summary>
/// Removes the node from the tree.
/// </summary>
/// <param name="pNode">The node to remove.</param>
template<typename T>
void Tree<T>::removeNode(TreeNode<T>* pNode) {
	// if the node exists
	if (pNode) {
		// call its destory method
		int removedNodes = pNode->destroy();
		_size -= removedNodes;
	}
}


/// <summary>
/// Returns the preorder from the specified node.
/// </summary>
/// <param name="pNode">The start node.</param>
/// <returns></returns>
template<typename T>
std::vector<TreeNode<T>*> Tree<T>::preorder(TreeNode<T>* pNode = nullptr) {
	// if no leaf is given, set it to the root
	if (!pNode) pNode = _root;

	// declare a vector to return with all the nodes
	std::vector<TreeNode<T>*> returnList;

	// if the start node exists
	if (pNode != nullptr) {

		// add this node
		returnList.push_back(pNode);

		// for each of this nodes children
		for (int i = 0; i < pNode->getChildren().size(); ++i) {

			// get all the childs nodes in preorder
			std::vector<TreeNode<T>*> nodes = preorder(pNode->getChildren()[i]);

			// add all the found nodes to the return list
			for (int j = 0; j < nodes.size(); ++j) {
				returnList.push_back(nodes[j]);
			}
		}
	}

	// return all nodes in preorder
	return returnList;
}

/// <summary>
/// Returns the postorder from the specified node.
/// </summary>
/// <param name="pNode">The start node.</param>
/// <returns></returns>
template<typename T>
std::vector<TreeNode<T>*> Tree<T>::postorder(TreeNode<T>* pNode = nullptr) {
	// if no leaf is given, set it to the root
	if (!pNode) pNode = _root;

	// declare a vector to return with all the nodes
	std::vector<TreeNode<T>*> returnList;

	// if the start node exists
	if (pNode != nullptr) {

		// for each of this nodes children
		for (int i = 0; i < pNode->getChildren().size(); ++i) {

			// get all the childs nodes in postorder
			std::vector<TreeNode<T>*> nodes = postorder(pNode->getChildren()[i]);

			// add all the found nodes to the return list
			for (int j = 0; j < nodes.size(); ++j) {
				returnList.push_back(nodes[j]);
			}
		}

		// add this node
		returnList.push_back(pNode);
	}

	// return all nodes in postorder
	return returnList;
}

template class Tree < int >;
template class Tree < char >;
template class Tree < float >;
template class Tree < bool >;
template class Tree < double >;