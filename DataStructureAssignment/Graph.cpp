#include <iostream>
using namespace std;

class NodeType {
public:
	int info;
	NodeType * link;
};

class LinkedList {
public:
	NodeType* head;
	NodeType* tail;
	int size;

	LinkedList() {
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	~LinkedList() {
		cout << "Going to delete all " << size << " elements of the list." << endl;
		NodeType * current = head;
		while (current != NULL) {
			current = current->link;
			delete head;
			head = current;
		}
	}

	void print() {
		NodeType * current = head;
		while (current != NULL)
		{
			if (size == 1 || current == tail) {
				cout << current->info << " ";
			}
			else {
				cout << current->info << " - ";
			}
			current = current->link;
		}
		cout << endl;
	}

	void insertAtEnd(int info) {
		NodeType * newNode = new NodeType;
		newNode->info = info;
		newNode->link = NULL;
		if (head == NULL) {
			head = tail = newNode;
		}
		else {
			tail->link = newNode;
			tail = newNode;
		}
		size++;
	}
};

class AGraph {
private:
	int numOfVertices;
	bool containUndirectedEdge = false;
	LinkedList * nodeList;
public:
	AGraph(int numOfVertices);
	~AGraph();
	void addDirectedEdge(int u, int v);
	void addUndirectedEdge(int u, int v);
	void removeDirectedEdge(int u, int v);
	void printTopologicalSort();
	void printAdjacencyList();
};

AGraph::AGraph(int numOfVertices)
{
	this->numOfVertices = numOfVertices;
	nodeList = new LinkedList[numOfVertices];
}

AGraph::~AGraph()
{
	cout << "Deleting graph" << endl;
	delete[] nodeList;
}

void AGraph::addDirectedEdge(int u, int v) {
	if (u < numOfVertices && v < numOfVertices) {
		nodeList[u].insertAtEnd(v);
	}
	else {
		cout << "Value u/v is out of bound." << endl;
	}
}

void AGraph::addUndirectedEdge(int u, int v) {
	if (u < numOfVertices && v < numOfVertices) {
		containUndirectedEdge = true;
		nodeList[u].insertAtEnd(v);
		nodeList[v].insertAtEnd(u);
	}
	else {
		cout << "Value u/v is out of bound." << endl;
	}
}

void AGraph::printAdjacencyList() {
	for (int i = 0; i < numOfVertices; i++)
	{
		cout << "[" << i << "] : ";
		nodeList[i].print();
	}
}

int main() {

	AGraph graph(9);
	graph.addDirectedEdge(7, 1);
	graph.addDirectedEdge(7, 8);
	graph.addDirectedEdge(1, 4);
	graph.addDirectedEdge(1, 6);
	graph.addDirectedEdge(1, 2);
	graph.addDirectedEdge(5, 1);
	graph.addDirectedEdge(3, 8);
	graph.addDirectedEdge(3, 2);
	graph.addDirectedEdge(8, 6);
	graph.printAdjacencyList();
	system("pause");
}
