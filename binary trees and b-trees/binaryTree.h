#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <cassert>;

using namespace std;

template <class elemType>
struct binaryTreeNode
{
	elemType info;
	binaryTreeNode<elemType>* llink;
	binaryTreeNode<elemType>* rlink;
};

template <class elemType>
class binaryTreeType
{
public:
	const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>&);
	bool isEmpty() const;
	void inorderTraversal() const;
	void preorderTraversal() const;
	void postorderTravesal() const;
	int treeHeight() const;
	int treeNodeCount() const;
	int treeLeavesCount() const;
	void destroyTree();
	binaryTreeType(const binaryTreeType<elemType>& otherTree);
	binaryTreeType();
	~binaryTreeType();

protected:
	binaryTreeNode<elemType>* root;

private:
	void copyTree(binaryTreeType<elemType>*& copiedTreeRoot, binaryTreeNode<elemType>* otherTreeRoot);
	void destroy(binaryTreeNode<elemType>*& p);
	void inorder(binaryTreeNode<elemType>* p) const;
	void preorder(binaryTreeNode<elemType>* p) const;
	void postorder(binaryTreeNode<elemType>* p) const;
	int height(binaryTreeNode<elemType>* p) const;
	int max(int x, int y)  const;
	int nodeCount(binaryTreeNode<elemType>* p) const;
	int leavesCount(binaryTreeNode<elemType>* p) const;
};

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType>
{
public:
	bool search(const elemType& searchItem) const;
	void insert(const elemType& searchItem);
	void deleteNode(const elemType& deleteItem);

private:
	void deleteFromTree(binaryTreeNode<elemType>*& p);
};
#endif // !BINARYTREE_H

template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
	return (root == NULL);
}
template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
	root = NULL;
}
template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
	inorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
	preorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::postorderTravesal() const
{
	postorder(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
	return height(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
	return nodeCount(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
	return leavesCount(root);
}
template <class elemType>
void binaryTreeType<elemType>::inorder(binaryTreeNode<elemType>* p) const
{
	if (p != NULL)
	{
		inorder(p->llink);
		cout << p->info << " ";
		inorder(p->rlink);
	}
}
template <class elemType>
void binaryTreeType<elemType>::preorder(binaryTreeNode<elemType>* p) const
{
	if (p != NULL)
	{
		cout << p->info << " ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}
template <class elemType>
void binaryTreeType<elemType>::postorder(binaryTreeNode<elemType>* p) const
{
	if (p != NULL)
	{
		postorder(p->llink);
		postorder(p->rlink);
		cout << p->info << " ";
	}
}
template <class elemType>
int binaryTreeType<elemType>::height(binaryTreeNode<elemType>* p) const
{
	if (p == NULL)
		return 0;
	else
		return 1 + max(height(p->llink), height(p->rlink));
}
template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
	if (x >= y)
		return x;
	else
		return y;
}
template <class elemType>
void binaryTreeType<elemType>::copyTree(binaryTreeType<elemType>*& copiedTreeRoot, binaryTreeNode<elemType>* otherTreeRoot)
{
	if (otherTreeRoot == NULL)
		copiedTreeRoot = NULL;
	else
	{
		copiedTreeRoot = new binaryTreeNode<elemType>;
		copiedTreeRoot->info = otherTreeRoot->info;
		copyTree(copiedTreeRoot->llink, otherRoot->llink);
		copyTree(copied->rlink, otherTreeRoot->rlink);
	}
}
template <class elemType>
void binaryTreeType<elemType>::destroy(binaryTreeNode<elemType>*& p)
{
	if (p != NULL)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}
template <class elemType>
void binaryTreeType<elemType>::destroyTree()
{
	destroy(root);
}
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
	if (this != &otherTree)
	{
		if (root != NULL)
			destroy(root);
		if (otherTree.root == NULL)
			root = NULL;
		else
			copyTree(root, otherTree.root);
	}
	return *this;
}

template <class elemType>
int binaryTreeType<elemType>::nodeCount(binaryTreeNode<elemType>* p) const
{
	if (p == NULL)
		return 0;
	else
		return 1 + nodeCount(p->llink) + nodeCount(p->rlink);
}

template <class elemType>
int binaryTreeType<elemType>::leavesCount(binaryTreeNode<elemType>* p) const
{
	if (p == NULL)
		return 0;
	else
		if (p->llink == NULL && p->rlink == NULL)
			return 1;
		else
			return leavesCount(p->llink) + leavesCount(p->rlink);
}
template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& search) const
{
	binaryTreeNode<elemType>* current;
	bool found = false;

	if (root == NULL)
		cerr << "Cannot search the empty tree." << endl;
	else
	{
		current = root;

		while (current != NULL && !found)
		{
			if (current->info == searchItem)
				found = true;
			else if (current->info > searchItem)
				current = current->llink;
			else
				current = current->rlink;
		}
	}
	return found;
}
template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
	binaryTreeNode<elemType>* current;
	binaryTreeNode<elemType>* trailCurrent;
	binaryTreeNode<elemType>* newNode;

	newNode = new binaryTreeNode<elemType>;
	assert(newNode != NULL);
	newNode->info = insertItem;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (root == NULL)
		root = newNode;
	else
	{
		current = root;
		while (current != NULL)
		{
			trailCurrent = current;

			if (current->info == insertItem)
			{
				cerr << "The insert item is already in the list - duplicates are not allowed." << insertItem << endl;
				return;
			}
			else if (current->info > insertItem)
				current = current->llink;
			else
				current = current->rlink;
		}
		if (trailCurrent->info > insertItem)
			trailCurrent->llink = newNode;
		else
			trailCurrent->rlink = newNode;
	}
}
template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(binaryTreeNode<elemType>*& p)
{
	binaryTreeNode<elemType>* current;
	binaryTreeNode<elemType>* trailCurrent;
	binaryTreeNode<elemType>* temp;
	if (p == NULL)
		cerr << "Error: the node to be deleted is NULL!" << endl;
	else if (p->llink == NULL && p->rlink == NULL)
	{
		temp = p;
		p = NULL;
		delete temp;
	}
	else if (p->llink == NULL)
	{
		temp = p;
		p = temp->rlink;
		delete temp;
	}
	else if (p->rlink == NULL)
	{
		temp = p;
		p = temp->llink;
		delete temp;
	}
	else
	{
		current = p->llink;
		trailCurrent = NULL;

		while (current->rlink != NULL)
		{
			trailCurrent = current;
			current = current->rlink;
		}
		p->info = current->info;
		
		if (trailCurrent == NULL)
			p->llink = current->llink;
		else
			trailCurrent->rlink = current->llink;
		
		delete current;
	}
}

template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
	binaryTreeNode<elemType>* current;
	binaryTreeNode<elemType>* trailCurrent;
	bool found = false;

	if (root == NULL)
		cout << "Cannot delete from the empty tree." << endl;
	else
	{
		current = root;
		trailCurrent = root;

		while (current != NULL && !found)
		{
			if (current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				if (current->info > deleteItem)
					current = current->llink;
				else
					current = current->rlink;
			}
		}

		if (current == NULL)
			cout << "The delete item is not in the tree." << endl;
		else if (found)
		{
			if (current == root)
				deleteFromTree(root);
			else if (trailCurrent->info > deleteItem)
				deleteFromTree(trailCurrent->llink);
			else
				deleteFromTree(trailCurrent->rlink);
		}
	}
}
