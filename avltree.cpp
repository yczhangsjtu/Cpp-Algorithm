#include <cstdio>
#include <cstdlib>

template<typename T>
class AVLTree
{
public:
	class Node
	{
	public:
		T data;
		int height;
		int size;
		Node * parent;
		Node * left_child;
		Node * right_child;
	public:
		Node(T val)
		{
			data = val;
			height = 0;
			size = 1;
			parent = (Node*)0;
			left_child = (Node*)0;
			right_child = (Node*)0;
		}
		T getData()
		{
			return data;
		}
		int getHeight()
		{
			return height;
		}
		int getSize()
		{
			return size;
		}
		int updateHeight()
		{
			if(left_child != 0 && right_child != 0)
			{
				if(left_child->getHeight() > right_child->getHeight())
					height = left_child->getHeight() + 1;
				else
					height = right_child->getHeight() + 1;
			}
			else if(left_child != 0)
				height = left_child->getHeight() + 1;
			else if(right_child != 0)
				height = right_child->getHeight() + 1;
			else
				height = 0;
			return height;
		}
		int updateSize()
		{
			if(left_child != 0 && right_child != 0)
			{
				size = left_child->getSize() + right_child->getSize() + 1;
			}
			else if(left_child != 0)
				size = left_child->getSize() + 1;
			else if(right_child != 0)
				size = right_child->getSize() + 1;
			else
				size = 1;
			return size;
		}
		int getBalance()
		{
			Node * n = this;
			if(n->getLeftChild() != 0 && n->getRightChild() !=0)
				return n->getLeftChild()->getHeight() - n->getRightChild()->getHeight();
			else if(n->getLeftChild() != 0)
				return n->getLeftChild()->getHeight() + 1;
			else if(n->getRightChild() != 0)
				return (-1) * (n->getRightChild()->getHeight() + 1);
			else
				return 0;
		}
		Node* getParent()
		{
			return parent;
		}
		void removeParent()
		{
			parent = (Node*)0;
		}
		Node* getLeftChild()
		{
			return left_child;
		}
		Node* setLeftChild(Node* new_left)
		{
			if(new_left != 0) new_left->parent = this;
			left_child = new_left;
			updateHeight();
			updateSize();
			return left_child;
		}
		Node* getRightChild()
		{
			return right_child;
		}
		Node* setRightChild(Node* new_right)
		{
			if(new_right != 0) new_right->parent = this;
			right_child = new_right;
			updateHeight();
			updateSize();
			return right_child;
		}
	};

	void setRoot(Node* n)
	{
		root = n;
		if(root != 0) root->removeParent();
	}

	int size(Node *t)
	{
		if(t) return t->getSize();
		return 0;
	}

	int height(Node *t)
	{
		if(t) return t->getHeight();
		return -1;
	}

	T rank(int r)
	{
		return rank(r,root)->data;
	}

	Node* rank(int r, Node *n)
	{
		if(n == NULL) return NULL;
		int s = size(n->right_child);
		if(s >= r)
			return rank(r,n->right_child);
		if(s + 1 == r)
			return n;
		return rank(r-s-1,n->left_child);
	}


	Node* findNode(T val)
	{
		Node* temp = root;
		while(temp != 0)
		{
			if(val == temp->getData())
				return temp;

			else if(val < temp->getData())
				temp = temp->getLeftChild();

			else
				temp = temp->getRightChild();
		}
		return (Node*)0;
	}
	void rotateLeft(Node * n)
	{
		Node * p = n->getParent();
		enum {left, right} side;
		if(p != 0)
		{
			if(p->getLeftChild() == n)
				side = left;
			else
				side = right;
		}
		Node * temp = n->getRightChild();
		n->setRightChild(temp->getLeftChild());
		temp->setLeftChild(n);
		// Now attach the subtree to the parent (or root)
		if(p != 0)
		{
			if(side == left)
				p->setLeftChild(temp);
			if(side == right)
				p->setRightChild(temp);
		}
		else
		{
			setRoot(temp);
		}
	}

	void rotateRight(Node * n)
	{
		Node * p = n->getParent();
		enum {left, right} side;
		if(p != 0)
		{
			if(p->getLeftChild() == n)
				side = left;
			else
				side = right;
		}
		Node * temp = n->getLeftChild();
		n->setLeftChild(temp->getRightChild());
		temp->setRightChild(n);
		// Now attach the subtree to the parent (or root)
		if(p != 0)
		{
			if(side == left)
				p->setLeftChild(temp);
			if(side == right)
				p->setRightChild(temp);
		}
		else
		{
			setRoot(temp);
		}
	}

	// This function does balancing at the given node
	void balanceAtNode(Node* n)
	{			
		int bal = n->getBalance();
		if(bal > 1)
		{
			if(n->getLeftChild()->getBalance() < 0)
				rotateLeft(n->getLeftChild());
			rotateRight(n);
		}
		else if(bal < -1)
		{
			if(n->getRightChild()->getBalance() > 0)
				rotateRight(n->getRightChild());
			rotateLeft(n);
		}
	}

	Node * root;

public:
	AVLTree()
	{
		root = (Node*)0;
	}

	AVLTree(T val)
	{
		root = new Node(val);
	}

	AVLTree * findSubtree(T val)
	{
		Node* target;
		target = findNode(val);

		if(target != 0)
		{
			AVLTree* subtree = new AVLTree();
			subtree->root = target;
			return subtree;
		}
		else
			return (AVLTree*)0;
	}

	// Returns:
	// 		true: If addition is successful
	// 		false: If item already exists
	//
	bool insert(T val)
	{
		Node* added_node;
		if(root == 0)
		{
			root = new Node(val);
			return true;
		}
		else
		{
			Node* temp = root;

			while(true)
			{
				if(temp->getData() > val)
				{
					if((temp->getLeftChild()) == 0)
					{
						added_node = temp->setLeftChild(new Node(val));
						break;
					}
					else
					{
						temp = temp->getLeftChild();
					}

				}
				else if(temp->getData() < val)
				{
					if((temp->getRightChild()) == 0)
					{
						added_node = temp->setRightChild(new Node(val));
						break;
					}
					else
					{
						temp = temp->getRightChild();
					}

				}
				else
				{
					return false;
				}
			}
			// The following code is for updating heights and balancing.
			temp = added_node;
			while(temp != 0)
			{
				temp->updateHeight();
				temp->updateSize();
				balanceAtNode(temp);
				temp = temp->getParent();
			}
		}
	}

	// Returns:
	// 		true: If removal is successful
	// 		false: If item is not found in the tree
	//
	bool remove(T val)
	{
		if(root == 0) return false;
		Node *replacement, *replacement_parent, *temp_node;
		Node * to_be_removed = findNode(val);			
		if(to_be_removed == 0) return false;

		Node * p = to_be_removed->getParent();

		enum {left, right} side;
		if(p != 0)
		{
			if(p->getLeftChild() == to_be_removed) side = left;
			else side = right;
		}

		int bal = to_be_removed->getBalance();

		if(to_be_removed->getLeftChild() == 0 && to_be_removed->getRightChild() == 0)
		{
			if(p != 0)
			{
				if(side == left) p->setLeftChild((Node*)0);
				else p->setRightChild((Node*)0);

				delete to_be_removed;
				p->updateHeight();
				p->updateSize();
				balanceAtNode(p);
			}
			else
			{
				setRoot((Node*)0);
				delete to_be_removed;
			}

		}
		else if(to_be_removed->getRightChild() == 0)
		{
			if(p != 0)
			{
				if(side == left) p->setLeftChild(to_be_removed->getLeftChild());
				else p->setRightChild(to_be_removed->getLeftChild());

				delete to_be_removed;
				p->updateHeight();
				p->updateSize();
				balanceAtNode(p);
			}
			else
			{
				setRoot(to_be_removed->getLeftChild());
				delete to_be_removed;
			}
		}

		else if(to_be_removed->getLeftChild() == 0)
		{
			if(p != 0)
			{
				if(side == left) p->setLeftChild(to_be_removed->getRightChild());
				else p->setRightChild(to_be_removed->getRightChild());

				delete to_be_removed;
				p->updateHeight();
				p->updateSize();
				balanceAtNode(p);
			}
			else
			{
				setRoot(to_be_removed->getRightChild());
				delete to_be_removed;
			}
		}
		else
		{
			if(bal > 0)
			{
				if(to_be_removed->getLeftChild()->getRightChild() == 0)
				{
					replacement = to_be_removed->getLeftChild();
					replacement->setRightChild(to_be_removed->getRightChild());

					temp_node = replacement;


				}
				else
				{
					replacement = to_be_removed->getLeftChild()->getRightChild();
					while(replacement->getRightChild() != 0)
					{
						replacement = replacement->getRightChild();
					}
					replacement_parent = replacement->getParent();
					replacement_parent->setRightChild(replacement->getLeftChild());

					temp_node = replacement_parent;

					replacement->setLeftChild(to_be_removed->getLeftChild());
					replacement->setRightChild(to_be_removed->getRightChild());
				}
			}
			else
			{
				if(to_be_removed->getRightChild()->getLeftChild() == 0)
				{
					replacement = to_be_removed->getRightChild();
					replacement->setLeftChild(to_be_removed->getLeftChild());

					temp_node = replacement;


				}
				else
				{
					replacement = to_be_removed->getRightChild()->getLeftChild();
					while(replacement->getLeftChild() != 0)
					{
						replacement = replacement->getLeftChild();
					}
					replacement_parent = replacement->getParent();
					replacement_parent->setLeftChild(replacement->getRightChild());

					temp_node = replacement_parent;

					replacement->setLeftChild(to_be_removed->getLeftChild());
					replacement->setRightChild(to_be_removed->getRightChild());
				}
			}		
			if(p != 0)
			{
				if(side == left) p->setLeftChild(replacement);
				else p->setRightChild(replacement);

				delete to_be_removed;
			}
			else
			{
				setRoot(replacement);
				delete to_be_removed;
			}

			balanceAtNode(temp_node);
		}

	}
	int getSize()
	{
		return root->getSize();
	}
	int getHeight()
	{
		return root->getHeight();
	}
};

int main()
{
	AVLTree<int> T;
	for(int i = 0; i < 100; i++)
		T.insert(i);
	for(int i = 0; i < 50; i++)
		T.remove(i+50);
	for(int i = 1; i <= 50; i++)
		printf("%d\n",T.rank(i));
	return 0;
}
