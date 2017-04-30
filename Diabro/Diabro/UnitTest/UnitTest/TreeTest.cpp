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

			AND_THEN("Those childrens data can be obtained") {
				//INFO("Data elements are: " << myTree->getRoot()->getChildAt(0)->getData() << " - " <<
				//	myTree->getRoot()->getChildAt(1)->getData() << " - " <<
				//	myTree->getRoot()->getChildAt(2)->getData());

				REQUIRE(myTree->getRoot()->getChildAt(0)->getData() == 1);
				REQUIRE(myTree->getRoot()->getChildAt(1)->getData() == 2);
				REQUIRE(myTree->getRoot()->getChildAt(2)->getData() == 3);
			}

			AND_WHEN("2 Child nodes are added to the first child of the root") {
				std::vector<int> datanode2;
				datanode2.push_back(100);
				datanode2.push_back(200);
				myTree->addNodes(datanode2, myTree->getRoot()->getChildAt(0));

				THEN("The first node of the root has 2 children") {
					REQUIRE(myTree->getRoot()->getChildAt(0)->getChildren().size() == 2);
				}

				AND_THEN("The data of the children of the first node of root can be obtained") {
					INFO("Data elements are: " << myTree->getRoot()->getChildAt(0)->getChildAt(0)->getData() << " - " <<
						myTree->getRoot()->getChildAt(0)->getChildAt(1)->getData());
					REQUIRE(myTree->getRoot()->getChildAt(0)->getChildAt(0)->getData() == 100);
					REQUIRE(myTree->getRoot()->getChildAt(0)->getChildAt(1)->getData() == 200);
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

/*TEST_CASE("Obtaining data character tree test", "[Tree]") {
	Tree<char>* myTree = new Tree<char>();

}

TEST_CASE("Pre- and post-order traversel floating point tree test", "[Tree]") {
	Tree<float>* myTree = new Tree<float>();

	std::vector<TreeNode<float>*> preorderTree = myTree->preorder();
	for (int i = 0; i < preorderTree.size(); ++i) {
		std::cout << preorderTree[i]->getData() << std::endl;
	}
	std::cout << std::endl;

	preorderTree = myTree->preorder();

	for (int i = 0; i < preorderTree.size(); ++i) {
		std::cout << preorderTree[i]->getData() << std::endl;
	}
}*/
