#include "TreeNode.h"

void TreeNode::addChild(TreeNode* child){
	children.push_back(child);
}

unsigned TreeNode::countDirect(){
	return children.size();
}

unsigned TreeNode::countIndirect(){
	unsigned sum = 0;

	for(TreeNode* c : children){
		sum += c->countDirect() + c->countIndirect();
	}

	return sum;
}

unsigned TreeNode::checksum(){
	unsigned sum = countDirect() + countIndirect();

	for(TreeNode* c : children){
		sum += c->checksum();
	}

	return sum;
}

TreeNode* TreeNode::find(const std::string& _name){
	if(name == _name) return this;

	TreeNode* found = nullptr;

	for(TreeNode* c : children){
		found = c->find(_name);
		if(found) break;
	}

	return found;
}

const std::string &TreeNode::getName() const{
	return name;
}

void TreeNode::setParent(TreeNode *parent){
	TreeNode::parent = parent;
}

int TreeNode::countJumps(const std::string &term){
	if(name == term) return 0;

	for(TreeNode* c : children){
		if(c->find(term)){
			return 1 + c->countJumps(term);
		}
	}

	return -1;
}

int TreeNode::countJumpsUp(const std::string &term){
	int jumps = countJumps(term);

	if(jumps == -1){
		if(!parent) return -1;
		int parentJumps = parent->countJumpsUp(term);

		if(parentJumps == -1){
			return -1;
		}else{
			return 1 + parentJumps;
		}
	}else{
		return jumps;
	}
}

TreeNode *TreeNode::getParent() const{
	return parent;
}
