//knight.cpp file
//Description: In this file, I try to move my knight from starting location to the end location by finding a shortest path.
//Author: Gaurav Shienhmar
//Creation Date : 07/28/2021
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;


//Position class that represent a location of knight on the chessboard
class position{

public:

	position(){

		weight = INT_MAX;
		prevX = -1;
		prevY = -1;
		checked = false;

	}

	//simple setter
	void setPrev(int xCoord, int yCoord){
		prevX = xCoord;
		prevY = yCoord;
	}

	//simple getter
	int getPrevX(){

		return prevX;

	}

	//simple getter
	int getPrevY(){

		return prevY;

	}

	//the function makes sure that the current postion has been checked for shortest path
	void positionChecked(){

		checked = true;
	}

	//simple getter
	int getWeight(){

		return weight;

	}

	//simple setter
	void setWeight(int wt){

		weight = wt;

	}

	//returns whether the current position has been checked or not
	bool isChecked(){

		return checked;
	}


private:

	int prevX, prevY, weight; 
	bool checked;

};


//We try to find if the adjancent positon exists or not, & if exists, we check the shortest path to that position.
void checkAdjacent(position  obj[][8], int & current_x, int & current_y, int & x, int & y, int & wt){

	if(x >= 0 && y >= 0 && x < 8 && y < 8){

			if(obj[x][y].getWeight() > wt){
				obj[x][y].setPrev(current_x,current_y);
				obj[x][y].setWeight(wt);
			}

	}

}


//This function tries to find a shortest path between the staring and ending position of the knight.
//It uses the Dijkstra approach for finding the shortest path.
void knight_moves(){

	int startX, startY;
	int endX, endY;

	cout<<"\nEnter the current Knight's location: ";
	cin>>startX;
	cin>>startY;
	if(!(startX >= 0 && startY >= 0 && startX < 8 && startY < 8)){
		cout<<"\nINVALID VALUES ENTERED";
		exit(1);
	}

	cout<<"\nEnter the destination location : ";
	cin>>endX;
	cin>>endY;
	if(!(endX >= 0 && endY >= 0 && endX < 8 && endY < 8)){
		cout<<"\nINVALID VALUES ENTERED";
		exit(1);
	}

	position obj[8][8];


	obj[startX][startY].setPrev(startX, startY);
	obj[startX][startY].setWeight(0);

	bool reached = false;

	int x, y;
	int wt;


	int min_wt;
	int current_x;
	int current_y;

	while(!reached){

		min_wt = INT_MAX;

		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){

				if(!obj[i][j].isChecked()){
					if(obj[i][j].getWeight() < min_wt){
						min_wt = obj[i][j].getWeight();
						current_x = i;
						current_y = j;
					}
				}

			}
		}

		obj[current_x][current_y].positionChecked();


		if(current_x == endX && current_y == endY){

			reached = true;
			break;
		}

		wt = min_wt + 1;

		
		x = current_x - 2;
		y = current_y - 1;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x - 1;
		y = current_y - 2;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x + 1;
		y = current_y - 2;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x + 2;
		y = current_y - 1;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x - 2;
		y = current_y + 1;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x - 1;
		y = current_y + 2;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x + 1;
		y = current_y + 2;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

		x = current_x + 2;
		y = current_y + 1;
		checkAdjacent(obj, current_x, current_y, x, y ,wt);

	}

	int trace_x = endX;
	int trace_y = endY;
	int temp1, temp2;

	string str = " ";


	while(!(trace_x == startX && trace_y == startY)){

		str = "[" + to_string(trace_x) + ", " + to_string(trace_y) + "]\n" + str;

		temp1 = obj[trace_x][trace_y].getPrevX();
		temp2 = obj[trace_x][trace_y].getPrevY();
		trace_x = temp1;
		trace_y = temp2;
	}


	str = "[" + to_string(trace_x) + ", " + to_string(trace_y) + "]\n" + str;

	cout<<"\nYou made it in "<<obj[endX][endY].getWeight()<<" moves from ["<<startX<<","<<startY<<"] to ["<<endX<<","<<endY<<"]! Here is your path : "<<endl;

	cout<<str;


}


int main(){

	knight_moves();

	return 0;

}