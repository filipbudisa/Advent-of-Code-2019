#ifndef DAY6_BINARYTREENODE_H
#define DAY6_BINARYTREENODE_H


#include <string>
#include <optional>
#include <vector>

class BinaryTreeNode {
public:
	BinaryTreeNode(const std::string& name, const std::string& orbiter) : name(name) { orbiters.push_back(orbiter); }

	void setLeft(BinaryTreeNode* node);
	void setRight(BinaryTreeNode* node);

	BinaryTreeNode* getLeft();
	BinaryTreeNode* getRight();

	BinaryTreeNode* find(const std::string& term);
	void insert(const std::string& _name, const std::string& orbiter);

	const std::vector<std::string> &getOrbiters() const;

private:
	std::string name;
	std::vector<std::string> orbiters;

	BinaryTreeNode* left;
	BinaryTreeNode* right;
};


#endif //DAY6_BINARYTREENODE_H
