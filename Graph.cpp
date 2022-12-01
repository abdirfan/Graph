/**************************
 * Name: Abdullah Irfan
 * Class: CS141
 * Program# 6 Graph
 *
 *
 * ************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
using namespace std;

//************************** Node *************************

class Node {
public:
	int id;
	Node* pNext;

	Node(int id) {
		this->id = id;
		pNext = NULL;
	}
};

//************************** Graph ****************************
class Graph {
public:
	//add the node with neighborId as the neighbor of nodeId
	void addNeighbor(int nodeId, int neighborId) {
		Node* pHead = vertices[nodeId];
		if (pHead->id == neighborId) {
			return;
		}
	    if (pHead->id > neighborId) {
			Node* newNode = new Node(neighborId);
			Node* next = pHead->pNext;
			newNode->pNext = pHead;
			vertices[nodeId] = newNode;
			
		}
		else {
			bool done = false;
			while (pHead->pNext != NULL && !done) {
				if (pHead->pNext->id == neighborId) {
					done = true;
				}
				else if (pHead->pNext->id > neighborId) {
					Node* newNode = new Node(neighborId);
					newNode->pNext = pHead->pNext;
					pHead->pNext = newNode;
					done = true;
				}
				else {
					pHead = pHead->pNext;
				}
			}
			if (!done)
			{
				pHead->pNext = new Node(neighborId);
			}
		}

	}

	//reads the edge list from file and creates the adjacency list data structure
	void loadGraph(string edgeListFileName) {
		ifstream streamIn;
		streamIn.open(edgeListFileName);
		assert(streamIn.fail() == false);
		while (!streamIn.eof()) {
			int nodeId, neighborId;
			streamIn >> nodeId;
			streamIn >> neighborId;
			int large = neighborId;

			
			while (nodeId >= vertices.size()) {
				vertices.push_back(NULL);
			}
			while (neighborId >= vertices.size())
			{
				vertices.push_back(NULL);
			}
			if (vertices[nodeId] == NULL) {
				vertices[nodeId] = new Node(neighborId);
			}
			else {
				addNeighbor(nodeId, neighborId);
			}
			if (vertices[neighborId] == NULL) {
				vertices[neighborId] = new Node(nodeId);
			}
			else {
				addNeighbor(neighborId, nodeId);
			}
		}
		streamIn.close();
	}

	//writes the adjacency list into the file
	void dumpGraph(string adjListFileName) {
		ofstream streamobj;
		
		streamobj.open(adjListFileName);
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i] != NULL) {
				streamobj << i << ":";
				Node* pHead = vertices[i];
				while (pHead != NULL) {
					streamobj <<  " " << pHead->id ;
					pHead = pHead->pNext;
				}
				streamobj << endl;
			}
		}
		streamobj.close();
	}
	int getNumNeighbors(int nodeId) {
		int count = 0;
		Node* pHead = vertices[nodeId];
		while (pHead != NULL) {
			count++;
			pHead = pHead->pNext;
		}
		return count;
	}

	//returns the number of nodes in the graph
	int getNumVertices() {
		int counter = 0;
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i] != NULL) {
				counter++;
			}
		}
		return counter;
	}
	//Prints number of nodes, number of edges, and maximum degree on terminal
	void printGraphInfo() {
		cout << "number of nodes: " << getNumVertices() << endl;
		int count = 0;
		int maxDegree = 0;
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i] != NULL) {
				int edges = getNumNeighbors(i);   //not sure what this say
				count += edges;
				if (getNumNeighbors(i) > maxDegree) {
					maxDegree = edges;
				}
				
			}
		}
		cout << "number of edges: " << count / 2 << endl;
		//cout << "number of edegs: " << count / 2 << endl;
		cout << "Maximum degree: " << maxDegree;
	}

	//returns the number of neighbor (degree) of a node
	

private:
	vector<Node*> vertices;

};




void run(string edgeListFileName, string adjListFileName) {
	Graph* graph = new Graph();
	graph->loadGraph(edgeListFileName);
	graph->dumpGraph(adjListFileName);
	graph->printGraphInfo();
}

//*****************************************************************************


// The main will be removed for testing, do not add any code in the main function 
int main() {
	//Change the filenames according to your local path.
	string edgeListFileName("karate.txt");
	string adjListFileName("karate_adj.txt");
	run(edgeListFileName, adjListFileName);
	return 0;
}
