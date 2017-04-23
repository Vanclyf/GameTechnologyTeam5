#ifndef TREE_H
#define TREE_H
#include <vector>

template<typename T>
class TreeNode {
	TreeNode<T>();
	TreeNode<T>(T data) : _data(data) {};
	~TreeNode();

	// get node methods
	std::vector<TreeNode<T>*> getChildren() { return _childs; }
	TreeNode<T>* getChildAt(int pIndex) {
		if (_childs.size() < pIndex) return _childs[pIndex];
		else return nullptr;
	}

	// set node methods
	void setChildren(std::vector<TreeNode<T>*> pNodes) {
		if (_childs.size() != 0) { removeChildren(); }
		_childs = pNodes;
	}
	void addChildren(std::vector<TreeNode<T>*> pNodes) {
		for (int i = 0; i < pNodes.size(); ++i) {
			_childs.push_back(pNodes[i]);
		}
	}
	int insertChild(TreeNode<T>* pNode, int pIndex) {
		int resultingIndex = _childs.size();
		if (_childs.size() >= pIndex) {
			_childs.push_back(pNode);
		}
		else {
			std::vector<int>::iterator it;
			it = _childs.begin();
			_childs.insert(it+pIndex, pNode);
			resultingIndex = pIndex;
		}

		return resultingIndex;
	}

	// remove nodes
	void removeChildren() {
		for(int i = 0; i < _childs.size(); ++i) {
			_childs[i]->destory();
		}

		_childs.earse(_childs.begin(), _childs.end());
	}
	void removeChild(int pIndex) {
		if(_childs.size() >= pIndex) return;

		_childs[pIndex]->destroy;
	}

	// last node?
	bool isLeafNode() { return _childs.size() == 0; }

	// get its data
	T* getData() { return _data; }

	void destroy() {
		removeChildren();
		delete _data;
	}

protected:
	std::vector<TreeNode<T>*> _childs;
	T* _data;
};

// TODO: remove this class if it seems to be unnessacery 
/*template<typename T>
class TreeRoot : TreeNode<T> {
	TreeRoot<T>() { TreeNode<T>(); };
	~TreeRoot() { ~TreeNode<T>(); };
};*/

// TODO: possibly two templates needed (action and strat), but maybe solvable with super class or interface
template<typename T>
class Tree {
	Tree<T>();
	~Tree();

	int size() const { return _size; }

	T* getRootData() { return _root->getData(); }
	
	void setRoot(TreeNode<T>* pRoot) {
		++_size;
		_root = pRoot;
	}

	void addNode(T pData, TreeNode<T>* pLeaf = _root) {
		++_size;
		if (_root == NULL) {
			TreeNode<T>* node = new TreeNode<T>(pData);
			_root = node;
		}
		else {
			TreeNode<T>* node = new TreeNode<T>(pData);
			if(pLeaf->getChildren().size() == 0) {
				pLeaf->setChildren(node);
			}
			else {
				pLeaf->addChildren(node);
			}
		}
	}

	void addNodes(std::vector<T> pData, TreeNode<T> pNode) {
		_size += pData.size();
		if (_root == NULL) {
			// error occured, as long as the root is null you cant add multiple children.
			return;
		}

		std::vector<TreeNode<T>*> nodes;
		for (int i = 0; i < pData.size(); ++i) {
			TreeNode<T>* node = new TreeNode<T>(pData);
			nodes.push_back(node);
		}

		if (pNode->getChildren().size() == 0) {
			pNode->setChildren(nodes);
		}
		else {
			pNode->addChildren(nodes);
		}

	}

	void removeNode(TreeNode<T>* pNode) {
		if(pNode != NULL) {
			pNode->destroy();
		}
	}

	std::vector<TreeNode<T>*> preorder(TreeNode<T>* pNode) {
		std::vector<TreeNode<T>*> returnList;
		if(pNode != NULL) {
			returnList.push_back(pNode);
			for (int i = 0; i < pNode->getChildren().size(); ++i) {
				preorder(pNode->getChildren()[i]);
			}
		}
		return returnList;
	}
	std::vector<TreeNode<T>*> postorder(TreeNode<T>* pNode) {
		std::vector<TreeNode<T>*> returnList;
		if (pNode != NULL) {
			for (int i = 0; i < pNode->getChildren().size(); ++i) {
				postorder(pNode->getChildren()[i]);
			}
			returnList.push_back(pNode);
		}
		return returnList;
	}

private:
	TreeNode<T>* _root;
	int _size;
};

#endif