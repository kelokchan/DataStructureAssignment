#include<iostream>
#include<string>
#include <iomanip>

using namespace std;

class NodeType {
public:
	int info;
	int index;
	NodeType* link;
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

	//copy constructor
	LinkedList(const LinkedList & other) {
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
		NodeType * current = other.head;
		while (current != NULL) {
			this->setValue(current->info, current->index);
			current = current->link;
		}
	}

	//LinkedList &operator =(const LinkedList & other) {
	//	NodeType * current = other.head;
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
		NodeType * current = head;
		while (current != NULL) {
			current = current->link;
			delete head;
			head = current;
		}
	}

	void setValue(int value, int inputIndex) {
		NodeType * newNode = new NodeType;
		newNode->info = value;
		newNode->index = inputIndex;

		if (size == 0 || head->index > inputIndex) {
			insertAtBeginning(value, inputIndex);					//list is empty || head index > new index, put at beginning
		}
		else if (tail->index < inputIndex) {
			insertAtEnd(value, inputIndex);
		}
		else {
			NodeType * current = head;
			while (current != NULL) {
				if (current->index == inputIndex) {
					current->info = value;
					break;
				}
				else if (current->index < inputIndex) {					//first is smaller than input
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
			}
		}
	}

	NodeType* insertValue(int value, int inputIndex, NodeType * &prev) {			//insert newNode after prev
		NodeType * newNode = new NodeType;
		newNode->info = value;
		newNode->index = inputIndex;
		newNode->link = prev->link;
		prev->link = newNode;
		size++;
		return newNode;
	}

	int getValue(int column) {
		NodeType* current = head;
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
		NodeType * current = head;
		cout << "[";
		for (int i = 0; i < column; i++)
		{		//list not empty
			if(current != NULL)
				if (current->index == i) {	//list index == iteration
					cout << right << setw(7) << current->info;	//prints out the info with width of 7 to fix spacing
					current = current->link;		//traverse to next
				}
				else {
					cout << right << setw(7) << "0";
				}
			else
				cout << right << setw(7) << "0";
		}
		cout << setw(7) << "]";
		cout << endl;
	}

	void print() {
		NodeType * current = head;
		while (current != NULL) {
			cout << " " << current->info << " ";
			current = current->link;
		}
	}

	void insertAtBeginning(int value, int index) {
		NodeType * newNode = new NodeType;
		newNode->info = value;
		newNode->index = index;
		newNode->link = head;
		head = newNode;
		if (tail == NULL)
			tail = newNode;
		size++;
	}

	void insertAtEnd(int value, int index) {
		NodeType * newNode = new NodeType;
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

	void sumNodes(LinkedList &list2) {
		NodeType * current = head;
		NodeType * other = list2.head;
		NodeType * prev = NULL;
		while (other != NULL) {
			if (head == NULL || other->index > tail->index) {					//list is 0 or tail index < other index
				this->insertAtEnd(other->info, other->index);
			}
			else if (head->index > other->index) {							//put other in front of head
				this->insertAtBeginning(other->info, other->index);
			}
			else {															//other index > current index
				while (current->index < other->index) {							//loop current until nearest to other
					prev = current;
					current = current->link;
				}
				if (current->index == other->index) {							//same index, update current value
					current->info += other->info;
					prev = current;
					current = current->link;
				}
				else {
					prev = this->insertValue(other->info, other->index, prev);				//insert other after current
				}
			}
			other = other->link;
		}
	}
};

class SM {
private:
	int rows;
	int columns;
	LinkedList * rowList;

public:
	SM(int rows, int columns);
	SM(const SM & other);
	SM &operator=(const SM & other);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM & other);
};


SM::SM(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	this->rowList = new LinkedList[rows];
	cout << "Going to create a sparse matrix of dimensions " << this->rows << "-" << this->columns << endl;
}


SM::SM(const SM & other)
{
	this->rows = other.rows;
	this->columns = other.columns;
	this->rowList = new LinkedList[this->rows];
	for (int i = 0; i < this->rows; i++) {
		rowList[i] = other.rowList[i];
	}
}


SM & SM::operator=(const SM& other)
{
	if (this == &other) {
		return *this;
	}

	SM temp(other);
	swap(temp.rows, rows);
	swap(temp.columns, columns);
	swap(temp.rowList, rowList);
	return *this;
}


SM::~SM()
{
	cout << "Deleting sm" << endl;
	delete[] rowList;
}


void SM::readElements()
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


void SM::printMatrix()
{
	for (int i = 0; i < this->rows; i++)
	{
		rowList[i].printNodes(columns);
	}
	cout << endl;
}


void SM::addSM(SM & other)
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
	cout << "HI!" << endl;
	rowList[0].print();
	cout << endl << "BYE!" << endl;
}

int main()
{
	cout << "Enter sparse matrix dimension in following format: rowIndex columnIndex " << endl;
	int rows, columns;
	cin >> rows;
	cin >> columns;

	SM sm(rows, columns);
	SM sm2(rows, columns);

	sm.readElements();
	sm.printMatrix();

	sm2.readElements();
	sm2.printMatrix();

	sm.addSM(sm2);
	cout << "Result: " << endl;
	sm.printMatrix();
	system("pause");
	return 0;
}
