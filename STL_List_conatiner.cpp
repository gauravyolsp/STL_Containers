#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

class List;

class node
{
	node *pPrev;
	char iData;
	node *pNext;
	
	friend class List;
	friend class iterator;
	friend void ConcatList(node *pNode, List &lObj2);
	friend ostream& operator<<(ostream &, List &);

public : 
	node();
	~node();
};

class List
{
	node *pDummy;
	void DeleteAllNodes();
	friend void ConcatList(node *pNode, List &lObj2);
	friend ostream& operator<<(ostream &, List &);
	
public : 
	List();
	~List();

	bool IsEmpty();
	void Display();
	int CountNode();
	
	void InsertLast(char);
	void InsertFirst(char);
	void InsertAtPosition(int, int);
	
	int DeleteLast();
	int DeleteFirst();
	int DeleteAtPosition(int);
	
	int SearchAllOccurance(int);
	int SearchLastOccurance(int);
	int SearchFirstOccurance(int);
	
	class iterator
	{
		node * pCurrentNode;
	
	public: 
		iterator();
		~iterator();
		char operator*();		
		iterator& operator--();
		iterator& operator++();
		iterator operator++(int);
		iterator operator--(int);
		void setiter(node* pNode);		
		bool operator!=(iterator obj);
		bool operator==(iterator obj);

		node* getiter()
		{
			node *pNode = pCurrentNode;
			return pNode;
		}
	};

private:
	iterator endobj;
	iterator startobj;

public:
	iterator& end();
	iterator& begin();
	friend iterator find(iterator& iter1, iterator& iter2, char Data);
	
	void push_back(char Data)
	{
		InsertLast(Data);
	}
	
	void push_front(char Data)
	{
		InsertFirst(Data);
	}
	
	void sort()
	{
		//cout << "\nin sort fxn"<<endl;
		node *pTemp1 = pDummy->pNext;
		node *pTemp2 = pTemp1;
		
		while(pTemp1 != pDummy)
		{
			while(pTemp2 != pDummy)
			{
				if(pTemp1->iData > pTemp2->iData)
				{
					pTemp2->pPrev->pNext = pTemp2->pNext;
					pTemp2->pNext->pPrev = pTemp2->pPrev;
					
					pTemp2->pPrev = pTemp1->pPrev;
					pTemp2->pNext = pTemp1;
					pTemp2->pPrev->pNext = pTemp2;
					pTemp1->pPrev = pTemp2;
					
					pTemp1 = pTemp2;
					pTemp2 = pTemp1->pNext;
				}				
				else 
					pTemp2 = pTemp2->pNext;
			}
			pTemp1 = pTemp1->pNext;
			pTemp2 = pTemp1->pNext;
		}
	}
	
	void unique()
	{
		node *pTemp1 = pDummy->pNext;
		node *pTemp2 = pTemp1;
		
		while(pTemp1 != pDummy)
		{
			while(pTemp2 != pDummy)
			{
				if((pTemp1->iData == pTemp2->iData) && (pTemp1 != pTemp2))
				{
					pTemp2->pPrev->pNext = pTemp2->pNext;
					pTemp2->pNext->pPrev = pTemp2->pPrev;
					
					pTemp2->pPrev = pTemp2->pNext = NULL;
					delete pTemp2;
					pTemp2 = pTemp1->pNext;
				}
				
				else 
					pTemp2 = pTemp2->pNext;
			}
			pTemp1 = pTemp1->pNext;
			pTemp2 = pTemp1->pNext;
		}
	}
	
	void splice(iterator iterPos, List& lObj)
	{
		//cout << "in splice 1\n";
		node *pTemp = iterPos.getiter();
		
		pTemp->pPrev->pNext = lObj.pDummy->pNext;
		lObj.pDummy->pNext->pPrev = pTemp->pPrev;
		
		lObj.pDummy->pPrev->pNext = pTemp;
		pTemp->pPrev = lObj.pDummy->pPrev;
		
		lObj.pDummy->pNext = lObj.pDummy;
		lObj.pDummy->pPrev = lObj.pDummy;	
	}
	
	void splice(iterator& iter1, List& lObj, iterator& iter2)
	{
		node *pTemp1 = iter2.getiter();
		node *pTemp2 = iter1.getiter();
						
		pTemp1->pPrev->pNext = pTemp1->pNext;
		pTemp1->pNext->pPrev = pTemp1->pPrev;
		
		pTemp1->pNext = pTemp2;
		pTemp1->pPrev = pTemp2->pPrev;
		pTemp1->pPrev->pNext = pTemp1;
		pTemp2->pPrev = pTemp1;
	}
	
	void operator=(List &refObj1)
	{
		//cout << "in Equal to operator" <<endl;
		node *pTemp1 = refObj1.pDummy->pNext;
		node *pTemp2 = pDummy->pNext;
		
		if(pDummy->pNext != pDummy) //if list1 already have elements
			DeleteAllNodes();						// then delete them first
			
		while(pTemp1 != refObj1.pDummy)
		{
			node *pNewNode = NULL;
			pNewNode = new node;
	
			if(NULL == pNewNode)
			{
				cout <<"Memory Allocation failed !!!";
				return;
			}
	
			pNewNode->iData = pTemp1->iData;
			pNewNode->pNext = pDummy;
			
			pNewNode->pPrev = pDummy->pPrev;
			pNewNode->pPrev->pNext = pNewNode;
			pDummy->pPrev = pNewNode;
			
			pTemp1 = pTemp1->pNext;
		}
	}
	void merge(List &lObj)
	{
		//cout << "\nin merge function"<<endl;
		ConcatList(pDummy, lObj);
		sort();
	}
};

////////////////////////////////////////////////////////////////////////////////////
//	CLIENT FUNCTION DECLARATION
////////////////////////////////////////////////////////////////////////////////////

void printLists(List& l1, List &l2)
{
	cout << "list 1: ";
	for(List::iterator iter = l1.begin(); iter != l1.end(); ++iter)
		cout << *iter << " ";
	
	cout << endl << "list 2: ";
	for(List::iterator iter = l2.begin(); iter != l2.end(); ++iter)
		cout << *iter << " ";
	cout << endl << endl;
}

List::iterator find(List::iterator& iterFirst, List::iterator& iterLast, char Data)
{
	//cout << "\nin find function\n";
	
	while(iterFirst != iterLast)
	{
		if(*iterFirst == Data)
			return iterFirst;
		iterFirst++;
	}
	return iterLast;
}

////////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION OR CLIENT SIDE
////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// create two empty lists
	
	List list1, list2;
	
	// fill both lists with elements
	
	for(int i = 0; i < 6; i++)
	{
		list1.push_back(i + 65);
		list2.push_front(i + 65);
	}
	
	printLists(list1, list2);
	
	// insert all elements of list1 before the first element with value E of list 2
	// -find() returns an interator to the first element with value E

	//cout << "\nsplice 1 call..\n" <<endl;
	list2.splice(find(list2.begin(), list2.end(), 'E'), list1); //source list
									// destination position

	printLists(list1, list2);
	
	// move first element of list2 to the end
	
	//cout << "\nsplice 2 call..\n" <<endl;
	list2.splice(list2.end(), list2, list2.begin());// source position
	//destinastion position	// source list
	
	printLists(list1, list2);
	
	// sort second list, assign to list1 and remove duplicates
	//cout << "\ncalling sort" <<endl;
	list2.sort();
	//list1.sort();
	printLists(list1, list2);
	//cout << "\ncalling equal to" <<endl;
	list1 = list2;
	printLists(list1, list2);
	//cout << "\ncalling unique" <<endl;
	list2.unique();
	//list1.unique();
	
	printLists(list1, list2);
	
	// merge both sorted lists into the first list
	
	list1.merge(list2);
	
	printLists(list1, list2);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//	CLIENT FUNCTION : DISPLAY Iterator
//////////////////////////////////////////////////////////////////////////////////
	
void DisplayIterator(List &list)
{
	cout << "\nIterator display start : linked list is : \n";
	for(List :: iterator iter = list.begin(); iter != list.end(); ++iter)
		cout << "<-|" << *iter << "|->";
	cout << endl;
}

/////////////////////////////////////////////////////
//	NODE CLASS CONSTRUCTOR AND DESTRUCTOR
/////////////////////////////////////////////////////

node :: node()
{
	iData = 0;
	pPrev = pNext = NULL;
}

node :: ~node()
{
	if(pNext != NULL)
	{
		delete pNext;
		delete pPrev;
		pNext = pPrev = NULL;	
	}
}

/////////////////////////////////////////////////////
// LIST CLASS CONSTRUCTOR AND DESTRUCTOR
/////////////////////////////////////////////////////

List :: List()
{
	pDummy = new node;
	
	if(NULL == pDummy)
	{
		cout << "Memory Allocation failed !!!"; 
		return;
	}
	
	// given doubly feel.
	pDummy->iData = 0;			// this data will never get accessed.
	pDummy->pPrev = pDummy;
	pDummy->pNext = pDummy;
}

List :: ~List()
{
	if(pDummy->pNext != pDummy)
		DeleteAllNodes();

	pDummy->pPrev = NULL;
	pDummy->pNext = NULL;
	pDummy = NULL;
	delete pDummy;	
}

/////////////////////////////////////////////////////
//	ITERATOR CLASS CONSTRUCTOR AND DESTRUCTOR
/////////////////////////////////////////////////////

List :: iterator :: iterator()
{
	pCurrentNode = NULL;
}

List :: iterator :: ~iterator()
{
	pCurrentNode = NULL;
}

/////////////////////////////////////////////////////
// BEGIN AND END FUNCTION
/////////////////////////////////////////////////////

List :: iterator& List :: begin()
{
	startobj.setiter(pDummy->pNext);
	return startobj;
}

List :: iterator& List :: end()
{
	endobj.setiter(pDummy);
	return endobj;
}

/////////////////////////////////////////////
//	SET ITERATOR FUNCTION
/////////////////////////////////////////////

void List :: iterator :: setiter(node * pNode)
{
	pCurrentNode = pNode;
}

/////////////////////////////////////////////////////
// INSERTION FUNCTIONS
/////////////////////////////////////////////////////

void List :: InsertFirst(char iData)
{
	node *pNewNode = NULL;
	pNewNode = new node;
	 
	if(NULL == pNewNode)
	{
		
		cout << "Memory Allocation failed !!!";
		return;
	}
	 
	pNewNode->iData = iData;
	pNewNode->pPrev = pDummy;
	
	pNewNode->pNext = pDummy->pNext;
	pNewNode->pNext->pPrev = pNewNode;
	pDummy->pNext = pNewNode;
}

void List :: InsertLast(char iData)
{
	node *pNewNode = NULL;
	pNewNode = new node;
	
	if(NULL == pNewNode)
	{
		cout <<"Memory Allocation failed !!!";
		return;
	}
	
	pNewNode->iData = iData;
	pNewNode->pNext = pDummy;
	
	pNewNode->pPrev = pDummy->pPrev;
	pNewNode->pPrev->pNext = pNewNode;
	pDummy->pPrev = pNewNode;
}

void List :: InsertAtPosition(int iData, int iPos)
{
	int iCount;
	node *pTemp = NULL;
	node *pNewNode = NULL;
	
	pNewNode = new node;
	
	if(NULL == pNewNode)
	{
		cout << "Memory Allocation failed !!!";
		return;
	}
	
	if(1 == iPos)
	{
		InsertFirst(iData);
		return;
	}
	
	else if(iPos == (CountNode() + 1))
	{
		InsertLast(iData);
		return;
	}
	
	pTemp = pDummy->pNext;
	iCount = 1;
	
	while(iCount < iPos - 1)
	{
		iCount++;
		pTemp = pTemp->pNext;
	}
	
	pNewNode->iData = iData;
	
	pNewNode->pNext = pTemp->pNext;
	pTemp->pNext->pPrev = pNewNode;
	pTemp->pNext = pNewNode;
	pNewNode->pPrev = pTemp;
}

/////////////////////////////////////////////////////
//	DELETION FUNCTIONS
/////////////////////////////////////////////////////

int List :: DeleteFirst()
{
	int iDelData;
	
	if(pDummy == pDummy->pNext)
		return -1;
	
	iDelData = pDummy->pNext->iData;
	
	pDummy->pNext->pPrev = NULL;
	pDummy->pNext = pDummy->pNext->pNext;
	pDummy->pNext->pPrev->pNext = NULL;
	delete pDummy->pNext->pPrev;
	pDummy->pNext->pPrev = pDummy;
	
	return iDelData;
}

int List :: DeleteLast()
{
	int iDelData;
	
	if(pDummy->pPrev == pDummy)
		return -1;
	
	iDelData = pDummy->pPrev->iData;
	
	pDummy->pPrev->pNext = NULL;
	pDummy->pPrev = pDummy->pPrev->pPrev;
	pDummy->pPrev->pNext->pPrev = NULL;
	delete pDummy->pPrev->pNext;
	pDummy->pPrev->pNext = pDummy;
	
	return iDelData;
}

int List :: DeleteAtPosition(int iPos)
{
	int iValue;
	node *pTemp = NULL;
	
	if(pDummy->pNext == pDummy)
		return -1;
	
	if(1 == iPos)
		return DeleteFirst();
	
	else if(iPos == CountNode())
		return DeleteLast();
		 
	pTemp = pDummy->pNext;
	iValue = 1;
	
	while(iValue < iPos)
	{
		iValue++;
		pTemp = pTemp->pNext;
	}
	
	pTemp->pPrev->pNext = pTemp->pNext;
	pTemp->pNext->pPrev = pTemp->pPrev;
	pTemp->pPrev = NULL;
	pTemp->pNext = NULL;

	iValue = pTemp->iData;
	delete pTemp;
	
	return iValue;   	
}

void List :: DeleteAllNodes()
{		
	while(pDummy != pDummy->pNext)
	{
		pDummy->pNext->pPrev = NULL;
		pDummy->pNext = pDummy->pNext->pNext;
		pDummy->pNext->pPrev->pNext = NULL;
		delete pDummy->pNext->pPrev;
		pDummy->pNext->pPrev = pDummy;
	}
	
	cout << "\nAll Nodes Deleted Successfully\n";	
	
	//if(pDummy->pPrev == pDummy->pNext)
		//cout << "Dummy node is present...\n";
}

/////////////////////////////////////////////////////
//	COUNT NODE FUNCTION
/////////////////////////////////////////////////////

int List :: CountNode()
{
	int iCount = 0;
	node *pTemp = NULL;
	
	pTemp = pDummy->pNext;
	
	if(pTemp == pDummy)
		return iCount;
	
	while(pTemp != pDummy)
	{
			++iCount;
			pTemp = pTemp->pNext;
	}
	
	return iCount;
}

/////////////////////////////////////////////////////
//	DISPLAY FUNCTION
/////////////////////////////////////////////////////

void List :: Display()
{
	node *pTemp = pDummy->pNext;
	
	if(NULL == pTemp)
	{
		cout << "\nLinked List is Empty!!!\n";
		return;
	}

	cout << "\nLinked List is:\n";
	do
	{
		cout << "<-|" << pTemp->iData << "|->";
		pTemp = pTemp->pNext;
	}while(pTemp != pDummy);
	cout << "\n";
}

/////////////////////////////////////////////////////
//	IS EMPTY FUNCTION
/////////////////////////////////////////////////////

bool List :: IsEmpty()	// This function if for checking if linked List is empty or not.
{
	if(pDummy == pDummy->pNext)
		return true;
	return false;
}

/////////////////////////////////////////////////////
//	SERACHING FUNCTIONS
/////////////////////////////////////////////////////

int List :: SearchFirstOccurance(int iKey)
{
	int iCount = 1;
	node *pTemp = pDummy->pNext;

	if(pDummy == pDummy->pNext)
		return -1;

	do
	{
		if(pTemp->iData == iKey)
			break;
		iCount++;		
		pTemp = pTemp->pNext;
	}while(pTemp != pDummy);

	if(pTemp == pDummy && iCount != 1)
		iCount = 0;

	return iCount;
}

int List :: SearchLastOccurance(int iKey)
{
	int iLast = 0;
	int iCount = 0;
	node *pTemp = pDummy->pNext;
	
	if(pDummy == pDummy->pNext)
		return -1;
	
	do
	{
		iCount++;	
		if(pTemp->iData == iKey)
			iLast = iCount;

		pTemp = pTemp->pNext;
	}while(pTemp != pDummy);

	return iLast;
}

int List :: SearchAllOccurance(int iKey)
{
	int iCount = 0;
	node *pTemp = pDummy->pNext;
	
	if(NULL == pDummy->pNext)
		return -1;

	do
	{
		if(pTemp->iData == iKey)
			iCount++;

		pTemp = pTemp->pNext;
	}while(pTemp != pDummy);
	
	return iCount;
}

/////////////////////////////////////////////
//	OVERLOADED OPERATOR'S
/////////////////////////////////////////////

ostream& operator<<(ostream &out, List &refObj)
{
	node *pTemp = NULL;
	
	if(refObj.pDummy == refObj.pDummy->pNext)
	{
		out << "\nLinked List is Empty!!!\n";
		return out;
	}
	pTemp = refObj.pDummy->pNext;

	out << "\nLinked List is:\n";
	do
	{
		out << "<-|" << pTemp->iData << "|->";
		pTemp = pTemp->pNext;
	}while(pTemp != refObj.pDummy);
	out << "\n";
	
	return out;
}

List :: iterator& List :: iterator :: operator++()
{
	pCurrentNode = pCurrentNode->pNext;
	return *this; 
}
		
List :: iterator List :: iterator :: operator++(int)
{
	iterator temp;
	temp.pCurrentNode = pCurrentNode;
	pCurrentNode = pCurrentNode->pNext;
	return temp;
}
		
List :: iterator& List :: iterator :: operator--()
{
	pCurrentNode = pCurrentNode->pPrev;
	return *this;
}
		
List :: iterator List :: iterator ::  operator--(int)
{
	iterator temp;
	temp.pCurrentNode = pCurrentNode;
	pCurrentNode = pCurrentNode->pPrev;
	return temp;
}
			
char List :: iterator :: operator*()
{
	return pCurrentNode->iData;
}
		
bool List :: iterator :: operator!=(iterator obj)
{
	return (pCurrentNode != obj.pCurrentNode);
}
		
bool List :: iterator :: operator==(iterator obj)
{
	return (pCurrentNode == obj.pCurrentNode);
}

void ConcatList(node *pNode, List &lObj2)
{	
	if(lObj2.pDummy == lObj2.pDummy->pNext) // if second list is empty
		return;
	
	if(pNode == pNode->pNext)	// if first list is empty but second list present
	{
		pNode->pNext = lObj2.pDummy->pNext;
		pNode->pPrev = lObj2.pDummy->pPrev;
		lObj2.pDummy->pNext = lObj2.pDummy;
		lObj2.pDummy->pPrev = lObj2.pDummy;
		return;
	}

	pNode->pPrev->pNext = lObj2.pDummy->pNext;
	lObj2.pDummy->pNext->pPrev = pNode->pPrev;
	
	pNode->pPrev = lObj2.pDummy->pPrev;
	lObj2.pDummy->pPrev->pNext = pNode;
	
	lObj2.pDummy->pNext = lObj2.pDummy;
	lObj2.pDummy->pPrev = lObj2.pDummy;
}