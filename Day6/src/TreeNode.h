#ifndef DAY6_TREENODE_H
#define DAY6_TREENODE_H


#include <string>
#include <vector>
#include <optional>

class TreeNode {
public:
	TreeNode(const std::string& name) : name(name) {}

	TreeNode* find(const std::string& name);

	void addChild(TreeNode* child);
	unsigned countDirect();
	unsigned countIndirect();
	unsigned checksum();

	const std::string &getName() const;

	void setParent(TreeNode *parent);

	TreeNode *getParent() const;

	/**
	 * Counts number of jumps from the current node to the desired child node.
	 * @param term Child node name
	 * @return Number of jumps, or -1 if the child node doesn't exist in the subtree
	 */
	int countJumps(const std::string& term);

	/**
	 * Counts number of jumps from the current node to the desired node in the tree.
	 * @param term Child node name
	 * @return Number of jumps, or -1 if the child doesn't exist in the tree
	 */
	int countJumpsUp(const std::string& term);

private:
	std::string name;
	std::vector<TreeNode*> children;
	TreeNode* parent = nullptr;
};


#endif //DAY6_TREENODE_H
