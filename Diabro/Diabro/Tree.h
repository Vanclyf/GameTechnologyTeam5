#ifndef TREE_H
#define TREE_H
#include <vector>

template<typename T>
class TreeNode {
public:
	TreeNode<T>();
	TreeNode<T>(T pData, TreeNode<T>* pParent) : _data(pData), _myParent(pParent) {};
	~TreeNode();

	// get node methods
	std::vector<TreeNode<T>*> getChildren() { return _childs; }
	TreeNode<T>* getChildAt(int pIndex) {
		if (_childs.size() < pIndex) return _childs[pIndex];
		else return nullptr;
	}
	TreeNode<T>* getParent() { return _myParent; }

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
			std::vector<TreeNode<T>*>::iterator it;
			it = _childs.begin();
			_childs.insert(it+pIndex, pNode);
			resultingIndex = pIndex;
		}

		return resultingIndex;
	}

	// remove nodes
	void removeChildren() {
		for(int i = 0; i < _childs.size(); ++i) {
			_childs[i]->destroy();
		}

		_childs.erase(_childs.begin(), _childs.end());
	}
	void removeChild(int pIndex) {
		if(_childs.size() <= pIndex) return;

		_childs[pIndex]->destroy();
		std::vector<TreeNode<T>*>::iterator it;
		it = _childs.begin();
		_childs.erase(it + pIndex);
	}

	// last node?
	bool isLeafNode() { return _childs.size() == 0; }

	// get its data
	T getData() { return _data; }

	void destroy() {
		if(_childs.size() > 0) removeChildren();

		int index;
		for (int i = 0; i < _myParent->getChildren().size(); ++i) {
			if(_myParent->getChildren()[i] == this) {
				index = i;
				break;
			}
		}
		_myParent->removeChildFromDestroy(index);
		//delete _data;
	}

protected:
	std::vector<TreeNode<T>*> _childs;
	TreeNode<T>* _myParent;
	T _data;

	void removeChildFromDestroy(int pIndex) {
		if (_childs.size() <= pIndex) return;

		std::vector<TreeNode<T>*>::iterator it;
		it = _childs.begin();
		_childs.erase(it + pIndex);
	}
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
public:
	Tree<T>() {};
	~Tree();

	int size() const { return _size; }

	TreeNode<T>* getRoot() { return _root; }
	T getRootData() { return _root->getData(); }
	
	void setRoot(T pData) {
		++_size;
		TreeNode<T>* node = new TreeNode<T>(pData, nullptr);
		_root = node;
	}

	void addNode(T pData, TreeNode<T>* pLeaf = nullptr) {
		if (!pLeaf) pLeaf = _root;

		++_size;
		if (_root == NULL) {
			TreeNode<T>* node = new TreeNode<T>(pData, nullptr);
			_root = node;
		}
		else {
			std::vector<TreeNode<T>*> nodes;
			TreeNode<T>* node = new TreeNode<T>(pData, pLeaf);
			nodes.push_back(node);
			if(pLeaf->getChildren().size() == 0) {
				pLeaf->setChildren(nodes);
			}
			else {
				pLeaf->addChildren(nodes);
			}
		}
	}

	void addNodes(std::vector<T> pData, TreeNode<T>* pNode = nullptr) {
		if (!pNode) pNode = _root;

		_size += pData.size();
		if (_root == NULL) {
			// error occured, as long as the root is null you cant add multiple children.
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			std::cout << "ERROR occured, as long as the root is null you cant add multiple children." << std::endl;
			fclose(fp);
#endif
			return;
		}

		std::vector<TreeNode<T>*> nodes;
		for (int i = 0; i < pData.size(); ++i) {
			TreeNode<T>* node = new TreeNode<T>(pData[i], pNode);
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
		if(pNode) {
			pNode->destroy();
		}
	}

	std::vector<TreeNode<T>*> preorder(TreeNode<T>* pNode = nullptr){
		if (!pNode) pNode = _root;

		std::vector<TreeNode<T>*> returnList;
		if(pNode != NULL) {
			returnList.push_back(pNode);
			for (int i = 0; i < pNode->getChildren().size(); ++i) {
				std::vector<TreeNode<T>*> nodes = preorder(pNode->getChildren()[i]);
				for (int j = 0; j < nodes.size(); ++j) {
					returnList.push_back(nodes[j]);
				}
			}
		}
		return returnList;
	}
	std::vector<TreeNode<T>*> postorder(TreeNode<T>* pNode = nullptr) {
		if (!pNode) pNode = _root;

		std::vector<TreeNode<T>*> returnList;
		if (pNode != NULL) {
			for (int i = 0; i < pNode->getChildren().size(); ++i) {
				std::vector<TreeNode<T>*> nodes = postorder(pNode->getChildren()[i]);
				for (int j = 0; j < nodes.size(); ++j) {
					returnList.push_back(nodes[j]);
				}
			}
			returnList.push_back(pNode);
		}
		return returnList;
	}

private:
	TreeNode<T>* _root;
	int _size;
};

template class Tree < int >;
template class TreeNode < int >;
#endif