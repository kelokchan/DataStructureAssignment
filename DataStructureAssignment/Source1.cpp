#include<iostream>
using namespace std;

template <class T>
class NodeType {
public:
	T info;
	T index;
	NodeType<T> * next;
};

template <class T>
class LinkedList {
public:
	NodeType<T> * head;
	NodeType<T> * tail;
	int size;

	LinkedList() {
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	~LinkedList() {
		cout << "Going to delete all " << size << " elements of the list." << endl;
		NodeType<T> * current = head;
		while (current != NULL) {
			current = current->next;
			delete head;
			head = current;
		}
	}

	void insertAtBeginning(T col, T value) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = col;
		newNode->next = head;
		head = newNode;
		size++;
		if (tail == NULL)
			tail = newNode;

	}

	void insertAtEnd(T col, T value) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = col;
		newNode->next = NULL;
		if (head == NULL)//inserting to an empty list
			head = tail = newNode;
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	void insertAt(T col, T value, NodeType <T> * &current, NodeType <T> * &prev) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = col;
		newNode->next = current;
		prev = newNode;

		size++;
	}

	void insertValue(T col, T value) {
		//IF the list is empthy or the first node is bigger than newNode, insert at the beginning 
		if (head == NULL || head->index > col)
		{
			this->insertAtBeginning(col, value);
		}
		//IF the last node of the list is bigger than newNode, insert at the end
		else if (tail->index<col) {
			this->insertAtEnd(col, value);
		}
		//ELSE do searching in existing nodes list in order to find the node which is bigger than or equal with newNode.
		//BIGGER THAN : Insert the newNode before it.
		//EQUAL WITH : Replace the value of node.
		else
		{
			NodeType<T> * current = head;
			NodeType<T> * prev = head;

			while (current->index < col) {
				prev = current;
				current = current->next;
			}
			if (current->index == col)
			{
				current->info = value;
			}
			else
			{
				this->insertAt(col, value, current, prev);
			}
		}
	}

	void printValue(T column) {
		NodeType<T>* current = head;
		for (int colIndex = 0; colIndex < column; colIndex++)
		{
			int value = 0;
			if (current != NULL && current->index == colIndex) {
				value = current->info;
				current = current->next;
			}

			int temp_value = value;
			if (temp_value > 0)
			{
				int len;
				for (len = 0; temp_value > 0; len++)
				{
					temp_value = temp_value / 10;
				}

				switch (len)
				{
				case 1: cout << "  " << value << "   "; break;
				case 2: cout << " " << value << "   "; break;
				case 3: cout << " " << value << "  "; break;
				case 4: cout << value << "  "; break;
				case 5: cout << value << " "; break;
				default: break;
				}
			}
			else
			{
				cout << "  " << value << "   ";
			}
		}
	}

	void addValue(LinkedList<int> & list2) {

		NodeType<T> * listA = head;
		NodeType<T> * listB = list2.head;

		//Loop until the listB empty 
		while (listB != NULL)
		{
			if (head == NULL)
			{
				this->insertAtEnd(listB->index, listB->info);
				listB = listB->next;
			}
			else if (head->index > listB->index)
			{
				this->insertAtBeginning(listB->index, listB->info);
				listB = listB->next;
			}
			else if (tail->index< listB->index)
			{
				this->insertAtEnd(listB->index, listB->info);
				listB = listB->next;
			}
			else {

				NodeType<T>* listAPrev;

				while (listA->index < listB->index) {
					listAPrev = listA;
					listA = listA->next;
				}
				if (listA->index == listB->index) {
					listA->info = listA->info + listB->info;
					listA = listA->next;
				}
				else {
					this->insertAt(listB->index, listB->info, listA, listAPrev);
				}
				listB = listB->next;
			}
		}

	}
};

class SM {
public:
	int n; int m; // # rows, # columns
	LinkedList<int>* list;

	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM & other);

};

SM::SM(int rows, int columns) {
	this->n = rows;
	this->m = columns;
	this->list = new LinkedList<int>[rows];
};

SM::~SM() {
	delete[] list;
};

void SM::readElements() {
	int row;
	int col;
	int value;
	int temp = 1;
	do {
		cin >> row;
		cin >> col;
		cin >> value;
		temp = row + col + value;

		if (row< this->n && col< this->m &&temp>0) {
			list[row].insertValue(col, value);
		}
		else {
			if (temp != 0) {
				cout << "Index out of bound.\n";
				abort();
			}
		}
	} while (temp> 0);
	this->printMatrix();
};

void SM::printMatrix() {
	for (int rowIndex = 0; rowIndex < this->n; rowIndex++)
	{
		cout << "[ ";
		list[rowIndex].printValue(this->m);
		cout << " ]" << endl;
	}
};

void SM::addSM(SM & other) {

	for (int row = 0; row < n; row++) {
		this->list[row].addValue(other.list[row]);
	}

};

void main() {
	int rows, columns;
	cout << "Sparse Matrix's Row : ";
	cin >> rows;
	cout << "Sparse Matrix's Column : ";
	cin >> columns;

	SM sm(rows, columns);
	sm.readElements();

	SM sm2(rows, columns);
	sm2.readElements();

	sm.addSM(sm2);
	cout << "Result is...." << endl;
	sm.printMatrix();

	system("pause");
};