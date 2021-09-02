//BST.h file
//Description: This class represents a binary search tree and the functions are the different operations on this tree.
//Author: Gaurav Shienhmar
//Creation Date : 06/19/2021
#ifndef BST_H
#define BST_H

#include <iostream>
#include<vector>
using namespace std;

template <typename T>
class BSTree;

//Node class for the required for building tree nodes
template <typename T>
class BSTNode{

public :

	BSTNode(){
		left = right = nullptr;
		parent = nullptr; //yoyo
	}


	void insertLeft(BSTNode<T> *item){
		left = item;
		item->parent = this;

	}

	void insertRight(BSTNode<T> *item){
		right = item;
		item->parent = this;
	}


	BSTNode(const T &e, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr){
		element = e;
		right = r;
		left = l;

		if(l != nullptr)
		r->parent = this;

		if(r != nullptr)
		l->parent = this;
	}

	friend class BSTree<T>;

private:

	T element;
	BSTNode<T> *left, *right, *parent;

};



//Templated Binary Search Tree class
template <typename T>
class BSTree{

public:

	BSTree();
	void insertRoot(BSTNode<T> * temp);
	void insert(T item);
	vector<T> inOrderPrint();
	void inOrderTraversing(BSTNode<T> *temp, vector<T> &vec);
	vector<T> postOrderPrint();
	void postOrderTraversing(BSTNode<T> *temp, vector<T> &vec);
	vector<T> preOrderPrint();
	void preOrderTraversing(BSTNode<T> *temp, vector<T> &vec);
	int getHeight();
	int computeHeight(BSTNode<T>* temp);
	void deleteByCopying(BSTNode<T> *node);
	void findAndDelete(T  item);
	


private:

	BSTNode<T> *root;
};

//Simple constructor
template <typename T>
BSTree<T>::BSTree(){
	root = nullptr;
}

//Function allowing us to insert a root node to the tree
template <typename T>
void BSTree<T>::insertRoot(BSTNode<T> * temp){
	root = temp;
}

//Function for inserting an item.
//This function is taken from the lecture notes provided by instructor Bita Shadgar	
template <typename T>
void BSTree<T>::insert(T item){

	BSTNode<T> * node = new BSTNode<T>(item);

	if(root == nullptr){
		root = node;
	}

	else{

		BSTNode<T> *temp = root;
		BSTNode<T> * prev;

		while(temp){
			prev = temp;

			if(item <= temp->element){

				temp = temp->left;
			}

			else{
				temp = temp->right;
			}

		}

		if(item <= prev->element){
			prev->left = node;
			prev->left->parent = prev;
				
		}

		else{
			prev->right = node;
			prev->right->parent = prev;

		}



	}

		
}

//calls a recursive function inOrderTraversing to store and return the tree elements in form of a vector
template <typename T>
vector<T> BSTree<T>::inOrderPrint(){
	BSTNode<T> * temp = root;
    vector<T> vec;
	inOrderTraversing(temp,vec);
	return vec;
}	

//calls a recursive function postOrderTraversing to store and return the tree elements in form of a vector
template <typename T>
vector<T> BSTree<T>::postOrderPrint(){
	BSTNode<T> * temp = root;
    vector<T> vec;
	postOrderTraversing(temp,vec);
	return vec;
}	

//calls a recursive function preOrderTraversing to store and return the tree elements in form of a vector
template <typename T>
vector<T> BSTree<T>::preOrderPrint(){
	BSTNode<T> * temp = root;
    vector<T> vec;
	preOrderTraversing(temp,vec);
	return vec;
}	

//calls a recursive function computeHeight to get the longest path in the tree
template <typename T>
int BSTree<T>::getHeight(){
	BSTNode<T> *temp = root;
	return computeHeight(temp) - 1;
}

//finds the longest path in the tree
template <typename T>
int BSTree<T>::computeHeight(BSTNode<T>* temp){

	
	if (temp == nullptr){
        return 0;
    }
    else
    {
        int left = computeHeight(temp->left);
        int right = computeHeight(temp->right);
     
        if (left > right){
        	left++;
            return left;
        }
        else{
        	right++;
        	return right;
        }
    }
}

//This function stores tree elements in a vector in pre Order
template <typename T>
void BSTree<T>::preOrderTraversing(BSTNode<T> *temp, vector<T> &vec){
    if(temp==NULL){
        return;
    }
    else{
    	vec.push_back(temp->element);
        preOrderTraversing(temp->left, vec);
        //cout<<temp->element<<" ";
        preOrderTraversing(temp->right, vec);

    }

}
//This function stores tree elements in a vector in Order
template <typename T>
void BSTree<T>::inOrderTraversing(BSTNode<T> *temp, vector<T> &vec){
    if(temp==NULL){
        return;
    }
    else{
        inOrderTraversing(temp->left, vec);
        //cout<<temp->element<<" ";
        vec.push_back(temp->element);
        inOrderTraversing(temp->right, vec);

    }

}

//This function stores tree elements in a vector in post Order
template <typename T>
void BSTree<T>::postOrderTraversing(BSTNode<T> *temp, vector<T> &vec){
    if(temp==NULL){
        return;
    }
    else{
        postOrderTraversing(temp->left, vec);
        postOrderTraversing(temp->right, vec);
        //cout<<temp->element<<" ";
        vec.push_back(temp->element);


    }
}

//This methods deletes the desired node without actually causing any imbalance in the tree
//Also, this function is built from the notes provided by Bita Shadgar in class
template <typename T>
void BSTree<T>::deleteByCopying(BSTNode<T> *node){
	BSTNode<T> *prev;
	BSTNode<T> *temp;
	temp = node->left;
	prev = node;

	while(temp->right != nullptr){
		prev = temp;
		temp = temp->right;
	}

	node->element = temp->element;

	if(prev == node){
		prev->left = temp->left;
	}

	else{
		prev->right = temp->left;
	}

     delete temp;

}

//This method find the node which contains the element to be deleted and delete it 
//either by itself if the node is a leaf node or by calling deleteByCopying otherwise.
//Also, this function is built from the notes provided by Bita Shadgar in class
template <typename T>
void BSTree<T>::findAndDelete(T  item){

	BSTNode<T> *node = root;
	BSTNode<T> *prev = root;

	while(node != nullptr){
		if(node->element == item){
			break;
		}

		if(item < node->element){
			prev = node;
			node = node->left;
		}

		else{
			prev = node;
			node = node->right;
		}
	}

	
	if(node->right == nullptr){

		if(prev->element > node->element){
			prev->left = node->left;
		}

		else{
			prev->right = node->left;
		}
		delete node;

	}

	else if(node->left == nullptr){

		if(prev->element > node->element){
			prev->left = node->right;
		}

		else{
			prev->right = node->right;
		}

		delete node;
	}

	else if(node != nullptr && node->element == item){
		deleteByCopying(node);
	}

	else if(root!= nullptr){
		cout<<"\n Element "<<item<<" is not in the tree";
	}

	else{
		cout<<"\n The tree is empty";
	}

}

#endif