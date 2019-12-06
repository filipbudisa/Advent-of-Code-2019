#include <iostream>
#include <fstream>
#include "BinaryTreeNode.h"
#include "TreeNode.h"

BinaryTreeNode* loadData(const std::string& path){
	std::ifstream file(path);

	BinaryTreeNode* root = nullptr;

	std::string line;
	while(file >> line){
		std::string name;
		std::string orbiter;

		int index = line.find(')');
		name = line.substr(0, index);
		orbiter = line.substr(index+1);

		if(root){
			root->insert(name, orbiter);
		}else{
			root = new BinaryTreeNode(name, orbiter);
		}
	}

	return root;
}

void constructTree(TreeNode* root, BinaryTreeNode* node){

	BinaryTreeNode* orbitersNode = node->find(root->getName());
	if(!orbitersNode) return;

	std::vector<std::string> orbiters = orbitersNode->getOrbiters();
	for(const std::string& orbiter : orbiters){
		TreeNode* orbiterNode = new TreeNode(orbiter);
		constructTree(orbiterNode, node);
		orbiterNode->setParent(root);
		root->addChild(orbiterNode);
	}
}

int main(){
	BinaryTreeNode* data = loadData("../input.txt");
	TreeNode* root = new TreeNode("COM");
	constructTree(root, data);

	printf("Checksum: %d\n", root->checksum());

	TreeNode* you = root->find("YOU");
	int jumps = you->countJumpsUp("SAN");
	jumps -= 2;

	printf("Jumps: %d\n", jumps);

	// This could be done better for ex. get a list of nodes from root to YOU and root to SAN, find indexes of last
	// node with the same name (point of divergence), and sum the remainder of nodes in both lists (and subtract 2)
}