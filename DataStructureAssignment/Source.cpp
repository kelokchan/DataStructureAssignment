#include<iostream>
#include<string>
#include <iomanip>

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

	NodeType<T> * checkExisting(int inputIndex) {
		NodeType<T> * current = head;
		while (current != NULL) {
			if (current->index == inputIndex) {
				return current;
			}
			current = current->link;
		}
		return NULL;
	}

	void setValue(T value, int inputIndex) {
		NodeType<T> * existingNode = checkExisting(inputIndex);
		if (existingNode != NULL) {
			existingNode->info = value;
		}
		else {
			NodeType<T> * newNode = new NodeType<T>;
			newNode->info = value;
			newNode->index = inputIndex;

			if (size == 0) {
				insertAtBeginning(value, inputIndex);					//list is empty, put at beginning
			}
			else {
				NodeType<T> * current = head;
				while (current != NULL) {
					if (current->index < inputIndex) {						//first is smaller than input
						if (current->link != NULL) {						//check next
							if (current->link->index > inputIndex) {		//next index is bigger than input
								newNode->link = current->link;				//put newNode in between
								current->link = newNode;
								size++;
								break;
							}
							else {
								current = current->link;					//next index is smaller than input, current shifts to next
							}
						}
						else {
							insertAtEnd(value, inputIndex);					//next not found, insert after current
							break;
						}
					}
					else {
						insertAtBeginning(value, inputIndex);				//first index is bigger than input, put at beginning
						break;
					}
				}
			}
		}
	}


	T getValue(int column) {
		NodeType<T>* current = head;
		while (current != NULL) {
			if (current->index == column) {
				return current->info;
			}
			current = current->link;
		}
		return 0;
	}

	int getSize() {
		return size;
	}

	void printNodes(int column) {
		NodeType<T> * current = head;
		cout << "[";
		for (int i = 0; i < column; i++)
		{		//list not empty
				if (current != NULL && current->index == i) {	//list index == iteration
					cout << right << setw(7) << current->info;	//prints out the info
					current = current->link;		//traverse to next
				}
				else {
					cout << right << setw(7) << "0";
				}
		}
		cout << setw(7) << "]";
		cout << endl;
	}

	void insertAtBeginning(T value, int index) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = index;
		newNode->link = head;
		head = newNode;
		size++;
		if (tail == NULL)
			tail = newNode;
	}

	void insertAtEnd(T value, int index) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = index;
		newNode->link = NULL;
		if (head == NULL)
			head = tail = newNode;
		else {
			tail->link = newNode;
			tail = newNode;
		}
		size++;
	}

	void sumNodes(LinkedList<T> &list2) {
		if (this->size >= list2.size) {
			NodeType<T> * current = head;
			while (current != NULL) {
				NodeType<T> * other = list2.head;
				while (other != NULL) {
					if (current->index == other->index) {
						current->info += other->info;
					}
					other = other->link;
				}
				current = current->link;
			}
		}
		else {
			NodeType<T> * other = list2.head;
			while (other != NULL) {
				NodeType<T> * current = head;
				while (current != NULL) {
					if (other->index == current->index) {
						current->info += other->info;
						break;
					}
					current = current->link;
				}
				//setValue(other->info, other->index);
				other = other->link;
			}
		}
	}
};

template <class T>
class SM {
private:
	int rows;
	int columns;
	LinkedList<int> * rowList;

public:
	SM(int rows, int columns);
	SM(SM & other);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM & other);
};

template<class T>
SM<T>::SM(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	this->rowList = new LinkedList<int>[rows];
	cout << "Going to create a sparse matrix of dimensions " << this->rows << "-" << this->columns << endl;
}

template<class T>
SM<T>::SM(SM<T> & other)
{
	this->rows = other.rows;
	this->columns = other.columns;
	this->rowList = new LinkedList<T>[rows];
	for (int i = 0; i < rows; i++)
	{
		rowList[i] = other.rowList[i];
	}
}

template<class T>
SM<T>::~SM()
{
	cout << "Deleting everything" << endl;
	delete[] rowList;
}

template<class T>
void SM<T>::readElements()
{
	cout << "Fill in the sparse matrix nodes by inputting in following format: rowIndex columnIndex value" << endl;
	cout << "Input 0 0 0 when done..." << endl;

	int inputRow;
	int inputColumn;
	int value;
	bool inputMode = true;
	while (inputMode) {
		cin >> inputRow;
		cin >> inputColumn;
		cin >> value;
		if (inputRow == 0 && inputColumn == 0 && value == 0) {
			inputMode = false;
		}
		else {
			if (inputRow >= rows || inputColumn >= columns) {
				cout << "Index out of bound. Please re-enter" << endl;
			}
			else {
				rowList[inputRow].setValue(value, inputColumn);
			}
		}
	}
}

template<class T>
void SM<T>::printMatrix()
{
	cout << "SIZE: " << rowList[0].getSize() << endl;
	for (int i = 0; i < this->rows; i++)
	{
		rowList[i].printNodes(columns);
	}

	cout << endl;
}

template<class T>
void SM<T>::addSM(SM<T> & other)
{
	cout << "Attempting to add 2 matrices" << endl;
	if (this->rows == other.rows && this->columns == other.columns) {
		for (int i = 0; i < rows; i++)
		{
			rowList[i].sumNodes(other.rowList[i]);
		}
	}
	else {
		cout << "Different dimensions of matrices. Aborting...";
		abort();
	}
}

int main()
{
	cout << "Input sparse matrix dimensions in following format: rowIndex columnIndex " << endl;
	int rows, columns;
	cin >> rows;
	cin >> columns;
	SM<int> sm(rows, columns);
	//	SM<int> sm2(rows, columns);
	sm.readElements();
	//	sm2.readElements();
	sm.printMatrix();
	//	sm2.printMatrix();
	//	SM<int> sm3(sm2);
	//	sm.addSM(sm3);
	//	sm.printMatrix();
	system("pause");
	return 0;
}
