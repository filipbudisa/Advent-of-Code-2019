#include "BinaryTreeNode.h"

void BinaryTreeNode::setLeft(BinaryTreeNode* node){
	left = node;
}

void BinaryTreeNode::setRight(BinaryTreeNode* node){
	right = node;
}

BinaryTreeNode* BinaryTreeNode::getLeft(){
	return left;
}

BinaryTreeNode* BinaryTreeNode::getRight(){
	return right;
}

BinaryTreeNode* BinaryTreeNode::find(const std::string& term){
	if(name == term) return this;

	if(name.compare(term) > 0 && right){
		return right->find(term);
	}else if(left) return left->find(term);

	return nullptr;
}

void BinaryTreeNode::insert(const std::string& _name, const std::string& orbiter){
	if(name == _name){
		orbiters.push_back(orbiter);
	}

	if(name.compare(_name) > 0){
		if(right){
			right->insert(_name, orbiter);
		}else{
			right = new BinaryTreeNode(_name, orbiter);
		}
	}else{
		if(left){
			left->insert(_name, orbiter);
		}else{
			left = new BinaryTreeNode(_name, orbiter);
		}
	}
}

const std::vector<std::string> &BinaryTreeNode::getOrbiters() const{
	return orbiters;
}
