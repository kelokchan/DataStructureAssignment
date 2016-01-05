#include<iostream>
using namespace std;

template <class T>
class DoublyNodeType {
public:
	T info;
	T index;
	DoublyNodeType<T> * next;
	DoublyNodeType<T> * prev;
};

template <class T>
class DoublyLinkedList {
public:
	DoublyNodeType<T> * head;
	DoublyNodeType<T> * tail;
	int size;

	DoublyLinkedList() {
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	~DoublyLinkedList() {
		cout << "Going to delete all " << size << " elements of the list." << endl;
		DoublyNodeType<T> * current = head;
		while (current != NULL) {
			current = current->next;
			delete head;
			head = current;
		}
	}

	void insertValue(T col, T value) {
		//IF the list is empthy or the first node is bigger than newNode, insert at the beginning 
		if (head == NULL || head->index>col)
		{
			this->insertAtBeginning(col, value);
		}
		//IF the last node of the list is bigger than newNode, insert at the end
		else if (tail->index<col) {
			this->insertAtEnd(col, value);
		}
		//ELSE do searching in existing nodes list in order to find the node which is bigger than or equal with newNode.
		//BIGGER THAN : point to the bigger one and insert the newNode before it.
		//EQUAL WITH : replace the value of node.
		else
		{
			DoublyNodeType<T> * current = head;
			while (current->index < col) {
				current = current->next;
			}
			if (current->index == col)
			{
				current->info = value;
			}
			else
			{
				DoublyNodeType<T> * newNode = new DoublyNodeType<T>;
				newNode->info = value;
				newNode->index = col;
				newNode->next = current;
				newNode->prev = current->prev;
				current->prev->next = newNode;
				current->prev = newNode;
				size++;
			}
		}
	}

	void insertAtBeginning(T col, T value) {
		DoublyNodeType<T> * newNode = new DoublyNodeType<T>;
		newNode->info = value;
		newNode->index = col;
		newNode->next = head;
		newNode->prev = NULL;
		head = newNode;
		if (tail == NULL)//inserting to an empty list
			tail = newNode;
		else
			newNode->next->prev = newNode;
		size++;
	}

	void insertAtEnd(T col, T value) {
		DoublyNodeType<T> * newNode = new DoublyNodeType<T>;
		newNode->info = value;
		newNode->index = col;
		newNode->next = NULL;
		newNode->prev = tail;
		tail = newNode;
		if (head == NULL)//inserting to an empty list
			head = newNode;
		else
			newNode->prev->next = newNode;
		size++;

	}

	void printValue(T column) {
		DoublyNodeType<T>* current = head;
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

	void addValue(DoublyLinkedList<int> & list) {

		DoublyNodeType<T> * listA = head;
		DoublyNodeType<T> * listB = list.head;
		while (listB != NULL) {
			if (listA != NULL) {

				while (listA->index < listB->index) {
					listA = listA->next;
				}
				if (listA->index == listB->index) {
					listA->info = listA->info + listB->info;

					listA = listA->next;
					listB = listB->next;
				}
				else {
					DoublyNodeType<T> * newNode = new DoublyNodeType<T>;
					newNode->info = listB->info;
					newNode->index = listB->index;

					newNode->next = listA;
					newNode->prev = listA->prev;
					listA->prev->next = newNode;
					listA->prev = newNode;
					size++;

					listB = listB->next;
				}

			}
			else {
				this->insertAtEnd(listB->index, listB->info);
				listB = listB->next;
			}


		}

	}
};

class SM {
public:
	int n; int m; // # rows, # columns
	DoublyLinkedList<int>* list;

	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM & other);

};

SM::SM(int rows, int columns) {
	this->n = rows;
	this->m = columns;
	this->list = new DoublyLinkedList<int>[rows];
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

void main2() {
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