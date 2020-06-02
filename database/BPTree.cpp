/**
 * @file BPTree.h
 * @brief the index engine used in database
 * @details B+Tree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-6-2
 */

#include <algorithm>
#include "BPTree.h"

void BPTree::BPTree::insertInternal(int x, Node** cursor, Node** child)
{
	if ((*cursor)->keys.size() < maxIntChildLimit - 1)
	{ // the cursor is not full. Add the key here
		int i = upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x) - (*cursor)->keys.begin();
		(*cursor)->keys.push_back(x);
		(*cursor)->ptr2TreeOrData.ptr2Tree.push_back(*child);

		if (i != (*cursor)->keys.size() - 1)
		{ // shift to the right position
			for (unsigned j = (*cursor)->keys.size() - 1; j > i; j--)
			{  // shifting the position for keys and datapointer
				(*cursor)->keys[j] = (*cursor)->keys[j - 1];
			}

			for (int j = (*cursor)->ptr2TreeOrData.ptr2Tree.size() - 1; j > (i + 1); j--)
			{
				(*cursor)->ptr2TreeOrData.ptr2Tree[j] = (*cursor)->ptr2TreeOrData.ptr2Tree[j - 1];
			}

			(*cursor)->keys[i] = x;
			(*cursor)->ptr2TreeOrData.ptr2Tree[i + 1] = *child;
		}
	}
	else
	{  //splitting

		vector<int> virtualKeyNode((*cursor)->keys);
		vector<Node*> virtualTreePtrNode((*cursor)->ptr2TreeOrData.ptr2Tree);

		int i = std::upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x)
		        - (*cursor)->keys.begin();  //finding the position for x
		virtualKeyNode.push_back(x);
		virtualTreePtrNode.push_back(*child);

		if (i != virtualKeyNode.size() - 1)
		{
			for (int j = virtualKeyNode.size() - 1; j > i; j--)
			{  // shifting the position for keys and datapointer
				virtualKeyNode[j] = virtualKeyNode[j - 1];
			}

			for (int j = virtualTreePtrNode.size() - 1; j > (i + 1); j--)
			{
				virtualTreePtrNode[j] = virtualTreePtrNode[j - 1];
			}

			virtualKeyNode[i] = x;
			virtualTreePtrNode[i + 1] = *child;
		}

		int partitionKey;                                            //exclude middle element while splitting
		partitionKey = virtualKeyNode[(virtualKeyNode.size() / 2)];  //right biased
		unsigned partitionIdx = (virtualKeyNode.size() / 2);

		//resizing and copying the keys & TreePtr to OldNode
		(*cursor)->keys.resize(partitionIdx);
		(*cursor)->ptr2TreeOrData.ptr2Tree.resize(partitionIdx + 1);
		(*cursor)->ptr2TreeOrData.ptr2Tree.reserve(partitionIdx + 1);
		for (unsigned j = 0; j < partitionIdx; j++)
		{
			(*cursor)->keys[j] = virtualKeyNode[j];
		}

		for (unsigned j = 0; j < partitionIdx + 1; j++)
		{
			(*cursor)->ptr2TreeOrData.ptr2Tree[j] = virtualTreePtrNode[j];
		}

		Node* newInternalNode = new Node;
		new(&newInternalNode->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
		//Pushing new keys & TreePtr to NewNode

		for (int j = partitionIdx + 1; j < virtualKeyNode.size(); j++)
		{
			newInternalNode->keys.push_back(virtualKeyNode[j]);
		}

		for (int j = partitionIdx + 1; j < virtualTreePtrNode.size(); j++)
		{  // because only key is excluded not the pointer
			newInternalNode->ptr2TreeOrData.ptr2Tree.push_back(virtualTreePtrNode[j]);
		}

		if ((*cursor) == root)
		{
			/*
				If cursor is a root we create a new Node
			*/
			Node* newRoot = new Node;
			newRoot->keys.push_back(partitionKey);
			new(&newRoot->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
			newRoot->ptr2TreeOrData.ptr2Tree.push_back(*cursor);
			//// now, newRoot->ptr2TreeOrData.ptr2Tree is the active member of the union
			newRoot->ptr2TreeOrData.ptr2Tree.push_back(newInternalNode);

			root = newRoot;
		}
		else
		{
			/*
				::Recursion::
			*/
			insertInternal(partitionKey, findParent(root, *cursor), &newInternalNode);
		}
	}
}

BPTree::Node** BPTree::BPTree::findParent(Node* cursor, Node* child)
{
	return nullptr;
}

BPTree::Node* BPTree::BPTree::firstLeftNode(Node* cursor)
{
	return nullptr;
}

BPTree::BPTree::BPTree()
{

}

BPTree::BPTree::BPTree(int degreeInternal, int degreeLeaf)
{

}

BPTree::Node* BPTree::BPTree::getRoot()
{
	return nullptr;
}

int BPTree::BPTree::getMaxIntChildLimit()
{
	return 0;
}

int BPTree::BPTree::getMaxLeafNodeLimit()
{
	return 0;
}

void BPTree::BPTree::setRoot(BPTree::Node*)
{

}

void BPTree::BPTree::display(BPTree::Node* cursor)
{

}

void BPTree::BPTree::seqDisplay(BPTree::Node* cursor)
{

}

void BPTree::BPTree::search(int key)
{

}

void BPTree::BPTree::insert(int key, FILE* filePtr)
{

}

void BPTree::BPTree::removeKey(int key)
{

}

void BPTree::BPTree::removeInternal(int x, BPTree::Node* cursor, BPTree::Node* child)
{

}
