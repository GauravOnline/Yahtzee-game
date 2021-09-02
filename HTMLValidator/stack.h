/*
This file implement stacks.
*/

//stack.h file
//Description: This class represents a stack of vectors. It allows to to push and pop element from the top of the stack
//Author: Gaurav Shienhmar
//Creation Date : 06/03/2021


#ifndef STACK_H
#define STACK_H

#include <vector>
using namespace std;

template <typename T>
class Stack{

public:


	Stack(){

		top = -1; //default value
	}

	~Stack(){
		v.clear();
	}

	void push(T ch){
		v.push_back(ch); //pushing an element
		top++;
	}
    
	T pop(){

		if(isEmpty()){
			throw std::runtime_error("ERROR: Invalid Expression"); //trying to pop from an empty stack will cause runtime error.
		}
		T poped = v[top];
		top--;
		v.pop_back();
		return poped;
	}

	int stackSize(){
		return top;
	}

	T topValue(){
		if(isEmpty()){
			throw std::runtime_error("ERROR: Invalid Expression"); //trying to access top of an empty stack will cause runtime error.
		}
		return v[top];
	}



	bool isEmpty(){
		if(top == -1){
			return true;
		}
		else{
			return false;
		}
	}



private:
	vector<T> v;
	int top;
};

#endif