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

	void	tree_insert_and_rebalance(const bool insert_left, NodeBase* node, NodeBase* parent, NodeBase& header)
	{
		NodeBase *& root = header._parent;

		// Fields initialization in new node
		node->_parent = parent;
		node->_left = 0;
		node->_right = 0;
		node->_color = _red_n;

		// Insertion. Creating dependences
		if (insert_left)
		{
			parent->_left = node;

			if (parent == &header)
			{
				header._parent = node;
				header._right = node;
			}
			else if (parent == header._left)
				header._left = node;
		}
		else
		{
			parent->_right = node;

			if (parent == header._right)
				header._right = node;
		}
		while (node != root && node->_parent->_color == _red_n)
		{
			NodeBase* const	_grand = node->_parent->_parent;

			if (node->_parent == _grand->_left)
			{
				NodeBase* const _uncle = _grand->_right;
				if (_uncle && _uncle->_color == _red_n)
				{
					node->_parent->_color = _black_n;
					_uncle->_color = _black_n;
					_grand->_color = _red_n;
					node = _grand;
				}
				else
				{
					if (node == node->_parent->_right)
					{
						node = node->_parent;
						tree_rotate_left(node, root);
					}
					node->_parent->_color = _black_n;
					_grand->_color = _red_n;
					tree_rotate_right(_grand, root);
				}
			}
			else
			{
				NodeBase* const _uncle = _grand->_left;
				if (_uncle && _uncle->_color == _red_n)
				{
					node->_parent->_color = _black_n;
					_uncle->_color = _black_n;
					_grand->_color = _red_n;
					node = _grand;
				}
				else
				{
					if (node == node->_parent->_left)
					{
						node = node->_parent;
						tree_rotate_right(node, root);
					}
					node->_parent->_color = _black_n;
					_grand->_color = _red_n;
					tree_rotate_left(_grand, root);
				}
			}
		}
		root->_color = _black_n;
	}
} // namespace ft

#endif