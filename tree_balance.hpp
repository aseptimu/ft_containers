#ifndef TREE_BALANCE_HPP
# define TREE_BALANCE_HPP

# include "tree.hpp"

namespace ft
{
	template < typename Val >
	static void	tree_rotate_left(Node<Val>* const node, Node<Val>*& root)
	{
		Node<Val>* const tmp = node->_right;

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

	template < typename Val >
	static void	tree_rotate_right(Node<Val>* const node, Node<Val>*& root)
	{
		Node<Val>* const tmp = node->_left;

		node->_left = tmp->_right;
		if (tmp->_right != 0)
			tmp->_right->_parent = node;
		tmp->_parent = node->_parent;
		if (node == root)
			root = tmp;
		else if (node == node->_parent->_right)
			node->_parent->_right = tmp;
		else
			node->_parent->_left = tmp;
		tmp->_right = node;
		node->_parent = tmp;
	}

	template < typename Val >
	void	tree_insert_and_rebalance(const bool insert_left, Node<Val>* node, Node<Val>* parent, Node<Val>& header)
	{
		Node<Val> *& root = header._parent;

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
			Node<Val>* const	_grand = node->_parent->_parent;

			if (node->_parent == _grand->_left)
			{
				Node<Val>* const _uncle = _grand->_right;
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
				Node<Val>* const _uncle = _grand->_left;
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

	template < typename Val >
	Node<Val>*	tree_rebalance_for_erase(Node<Val>* const node, Node<Val>& header)
	{
		Node<Val> *&	root = header._parent;
		Node<Val> *&	min_node = header._left;
		Node<Val> *&	max_node = header._right;
		Node<Val> *		cpy  = node;
		Node<Val> *		tmp = 0;
		Node<Val> *		tmp_parent = 0;

		if (cpy->_left == 0) // save child (if it's alone of none)
			tmp = cpy->_right;
		else
		{
			if (cpy->_right == 0) // only one (left) child
				tmp = cpy->_left;
			else // two children
			{
				cpy = cpy->_right;
				while (cpy->_left != 0)
					cpy = cpy->_left;
				tmp = cpy->_right;
			}
		}
		if (cpy != node) // if two child
		{
			node->_left->_parent = cpy;
			cpy->_left = node->_left;
			if (cpy != node->_right)
			{
				tmp_parent = cpy->_parent;
				if (tmp)
					tmp->_parent = cpy->_parent;
				cpy->_parent->_left = tmp;
				cpy->_right = node->_right;
				node->_right->_parent = cpy;
			}
			else
				tmp_parent = cpy;
			if (root == node)
				root = cpy;
			else if ( node->_parent->_left == node)
				node->_parent->_left = cpy;
			else
				node->_parent->_right = cpy;
			cpy->_parent = node->_parent;
			ft::swap(cpy->_color, node->_color);
			cpy = node;
		}
		else // if one or none child
		{
			tmp_parent = cpy->_parent;
			if (tmp)
				tmp->_parent = cpy->_parent;
			if (root == node)
				root = tmp;
			else
			{
				if (node->_parent->_left == node)
					node->_parent->_left = tmp;
				else
					node->_parent->_right = tmp;
			}
			if (min_node == node)
			{
				if (node->_right == 0)
					min_node = node->_parent;
				else
					min_node = Node<Val>::_Node_min(tmp);
			}
			if (max_node == node)
			{
				if (node->_left == 0)
					max_node = node->_parent;
				else
					max_node = Node<Val>::_Node_max(tmp);
			}
		}
		if (cpy->_color != _red_n) // if delete node is black
		{
			while (tmp != root && (tmp == 0 || tmp->_color == _black_n))
			{
				if (tmp == tmp_parent->_left)
				{
					Node<Val>*	tmp_uncle = tmp_parent->_right;
					if (tmp_uncle->_color == _red_n)
					{
						tmp_uncle->_color = _black_n;
						tmp_parent->_color = _red_n;
						tree_rotate_left(tmp_parent, root);
						tmp_uncle = tmp_parent->_right;
					}
					if ((tmp_uncle->_left == 0 || tmp_uncle->_left->_color == _black_n) && \
						(tmp_uncle->_right == 0 || tmp_uncle->_right->_color == _black_n))
					{
						tmp_uncle->_color = _red_n;
						tmp = tmp_parent;
						tmp_parent = tmp_parent->_parent;
					}
					else
					{
						if (tmp_uncle->_right == 0 || tmp_uncle->_right->_color == _black_n)
						{
							tmp_uncle->_left->_color = _black_n;
							tmp_uncle->_color = _red_n;
							tree_rotate_right(tmp_uncle, root);
							tmp_uncle = tmp_parent->_right;
						}
						tmp_uncle->_color = tmp_parent->_color;
						tmp_parent->_color = _black_n;
						if (tmp_uncle->_right)
							tmp_uncle->_right->_color = _black_n;
						tree_rotate_left(tmp_parent, root);
						break ;
					}
				}
				else // same, but but the left are mirrored to the right
				{
					Node<Val>*	tmp_uncle = tmp_parent->_left;
					if (tmp_uncle->_color == _red_n)
					{
						tmp_uncle->_color = _black_n;
						tmp_parent->_color = _red_n;
						tree_rotate_right(tmp_parent, root);
						tmp_uncle = tmp_parent->_left;
					}
					if ((tmp_uncle->_right == 0 || tmp_uncle->_right->_color == _black_n) && \
						(tmp_uncle->_left == 0 || tmp_uncle->_left->_color == _black_n))
					{
						tmp_uncle->_color = _red_n;
						tmp = tmp_parent;
						tmp_parent = tmp_parent->_parent;
					}
					else
					{
						if (tmp_uncle->_left == 0 || tmp_uncle->_left->_color == _black_n)
						{
							tmp_uncle->_right->_color = _black_n;
							tmp_uncle->_color = _red_n;
							tree_rotate_left(tmp_uncle, root);
							tmp_uncle = tmp_parent->_left;
						}
						tmp_uncle->_color = tmp_parent->_color;
						tmp_parent->_color = _black_n;
						if (tmp_uncle->_left)
							tmp_uncle->_left->_color = _black_n;
						tree_rotate_right(tmp_parent, root);
						break ;
					}
				}
			}
			if (tmp)
			tmp->_color = _black_n;
		}
		return (cpy);
	}
} // namespace ft

#endif