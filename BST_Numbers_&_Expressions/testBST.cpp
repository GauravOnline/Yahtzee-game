//testBST.cpp file
//Description: This is a tester class for making various binary trees and performing different operations on them.
//Author: Gaurav Shienhmar
//Creation Date : 06/19/2021

  
#include <ctime>    
#include <iostream>
#include <string>
#include "BST.h"
#include"stack.h"

using namespace std;

string getExpression();
BSTree<char> infixExprTree(string infix);
int getInput();
vector<int> genData(int n1);
void printList(vector<int> list);
BSTree<int>  makeBST(vector<int> list);
void remove(int  item, BSTree<int> tree);
string InfixPostfixExpr(string infix);
BSTree<int> mergeBST(BSTree<int> tree1, BSTree<int> tree2);
int height(BSTree<int> tree);
bool precedenceCheck(char ch, char ch2);


template <typename T>
void printBT(BSTree<T> tree);



int main() {

	int n1 = getInput(); 
	vector<int> list1 = genData(n1); 
	cout << "The List1: ";
	printList(list1);
	int n2 = getInput();
	vector<int> list2 = genData(n2);
	cout << "The List2: ";
	printList(list2);
	BSTree<int> bst1 = makeBST(list1);
	cout << "\nIn-order traversal of bst1 is: ";
	printBT(bst1); 

	remove(list1[n1/2], bst1);

	cout << "\nIn-order traversal of bst1 after deleting " <<list1[n1/2] <<" is: ";
	printBT(bst1);

	BSTree<int> bst2 = makeBST(list2);
	cout << "\nIn-order traversal of bst2 is: ";
	printBT(bst2);

	BSTree<int> bst3 = mergeBST(bst1, bst2);
	cout << "\nIn_order traversal of bst3 is: ";
	printBT(bst3);

	cout << "\nThe height of bst1 is " << height(bst1) << endl;
	cout << "The height of bst2 is " << height(bst2) << endl;
	cout << "The height of merged tree is " << height(bst3) << endl;

	string infix = getExpression();
	BSTree<char> bt4 = infixExprTree(infix);
	cout << "In-order traversal of bt4 is: ";
	printBT(bt4);
	cout << "\nThe postfix expression is "<<InfixPostfixExpr(infix)<<endl;

	return 0;
}

//input-> two binary search trees
//we store the pre-Order traversal of two trees in two vectors
//Then we make a new tree by inserting those vector elements
BSTree<int> mergeBST(BSTree<int> tree1, BSTree<int> tree2){
	vector<int> v1 = tree1.preOrderPrint();
	vector<int> v2 = tree2.preOrderPrint();

	BSTree <int> tree3;
	unsigned i;

	for(i = 0; i < v1.size(); i++){
		tree3.insert(v1[i]);
	}

	for(i = 0; i < v2.size(); i++){
		tree3.insert(v2[i]);
	}

	return tree3;

}  


//This function allows us to remove an item from a tree
void remove(int  item, BSTree<int> tree){
	tree.findAndDelete(item);
}

//input -> an infix expression
//We make an expression tree with this infix expression.
//then we store the postfix print of this tree in a vector 
//Then, we put it into a string and return it
string InfixPostfixExpr(string infix){
	BSTree<char> tree = infixExprTree(infix);
	vector<char> vec = tree.postOrderPrint();
	string result = "";

	for(unsigned i = 0; i < vec.size(); i++){
		result.push_back(vec[i]);
	}

	return result;

}

//To get the height of the input tree
int height(BSTree<int> tree){
	return tree.getHeight();
}

//Allows us to get input for list length from the user
int getInput(){

	int input;
	cout<<"\nEnter an integer : ";
	cin>>input;
	return input;
}

//Allows us to generate random integers ranging from -n to n
vector<int> genData(int n){

	srand((unsigned) time(0));

	vector<int> list;
	 list.resize(n);


	for(int i = 0; i < n; i++){

	    list[i]= (rand() % (2 * n)) - n;

	}

	return list;

}

//printing a list
void printList(vector<int> list){

	for(unsigned i = 0; i < list.size(); i++){
		cout<<"\n"<<list[i];
	}
}

//making a tree and inserting list elements in it
BSTree<int>  makeBST(vector<int> list){

	BSTree <int> tree1;
	int x;

	for(unsigned i = 0; i < list.size(); i++){
		x = list[i];
		tree1.insert(x);
	}

	return tree1;
}

//printing the tree elements in in-order traversal
template <typename T>
void printBT(BSTree<T> tree){

	vector<T> vec = tree.inOrderPrint();

	for(unsigned i = 0; i < vec.size(); i++){
		cout<<vec[i]<<" ";
	}
}

//Allows us to make an expression tree from an infix string
BSTree<char> infixExprTree(string infix){

	Stack<BSTNode <char> *> nodes;
	Stack<char> operators;
	char ch;
	BSTNode<char> * temp1, *temp2;

	for(unsigned i = 0; i < infix.length(); i++){

		if(infix[i] == ' '){

		}

		
		else if(infix.at(i) == '('){
			operators.push(infix.at(i));
		}

		else if(infix.at(i) == '+' || infix.at(i) == '-' || infix.at(i) == '*' || infix.at(i) == '/'){

			while(!operators.isEmpty() && precedenceCheck(infix.at(i),operators.topValue())){


				temp2 = nodes.topValue();
				nodes.pop();
				temp1 = nodes.topValue();
				nodes.pop();
				ch = operators.pop();
				BSTNode<char> *newNode = new BSTNode<char>(ch);
				newNode->insertLeft(temp1);
				newNode->insertRight(temp2);
				nodes.push(newNode);
			}
		
			operators.push(infix.at(i));
			
		}

		else if(infix.at(i) == ')'){
			while(operators.topValue() != '('){
				temp2 = nodes.topValue();
				nodes.pop();
				temp1 = nodes.topValue();
				nodes.pop();
				ch = operators.pop();
				BSTNode<char> *newNode = new BSTNode<char>(ch);
				newNode->insertLeft(temp1);
				newNode->insertRight(temp2);
				nodes.push(newNode);
			}
			operators.pop();
		}

		else{

			BSTNode<char> *newNode = new BSTNode<char>(infix.at(i));
			nodes.push(newNode);

		}
		

	}

	while(!operators.isEmpty()){
		temp2 = nodes.topValue();
		nodes.pop();
		temp1 = nodes.topValue();
		nodes.pop();
		ch = operators.pop();
		BSTNode<char> *newNode = new BSTNode<char>(ch);
		newNode->insertLeft(temp1);
		newNode->insertRight(temp2);
		nodes.push(newNode);

	}

	BSTree<char> tree;
	tree.insertRoot(nodes.pop());
	return tree;

}

//check if the precedence of inStack is greater than ch or not.
bool precedenceCheck(char ch, char inStack){

	if(inStack == '('){
		return false;
	}

	else if(ch == '-' || ch ==  '+'){
		return true;
	}


	else if(inStack == '*' || inStack == '/'){
		return true;
	}

	else{
		return false;
	}

}

//Allows us to get  an infix expression from the user
string getExpression(){

	string input;
	cout<<"Enter an infix expression : ";
	getline (cin,input);
	getline (cin,input);

	return input;
}
