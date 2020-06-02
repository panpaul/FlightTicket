/**
 * @file BPTree.h
 * @brief the index engine used in database
 * @details B+Tree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-6-2
 */

#ifndef _BPTREE_H_
#define _BPTREE_H_

#include <vector>
#include <fstream>

namespace BPTree
{
	using namespace std;

	class Node /// @brief the definition of every node
	{
	 public:
		bool isLeaf; ///< whether it is a leaf node
		vector<int> keys; ///< the instance to save the keys themselves
		Node* ptr2next; ///< Pointer to connect next node for leaf nodes
		union ptr
		{
			vector<Node*> ptr2Tree; ///< Array of pointers to Children sub-trees for intermediate Nodes
			vector<FILE*> dataPtr; ///< Data-Pointer for the leaf node

			ptr();
			~ptr();
		} ptr2TreeOrData;

		friend class BPTree; ///< allow class BPTree to access private data
	 public:
		Node();
	};

	class BPTree ///@brief the b plus tree
	{
		/*
			::For Root Node :=
				The root node has, at least two tree pointers
			::For Internal Nodes:=
				1. ceil(maxIntChildLimit/2)     <=  #of children <= maxIntChildLimit
				2. ceil(maxIntChildLimit/2)-1  <=  #of keys     <= maxIntChildLimit -1
			::For Leaf Nodes :=
				1. ceil(maxLeafNodeLimit/2)   <=  #of keys     <= maxLeafNodeLimit -1
		*/
	 private:
		int maxIntChildLimit;
		int maxLeafNodeLimit;
		Node* root; ///< pointer to the root
		void insertInternal(int x, Node** cursor, Node** child);
		Node** findParent(Node* cursor, Node* child);
		Node* firstLeftNode(Node* cursor);

	 public:
		BPTree();
		BPTree(int degreeInternal, int degreeLeaf);
		Node* getRoot();
		int getMaxIntChildLimit();
		int getMaxLeafNodeLimit();
		void setRoot(Node*);
		void display(Node* cursor);
		void seqDisplay(Node* cursor);
		void search(int key);
		void insert(int key, FILE* filePtr);
		void removeKey(int key);
		void removeInternal(int x, Node* cursor, Node* child);
	};
}
#endif //_BPTREE_H_
