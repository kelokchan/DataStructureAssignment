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

	//copy constructor
	LinkedList(const LinkedList & other) {
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
		NodeType<T> * current = other.head;
		while (current != NULL) {
			this->setValue(current->info, current->index);
			current = current->link;
		}
	}

	//LinkedList &operator =(const LinkedList & other) {
	//	NodeType<T> * current = other.head;
	//	while (current != NULL) {
	//		this->setValue(current->info, current->index);
	//		current = current->link;
	//	}
	//	return *this;
	//}

	//assignment operator
	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other) {
			return *this;
		}

		LinkedList temp(other); // uses copy constructor
		swap(temp.size, size);
		swap(temp.head, head);
		swap(temp.tail, tail);
		return *this;
	}

	~LinkedList() {
		//		cout << "Going to delete all " << size << " elements of the list." << endl;
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

	void insertValue(T value, int inputIndex, NodeType<T> * &prev) {
		NodeType<T> * newNode = new NodeType<T>;
		newNode->info = value;
		newNode->index = inputIndex;
		newNode->link = prev->link;
		prev->link = newNode;
		size++;
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
		if (tail == NULL)
			tail = newNode;
		size++;
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

	void sPrint() {
		NodeType<T> * current = head;
		while (current != NULL) {
			cout << " " << current->info << " ";
			current = current->link;
		}
	}

	void sumNodes(LinkedList<T> &list2) {
		NodeType<T> * current = head;
		NodeType<T> * other = list2.head;
		NodeType<T> * prev = NULL;
		while (other != NULL) {
			if (current != NULL) {
				if (current->index > other->index) {							//other index < current index, insert other until other >= current index
					this->setValue(other->info, other->index);
					other = other->link;
				}
				else {
					while (current->index < other->index) {						//traverse until current index >= other index, current info remains
						prev = current;
						if (current->link != NULL) {
							current = current->link;
						}
						else {
							break;
						}
					}
					if (current->index == other->index) {
						current->info += other->info;
						prev = current;
						current = current->link;
						other = other->link;
					}
					else {												//current > other
						this->insertValue(other->info, other->index, prev);
						//this->(other->info, other->index);
						other = other->link;
					}
				}
			}
			else {
				this->insertAtEnd(other->info, other->index);
				other = other->link;
			}
		}
		cout << "SIZE: " << size << endl;
	}
};

template <class T>
class SM {
private:
	int rows;
	int columns;
	LinkedList<T> * rowList;

public:
	SM<T>(int rows, int columns);
	SM<T>(const SM<T> & other);
	SM<T> &operator=(const SM<T> & other);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM<T> & other);
};

template<class T>
SM<T>::SM(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	this->rowList = new LinkedList<T>[rows];
	cout << "Going to create a sparse matrix of dimensions " << this->rows << "-" << this->columns << endl;
}

template<class T>
SM<T>::SM(const SM<T> & other)
{
	this->rows = other.rows;
	this->columns = other.columns;
	this->rowList = new LinkedList<T>[this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		rowList[i] = other.rowList[i];
	}
}

template<class T>
SM<T> & SM<T>::operator=(const SM<T>& other)
{
	if (this == &other) {
		return *this;
	}

	SM<T> temp(other);
	swap(temp.rows, rows);
	swap(temp.columns, columns);
	swap(temp.rowList, rowList);
	return *this;
}

template<class T>
SM<T>::~SM()
{
	cout << "Deleting sm" << endl;
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
	cout << "Enter sparse matrix dimension in following format: rowIndex columnIndex " << endl;
	int rows, columns;
	cin >> rows;
	cin >> columns;

	SM<int> sm(rows, columns);
	SM<int> sm2(rows, columns);

	sm.readElements();
	sm2.readElements();

	sm.printMatrix();
	sm2.printMatrix();

	SM<int> copySM(sm2);

	sm.addSM(copySM);

	sm.printMatrix();
	system("pause");
	return 0;
}
