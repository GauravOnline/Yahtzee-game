//Hash.cpp file
//Description: In this file, I have a Hash Class wich allows me to hash a list according to various functions. Then we compare the performance for those functions.
//Author: Gaurav Shienhmar
//Creation Date : 07/08/2021
#include <string>
#include <fstream>
#include <vector>
#include <math.h> 
#include <iostream>

using namespace std;

//Hash class
class Hash{

public:

	Hash(string textFile);
	int stringLength();
	int firstChar();
	int additive();
	int mystery();
	int bonus();


private:
	const int SIZE = (int) pow(2, 16);
	vector<int> hashTable = vector<int> (SIZE);
	string filename;

};

//Simple constructor
Hash::Hash(string textFile){

	filename = textFile;

}

//This function allows us to hash the list of string according to the string length. 
int Hash::stringLength(){

	fill(hashTable.begin(), hashTable.end(), 0);

	string abc;
	int index;
	int max = 0, min = 0;

	ifstream file (filename);
	    if(file.is_open()){
	    	while(getline(file,abc)){
	    		index = abc.size();
	    	    index = index % SIZE;		    		

	    		hashTable[index]++;

	    		if(hashTable[index] > max){
	    			max = hashTable[index];
	    		}
	    		
	    	}
	    	file.close();
	  	}

	  	for(unsigned k = 0; k < hashTable.size(); k++){
	  		if(min > hashTable[k]){
	  			min =hashTable[k];
	  		}
	  		if(min == 0){
	  			break;
	  		}
	  	}

	  	if(min == 0){

		  	return (max - 1) - min;    //Here max represents the max number of elements at an index. However, the collisions at that index would be max - 1.

	  	}

	  	else{

	  		return max - min;         //(max - 1) - (min - 1)
	  	}


}

//This function allows us to hash the list of string according to the ascii value of first character of the string 
int Hash::firstChar(){

	fill(hashTable.begin(), hashTable.end(), 0);

	string abc;
	int index;
	int max = 0, min = 0;

	ifstream file (filename);
	    if(file.is_open()){

	    	while(getline(file,abc)){

	    		if(abc.size() == 0){
	    			index = 0;
	    		}

	    		else{
	    			index = abs((int)abc.at(0));
	    		}


	    		hashTable[index]++;

	    		if(hashTable[index] > max){
	    			max = hashTable[index];
	    		}

	    		
	    	}
	    	file.close();
	  	}

	  	for(unsigned k = 0; k < hashTable.size(); k++){
	  		if(min > hashTable[k]){
	  			min =hashTable[k];
	  		}
	  		if(min == 0){
	  			break;
	  		}
	  	}

	  	if(min == 0){

		  	return (max - 1) - min;			//Here max represents the max number of elements at an index. However, the collisions at that index would be max - 1.

	  	}

	  	else{

	  		return max - min;				//(max - 1) - (min - 1)
	  	}

}

//This function allows us to hash the list of string according to the ascii values sum of the characters of the string
int Hash::additive(){

	fill(hashTable.begin(), hashTable.end(), 0);

	string abc;
	int index;
	int max = 0, min = 0;

	ifstream file (filename);
	    if(file.is_open()){

	    	while(getline(file,abc)){

	    		
    			index = 0;
    			for(int j = 0; j < (int)abc.size(); j++){

    				index += (abs((int)abc.at(j)));
    			}

    			index = index % SIZE;		    		

	    		hashTable[index]++;

	    		if(hashTable[index] > max){
	    			max = hashTable[index];
	    		}

	    		
	    	}
	    	file.close();
	  	}

	  	for(unsigned k = 0; k < hashTable.size(); k++){
	  		if(min > hashTable[k]){
	  			min =hashTable[k];
	  		}
	  		if(min == 0){
	  			break;
	  		}
	  	}

	  	if(min == 0){

		  	return (max - 1) - min;			//Here max represents the max number of elements at an index. However, the collisions at that index would be max - 1.

	  	}

	  	else{

	  		return max - min;				//(max - 1) - (min - 1)
	  	}

}

//This function allows us to hash the list of string according to the sum of the product of ascii value of characters and its position for each string
int Hash::mystery(){

	fill(hashTable.begin(), hashTable.end(), 0);

	string abc;
	int index;
	int max = 0, min = 0;

	ifstream file (filename);
	    if(file.is_open()){

	    	while(getline(file,abc)){

	    		
    			index = 0;
    			for(int j = 0; j < (int)abc.size(); j++){

    				index += (abs((int)abc.at(j))) * (j + 1);
    			}


    			index = index % SIZE;		    		

	    		hashTable[index]++;

	    		if(hashTable[index] > max){
	    			max = hashTable[index];
	    		}

	    		
	    	}
	    	file.close();
	  	}

	  	for(unsigned k = 0; k < hashTable.size(); k++){
	  		if(min > hashTable[k]){
	  			min =hashTable[k];
	  		}
	  		if(min == 0){
	  			break;
	  		}
	  	}
	  	if(min == 0){

		  	return (max - 1) - min;		//Here max represents the max number of elements at an index. However, the collisions at that index would be max - 1.

	  	}

	  	else{

	  		return max - min;			//(max - 1) - (min - 1)
	  	}

}

// Uses a unique equation to hash the list values.
int Hash::bonus(){

	fill(hashTable.begin(), hashTable.end(), 0);

	string abc;
	int index;
	int max = 0, min = 0;

	ifstream file (filename);
	    if(file.is_open()){

	    	while(getline(file,abc)){

	    		
    			index = 0;
    			for(int j = 0; j < (int)abc.size(); j++){

    				index += pow(((int)abc.at(j)) * (j + 1), 2);
    			}


    			index = index % SIZE;		    		

	    		hashTable[index]++;

	    		if(hashTable[index] > max){
	    			max = hashTable[index];
	    		}

	    		
	    	}
	    	file.close();
	  	}

	  	for(unsigned k = 0; k < hashTable.size(); k++){
	  		if(min > hashTable[k]){
	  			min =hashTable[k];
	  		}
	  		if(min == 0){
	  			break;
	  		}
	  	}
	  	if(min == 0){

		  	return (max - 1) - min;			//Here max represents the max number of elements at an index. However, the collisions at that index would be max - 1.

	  	}

	  	else{

	  		return max - min;			//(max - 1) - (min - 1)
	  	}
}




int main(){


	string filename = "keys1.txt";
	Hash h1(filename);
	cout<<"The difference between the maximum and the minimum collision on the enteries of the hash table using the following hash function are : "<<endl;
	cout<<"String length : "<<h1.stringLength()<<endl;
	cout<<"First Character : "<<h1.firstChar()<<endl;
	cout<<"Additive : "<<h1.additive()<<endl;
	cout<<"Mystery : "<<h1.mystery()<<endl;
	cout<<"Bonus : "<<h1.bonus()<<endl;


	return 0;
}