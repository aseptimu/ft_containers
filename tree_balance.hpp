#ifndef TREE_BALANCE_HPP
# define TREE_BALANCE_HPP

# include "tree.hpp"

namespace ft
{
	static void	tree_rotate_left(NodeBase* const node, NodeBase*& root)
	{
		NodeBase* const tmp = node->_right;

		node->_right = tmp->_left;
		if (tmp->_left != 0)
			tmp->_left->_parent = node;
		tmp->_parent = node->_parent;
		if (node == root)
			root = tmp;
		else if (node == node->_parent->_left)
			node->_parent->_left = tmp;
		else
			node->_parent->_right = tmp;
		tmp->_left = node;
		node->_parent = tmp;
	}

	static void	tree_rotate_right(NodeBase* const node, NodeBase*& root)
	{
		NodeBase* const tmp = node->_left;

		node->_left = tmp->_right;
		if (tmp->_right != 0)
			tmp->_right->_parent = node;
		if (node == root)
			root = tmp;
		else if (node == node->_parent->_right)
			node->_parent->_right = tmp;
		else
			node->_parent->_left = tmp;
		tmp->_right = node;
		node->_parent = tmp;
	}

	void	tree_insert_and_rebalance(const bool insert_left, NodeBase* node, NodeBase* parent, NodeBase* header)
	{
		NodeBase *& root = header->_parent;

		
	}
} // namespace ft

#endif