#include "Catch.hpp"
#include "TreeNode.h"
#include "Tree.h"

TEST_CASE("Creation integer tree test", "[Tree]") {
	Tree<int>* myTree = new Tree<int>();
	myTree->setRoot(0);

	SECTION("Creation of an integer tree") {
		INFO("The roots data is " << myTree->getRootData());
		REQUIRE(myTree != nullptr);
		REQUIRE(myTree->getRootData() == 0);
	}
}

TEST_CASE("Adjustment integer tree test", "[Tree]") {
	Tree<int>* myTree = new Tree<int>();
	myTree->setRoot(0);

	SECTION("Adding nodes to an integer tree") {
		GIVEN("No child node are added to the tree") {
			THEN("The root node's list of children is empty") {
				REQUIRE(myTree->getRoot()->getChildren().empty());
			}
		}

		GIVEN("3 Child nodes are added to the tree") {
			std::vector<int> data;
			data.push_back(1);
			data.push_back(2);
			data.push_back(3);
			myTree->addNodes(data);

			THEN("The root node has 3 children") {
				REQUIRE(myTree->getRoot()->getChildren().size() == 3);
				REQUIRE(myTree->size() == 4);
			}

			AND_WHEN("2 Child nodes are added to the first child of the root") {
				std::vector<int> datanode2;
				datanode2.push_back(100);
				datanode2.push_back(200);
				myTree->addNodes(datanode2, myTree->getRoot()->getChildAt(0));

				THEN("The first node of the root has 2 children") {
					REQUIRE(myTree->getRoot()->getChildAt(0)->getChildren().size() == 2);
				}

				SECTION("Removing nodes from an integer tree") {
					GIVEN("A tree exists with a root, which has three child node and the first child node has two child nodes.") {
						SECTION("Removing the root") {
							GIVEN("The root node is removed") {
								myTree->removeNode(myTree->getRoot());

								THEN("The tree is empty") {
									INFO("Amount of nodes in tree is " << myTree->size());
									REQUIRE(myTree->size() == 0);
								}
							}
						}

						SECTION("Removing a child of the root") {

							GIVEN("The third child of the root node is removed") {
								myTree->removeNode(myTree->getRoot()->getChildren()[2]);

								THEN("The root has two children") {
									INFO("Amount of child nodes is " << myTree->getRoot()->getChildren().size());
									REQUIRE(myTree->getRoot()->getChildren().size() == 2);
								}
							}
						}

						SECTION("Removing a child of the first child of the root") {
							GIVEN("The second child of first child of the root node is removed") {
								myTree->removeNode(myTree->getRoot()->getChildren()[0]->getChildAt(1));

								THEN("The first child of the root has one child") {
									INFO("Amount of child nodes is " << myTree->getRoot()->getChildren()[0]->getChildren().size());
									REQUIRE(myTree->getRoot()->getChildren()[0]->getChildren().size() == 1);
								}
							}
						}
					}
				}
			}
		}
	}
}

TEST_CASE("Obtaining data character tree test", "[Tree]") {
	Tree<char>* myTree = new Tree<char>();
	myTree->setRoot('A');

	std::vector<char> data;
	data.push_back('a');
	data.push_back('b');
	data.push_back('c');
	myTree->addNodes(data);

	std::vector<char> datanode2;
	datanode2.push_back('B');
	datanode2.push_back('C');
	datanode2.push_back('D');
	myTree->addNodes(datanode2, myTree->getRoot()->getChildAt(2));

	GIVEN("A tree with 3 child nodes and the third child with also 3 child nodes has been build.") {
		THEN("The root node has three children and the data of them can be obtained") {
			REQUIRE(myTree->getRoot()->getChildren().size() == 3);
			REQUIRE(myTree->getRoot()->getChildAt(0)->getData() == 'a');
			REQUIRE(myTree->getRoot()->getChildAt(1)->getData() == 'b');
			REQUIRE(myTree->getRoot()->getChildAt(2)->getData() == 'c');
		}

		THEN("The third child of the root has also three children and the data of them can be obtained") {
			REQUIRE(myTree->getRoot()->getChildAt(2)->getChildren().size() == 3);
			REQUIRE(myTree->getRoot()->getChildAt(2)->getChildAt(0)->getData() == 'B');
			REQUIRE(myTree->getRoot()->getChildAt(2)->getChildAt(1)->getData() == 'C');
			REQUIRE(myTree->getRoot()->getChildAt(2)->getChildAt(2)->getData() == 'D');
		}

		THEN("All nodes except the root and its third child are leaves") {
			REQUIRE(!myTree->getRoot()->isLeafNode());

			for (int i = 0; i < myTree->getRoot()->getChildren().size(); ++i) {
				if(i == 2) {
					REQUIRE(!myTree->getRoot()->getChildAt(i)->isLeafNode());
				}
				else {
					REQUIRE(myTree->getRoot()->getChildAt(i)->isLeafNode());
				}
			}
		}

		THEN("The parent of each child of the root is the root") {
			REQUIRE(myTree->getRoot()->getChildAt(0)->getParent() == myTree->getRoot());
			REQUIRE(myTree->getRoot()->getChildAt(1)->getParent() == myTree->getRoot());
			REQUIRE(myTree->getRoot()->getChildAt(2)->getParent() == myTree->getRoot());
		}
	}
}

TEST_CASE("Pre- and post-order traversel floating point tree test", "[Tree]") {
	Tree<float>* myTree = new Tree<float>();

	SECTION("Large tree in pre- and post-order traversal") {
		// set root
		myTree->setRoot(0.1f);

		// set level one nodes
		std::vector<float> data;
		data.push_back(1.1f);
		data.push_back(1.2f);
		data.push_back(1.3f);
		data.push_back(1.4f);
		data.push_back(1.5f);
		myTree->addNodes(data);

		data.clear();

		// set level two nodes
		data.push_back(2.1f);
		data.push_back(2.2f);
		data.push_back(2.3f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(0));

		data.clear();

		data.push_back(2.4f);
		data.push_back(2.5f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(2));

		data.clear();

		data.push_back(2.6f);
		data.push_back(2.7f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(3));

		data.clear();

		data.push_back(2.8f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(4));

		data.clear();

		// set level three nodes
		data.push_back(3.1f);
		data.push_back(3.2f);
		data.push_back(3.3f);
		data.push_back(3.4f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(0)->getChildAt(1));

		data.clear();

		data.push_back(3.5f);
		data.push_back(3.6f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(2)->getChildAt(1));

		data.clear();

		data.push_back(3.7f);
		data.push_back(3.8f);
		data.push_back(3.9f);
		myTree->addNodes(data, myTree->getRoot()->getChildAt(4)->getChildAt(0));

		GIVEN("A large tree with 3 layers has been build") {
			std::vector<TreeNode<float>*> preorderTree;
			std::vector<TreeNode<float>*> postorderTree;
			preorderTree = myTree->preorder();
			postorderTree = myTree->postorder();

			THEN("The tree can be obtained in pre-order traversal") {
				REQUIRE(preorderTree.size() != 0);
				REQUIRE(preorderTree.size() == myTree->size());
				REQUIRE(preorderTree[0] == myTree->getRoot());
				REQUIRE(preorderTree.back()->getData() == myTree->getRoot()->getChildren().back()->getChildren().back()->getChildren().back()->getData());
			}
			AND_THEN("The tree can be obtained in post-order traversal") {
				REQUIRE(postorderTree.size() != 0);
				REQUIRE(postorderTree.size() == myTree->size());
				REQUIRE(postorderTree[0]->getData() == myTree->getRoot()->getChildren().front()->getChildren().front()->getData());
				REQUIRE(postorderTree.back()->getData() == myTree->getRoot()->getData());
			}
			AND_THEN("Pre- and post-order traversal aren't the same, but their sizes are") {
				REQUIRE(preorderTree != postorderTree);
				REQUIRE(preorderTree.size() == postorderTree.size());
			}
		}
	}
}
