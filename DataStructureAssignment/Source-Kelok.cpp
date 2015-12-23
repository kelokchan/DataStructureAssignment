#include<iostream>
#include<string>

using namespace std;

template <class T>
class NodeType {
public:
	T info;
	int index;
	NodeType<T>* link;
};

template <class T>
class LinkedList {
public:
	NodeType<T>* head;
	NodeType<T>* tail;
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
			current = current->link;
			delete head;
			head = current;
		}
	}

	void clear() {
		NodeType<T> * current = head;
		while (head != NULL) {
			current = current->link;
			delete head;
			head = current;
		}
		tail = NULL;
		size = 0;
	}

	void insertAtBeginning(T value, int index) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->link = head;
		newNode->index = index;
		head = newNode;
		size++;

		if (tail == NULL)
			tail = newNode;
	}

	void insertAtEnd(T value, int index) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->link = NULL;
		newNode->index = index;
		if (head == NULL)
			head = tail = newNode;
		else {
			tail->link = newNode;
			tail = newNode;
		}
		size++;
	}

	void insertData(T value, int index) {
		if (size > 0) {
			NodeType<T> * current = head;
			NodeType<T> * newNode = new NodeType<T>;
			newNode->info = value;
			newNode->index = index;
			for (int i = 0; i < size; i++)
			{
				if (current->index > index) {
					current = current->link;
				}
			}
		}
		else {
			insertAtBeginning(value, index);
		}
	}

	void insertDiu(T value, int index) {
		if (index <= size) {//else, may want to give a message or error 
			if (index == 0)
				insertAtBeginning(value);
			else if (index == size)
				insertAtEnd(value);
			else {
				NodeType<T> * newNode = new NodeType<T>;
				newNode->info = value;
				NodeType<T> * prev = head;
				for (int i = 0; i<index - 1; i++)
					prev = prev->link;
				if (prev != NULL) {
					newNode->link = prev->link;
					prev->link = newNode;
				}
				else {

				}
				size++;
			}
		}
		else {
			cout << "Out of bounds" << endl;
		}
	}

	void insertItemAt(T value, int index) {
		if (index <= size) {//else, may want to give a message or error 
			if (index == 0)
				insertAtBeginning(value);
			else if (index == size)
				insertAtEnd(value);
			else {
				NodeType<T> * newNode = new NodeType<T>;
				newNode->info = value;
				NodeType<T> * prev = head;
				for (int i = 0; i<index - 1; i++)
					prev = prev->link;

				newNode->link = prev->link;
				prev->link = newNode;
				size++;
			}
		}
		else {
			cout << "Out of bounds" << endl;
		}
	}

	void setSize(int size) {
		this->size = size;
	}

	int getSize() {
		return size;
	}

	void print() {
		NodeType<T> * current = head;
		cout << " [ " << " ";
		for (int i = 0; i < 3; i++)
		{
			if (current != NULL) {
				
				cout << " " << current->info << " ";
			}
			else {
				cout << " 0 ";
			}
		}
		cout << " ] ";
		cout << endl;
	}

	
	void setItemAt(int index, T & value) {
		if (index<0 || index >= size) {
			cout << "Index out of bound.\n";
			abort();
		}
		NodeType<T> * current = head;
		for (int i = 0; i<index; i++)
			current = current->link;
		current->info = value;
		current->index = index;
	}
};

template <class T>
class SM {
private:
	int rows;
	int columns;
	LinkedList<int> * arrayList;

public:
	SM(){}

	SM(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
		this->arrayList = new LinkedList<int>[rows];
		//for (int i = 0; i < rows; i++)
		//{
		//	arrayList[i] = new LinkedList<int>;
		//}
	}

	~SM(){
		for (int i = 0; i < row; i++)
		{
			delete arrayList[i];
		}
		delete[] arrayList;
	}

	void readElements(){
		int value, inputRow, inputColumn;

		cout << "Input value: " << endl;
		cin >> value;

		cout << "Input row index: " << endl;
		cin >> inputRow;

		cout << "Input column index: " << endl;
		cin >> inputColumn;

		if ((inputRow < rows) && (inputColumn < columns)) {
			arrayList[inputRow].insertAtEnd(value, inputColumn);
		}
		else {
			cout << "Out of bounds..." << endl;
			readElements();
		}
	}
	void printMatrix(){
		for (int i = 0; i < rows; i++)
		{
			arrayList[i].print();
		}
	}
	void addSM(SM & other){}
};

int main() {
	SM<int>  * sm = new SM<int>(3, 3);
	sm->readElements();
	sm->printMatrix();
	system("pause");
}

