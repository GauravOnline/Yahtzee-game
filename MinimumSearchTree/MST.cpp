//MST.cpp file
//Description: In this file, I create a MST by using reverseKruskal algorithm
//Author: Gaurav Shienhmar
//Creation Date : 07/22/2021
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

//Edge Class
class Edge{

public:

	//constructor
	Edge(int n1, int n2, int wt){
		node1 = n1;
		node2 = n2;
		weight = wt;
	}

	int getWeight(){
		return weight;
	}

	int getNode1(){
		return node1;
	}

	int getNode2(){
		return node2;
	}

	void printEdge(){
		cout<<"City1 : "<<node1<<" City2 : "<<node2<<" distance : "<<weight<<endl;
	}



private:
	int node1;
	int node2;
	int weight;
};


//Graph class
class Graph{


public:


	Graph(int n);
	void insertEdge(int city1, int city2, Edge e1);
	void DFS(int current, vector<bool> &visited);
	bool checkConnected();
	void printGraph();
	int createMST();



private:

	vector<vector<int>> adjacent;
	vector<Edge> edges;
	int order;

};


//Constructor
Graph::Graph(int n){

	order = n;
	adjacent.resize(n);

}

//Helps me insert an edge into the graph
void Graph::insertEdge(int city1, int city2, Edge e1){

	unsigned i;
	for(i = 0; i < edges.size(); i++){
		if(edges[i].getWeight() < e1.getWeight()){

			edges.insert(edges.begin() + i, e1);
			break;

		}
	}

	if(i == edges.size()){

		edges.push_back(e1);

	}

	adjacent[city1].push_back(city2);
	adjacent[city2].push_back(city1);

}

//We check that the graph is connected or not
bool Graph::checkConnected(){

   vector<bool> visited;
   visited.resize(order);

    for(int i = 0; i < order; i++){
    	visited[i] = false;
    }
  
    DFS(0, visited);
  
    for (int i = 0; i < order; i++){
        if (visited[i] == false){
            return false;
        }
    }
  
    return true;
}


//Depth first traversal of the graph
void Graph::DFS(int current, vector<bool> &visited){

    visited[current] = true;

    int adj;
    for(unsigned i = 0; i < adjacent[current].size(); i++){

    	adj = adjacent[current][i];

    	if(!visited[adj]){
    		DFS(adjacent[current][i], visited);
    	}
    }

}
  
//Printing the edges in the graph
void Graph::printGraph(){

	for(unsigned i = 0; i < edges.size(); i++){
		cout<<"City1 : "<<edges[i].getNode1()<<" City2 : "<<edges[i].getNode2()<<" distance : "<<edges[i].getWeight()<<endl;
	}
}


//Here we try to create MST by deleting the high weight edges that causes a cycle in the graph.
//Once all such edges are deleted, we our left with our MST.
int Graph::createMST(){

	int totalWeight = 0;

	for(unsigned i = 0; i < edges.size(); i++){

		int first = edges[i].getNode1();
		int second = edges[i].getNode2();

		
		for(unsigned j = 0; j < adjacent[first].size(); j++){

			if(adjacent[first][j] == second){
				adjacent[first].erase(adjacent[first].begin() + j);
				break;
			}
		}

	
		for(unsigned j = 0; j < adjacent[second].size(); j++){

			if(adjacent[second][j] == first){
				adjacent[second].erase(adjacent[second].begin() + j);
				break;
			}
		}


		if(!checkConnected()){

			adjacent[first].push_back(second);
			adjacent[second].push_back(first);

			totalWeight+= edges[i].getWeight();

		}

		else{
			cout<<"Removed Edge : ";
			edges[i].printEdge();
			edges.erase(edges.begin() + i);
			i--;
		}

	}

    return totalWeight;
}

//This function allows us to read a graph from a file and then create a MST from that.
void reverseKruskal(string filename){


	ifstream file(filename);

	int nodes,city1,city2,distance;

	file >>nodes;

	Graph g(nodes);

	while(file>> city1){

		file >> city2;
		file >> distance;

	    Edge e1(city1, city2, distance);
		g.insertEdge(city1, city2, e1);


	}

	int totalDistance = g.createMST();
	cout<<"\nMST has been formed.";
	cout<<"\nThe edges present in the tree are : "<<endl;
	g.printGraph();
	cout <<"\nTotal distance : "<<totalDistance<<endl;

}




int main(){

	string filename = "sparce7.txt";
	reverseKruskal(filename);
	return 0;
}

