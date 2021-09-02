// semiHanoi.cpp
// Description: This program allows us to recursively solve the problem of a semi hanoi with input of 2n
// Author: Gaurav Shienhmar
// Creation date: 06/05/2021

#include <iostream>
using namespace std;

//Counting number of movements
//Just an addition int& movements parameter is added to keep a trace of the movements
void Hanoi(int n, char source, char temp, char destination , int & movements);

//input q which is = 2n and source, source2, destination representing three pegs.
//if there are 2 disks only, we put them on destination peg. Otherwise we recall the function for 2 discs less.
//When the q-2 discs are transfered to destination, we call Hanoi to transfer them to source2 containing 
//the odd number discs and then trasfer the largest even numbered disk from source to destination.
//After this we transfer all discs from source2 to destination 
int semiHanoi(int q, char source, char source2, char destination){

	int movements = 0;

	if(q == 2){
		cout<<"\nMove disk "<<q<<"from "<<source<<" to "<<destination; 
		cout<<"\nMove disk "<<q - 1<<"from "<<source2<<" to "<<destination;
		movements =2;
		return movements; 
	}

	else{
		movements += semiHanoi(q - 2, source, source2, destination);
		Hanoi(q - 2, destination, source, source2, movements);
		cout<<"\nMove disk "<<q<<" from "<<source<<" to "<<destination;
		movements++;
		Hanoi(q-1, source2, source, destination, movements);
		return movements;
	}
}

void Hanoi(int n, char source, char temp, char destination, int & movements ){
	if(n == 1){
		cout<<"\nMove disk 1 from "<<source<<" to "<<destination;
		movements++;
	}

	else{
		Hanoi(n-1,source, destination, temp, movements);
		cout<<"\nMove disk "<<n<<" from "<<source<<" to "<<destination;
		movements++;
		Hanoi(n-1, temp, source, destination, movements);
	}
}

int main(){

	cout<<"The number of moves for n =2 and 2n = 4  disks are : "<<endl;
	int q = 4;
	int count = semiHanoi(q,'A','B','C');
	cout<<"\nMovement Count = "<<count;
	return 0;
}