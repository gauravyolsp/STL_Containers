#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

template <typename T> T MyMain(T);
template <typename T> class List;

template <typename T>
class node
{
	node *pPrev;
	T iData;
	node *pNext;
	
	friend class List <T>;
	template <typename T1> friend ostream& operator<<(ostream &, List <T1> &);

public : 
	node(); 
	~node();
};

template <typename T> class List
{
	node <T> *pDummy;
	void DeleteAllNodes();
	template <typename T1> friend ostream& operator<<(ostream &, List <T1> &);
	
public : 
	List();
	~List();

	bool IsEmpty();
	void Display();
	int CountNode();
	
	void InsertLast(T);
	void InsertFirst(T);
	void InsertAtPosition(T, int);
	
	T DeleteLast();
	T DeleteFirst();
	T DeleteAtPosition(int);
	
	int SearchAllOccurance(T);
	int SearchLastOccurance(T);
	int SearchFirstOccurance(T);
	
	template <typename T1>
	class iterator
	{
		node <T1> * pCurrentNode;
		
		// used in future
		node <T1> *getiter(node <T1> *n)
		{
			return n;
		}
		
	public: 
		iterator();
		~iterator();
		T1 operator*();		
		iterator& operator--();
		iterator& operator++();
		iterator operator++(int);
		iterator operator--(int);
		void setiter(node <T1> *pNode);		
		bool operator!=(iterator obj);
		bool operator==(iterator obj);
	};

private:
	iterator <T> endobj;
	iterator <T> startobj;

public:
	iterator <T> end();
	iterator <T> begin();
};

////////////////////////////////////////////////////////////////////////////////////
//	CLIENT FUNCTION DECLARATION
////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void DisplayIterator(List <T> &list);

////////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION OR CLIENT SIDE
////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int iChoice;
	
	while(1)
	{
		cout << "\n\tWelCome !!!\n\n";
		cout << "1. Integer Linked List (int)\n2. Character Linked list (char)\n3. Single Precision Floating Point (float)\n4. Double Precision Floating Point (double)\n5. Exit\n";
		cout << "\nWhich type of Linked List you want to make : ";
		cin >> iChoice;
		
		switch(iChoice)
		{
			case 1 : MyMain(1);
					break;
						
			case 2 : MyMain('A');
					 break;
			
			case 3 : MyMain(3.0f);
					 break;
					 
			case 4 : MyMain(4.0);
					 break;
					 
			case 5 : cout << "\n\tBye... Leaving Program !!!\n\n" ;
					exit(0);
			
			default : cout << "\n\nEnter valid choice !!!	\n" ;
		}
	}
}

template <typename T>
T MyMain()
{
	List <T> lObj;
	int iPos;
	T iData;
	//int iTemp;
	int iChoice;

	while(1)
	{
		cout << "\n1.Insert\n2.Delete\n3.Search\n4.Count\n5.Exit\n";
		cout << "Enter your choice:\t";
		cin >> iChoice;
		
		if(iChoice <= 0 || iChoice > 8)
		{
			cout << "Enter valid choice.\n";
			continue;
		}

		switch(iChoice)
		{
			case 1:	while(1)
				{
					cout << "\n1.InsertFirst\n2.InsertLast\n3.InsertAtPosition\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;

					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}

					if(3 == iChoice)
					{
						cout << "\nEnter the position:\t";
						cin >> iPos;
						
						if(iPos <= 0 || iPos > (lObj.CountNode() + 1))
						{
							cout << "Enter valid position.\n";
							continue;
						}
					}

					cout << "Enter data to be inserted:\t";
					cin >> iData;

					switch(iChoice)
					{
						case 1:	lObj.InsertFirst(iData);
							break;
						
						case 2: lObj.InsertLast(iData);
							break;
	
						case 3: lObj.InsertAtPosition(iData, iPos);
					}			

					//cout << "\nDisplay using object : \n";
					//lObj.Display();
					DisplayIterator(lObj);
					
					//cout << "\nDisplay using operator overloading\n";
					//cout << lObj << endl;;		
				}break;
				
			case 2: if(lObj.IsEmpty())
				{
					cout << "Linked List Empty, Deletion Not Possible.\n";
					break;
				}
		
				while(1)
				{
					cout << "\n1.DeleteFirst\n2.DeleteLast\n3.DeleteAtPosition\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;

					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}

					switch(iChoice)
					{
						case 1: iData = lObj.DeleteFirst();
							break;

						case 2: iData = lObj.DeleteLast();
							break;

						case 3: if(lObj.IsEmpty())
							{
								cout << "Linked List is Empty\n";
								continue;
							}
								
							cout << "\nEnter the position:\t";
							cin >> iPos;
						
							if(iPos <= 0 || iPos > lObj.CountNode())
							{
								cout << "Enter valid position.\n";
								continue;
							}
							iData = lObj.DeleteAtPosition(iPos);
					}

					if(-1 != iData)
						cout << "\nDeleted data is " << iData << endl;

					//cout << "\nDisplay using object : \n";
					//lObj.Display();
					
					//cout << "\nDisplay using operator overloading\n";
					cout << lObj << endl;
				}break;

			case 3:	if(lObj.IsEmpty())
				{
					cout << "Linked List Empty, Searching Not Possible.\n";
					break;
				}

				while(1)
				{
					cout << "\n1.SearchFirstOccurance\n2.SearchLastOccurance\n3.SearchAllOccurance\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;
				
					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}
					DisplayIterator(lObj);

					cout << "Enter data to search:\t";
					cin >> iData;

					switch(iChoice)
					{
						case 1: iPos = lObj.SearchFirstOccurance(iData);
							if(-1 == iPos)
								cout << "Linked List is Empty\n";
							else if(0 != iPos)	
								cout << iData << " is found at "<< iPos << " location " << endl;

							else
								cout << "Data not Found\n";

							break;

						case 2: iPos = lObj.SearchLastOccurance(iData);
							if(-1 == iPos)
								cout << "Linked List is Empty\n";
							else if(0 != iPos)	
								cout << iData << " is found at "<< iPos << " location" << endl;
							else
								cout << "Data not Found\n";
							break;

						case 3: iPos = lObj.SearchAllOccurance(iData);
							cout << iData << " is found " << iPos << " time.\n";
					}
				}break;

			case 4: cout << "Total nodes present : " << lObj.CountNode() << endl;
				break;

			case 5:
			
				cout <<"Bye...\n";
				//cout << "\n\nDisplay using object\n\n";
				//lObj.Display();
				
				//cout << "\n\nDisplay using operator overloading\n\n";
				cout << lObj << endl;
				
				return 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
//	CLIENT FUNCTION : DISPLAY Iterator
//////////////////////////////////////////////////////////////////////////////////

template <typename T>
void DisplayIterator(List <T> &list)
{
	cout << "\nIterator display start : linked list is : \n";
	for(typename List <T> :: iterator iter = list.begin(); iter != list.end(); ++iter)
		cout << "<-|" << *iter << "|->";
	cout << endl;
}

/////////////////////////////////////////////////////
//	NODE CLASS CONSTRUCTOR AND DESTRUCTOR
/////////////////////////////////////////////////////
template <typename T>
node <T> :: node()
{
	iData = 0;
	pPrev = pNext = NULL;
}

template <typename T>
node <T> :: ~node()
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

template <typename T>
List <T> :: List()
{
	pDummy = new node <T>;
	
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

template <typename T>
List <T> :: ~List()
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

template <typename T>
typename List <T>:: iterator:: iterator()
{
	pCurrentNode = NULL;
}

template <typename T>
typename List <T> :: iterator:: ~iterator()
{
	pCurrentNode = NULL;
}

/////////////////////////////////////////////////////
// INSERTION FUNCTIONS
/////////////////////////////////////////////////////

template <typename T>
void List <T> :: InsertFirst(T iData)
{
	node <T> *pNewNode = NULL;
	pNewNode = new node <T>;
	 
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

template <typename T>
void List <T> :: InsertLast(T iData)
{
	node <T> *pNewNode = NULL;
	pNewNode = new node <T>;
	
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

template <typename T>
void List <T> :: InsertAtPosition(T iData, int iPos)
{
	int iCount;
	node <T> *pTemp = NULL;
	node <T> *pNewNode = NULL;
	
	pNewNode = new node <T>;
	
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

template <typename T>
T List <T> :: DeleteFirst()
{
	T iDelData;
	
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

template <typename T>
T List <T> :: DeleteLast()
{
	T iDelData;
	
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

template <typename T>
T List <T> :: DeleteAtPosition(int iPos)
{
	T iValue;
	node <T> *pTemp = NULL;
	
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

template <typename T>
void List <T> :: DeleteAllNodes()
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

template <typename T>
int List <T> :: CountNode()
{
	int iCount = 0;
	node <T> *pTemp = NULL;
	
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

template <typename T>
void List <T> :: Display()
{
	node <T> *pTemp = pDummy->pNext;
	
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

template <typename T>
bool List <T> :: IsEmpty()	// This function if for checking if linked List is empty or not.
{
	if(pDummy == pDummy->pNext)
		return true;
	return false;
}

/////////////////////////////////////////////////////
//	SERACHING FUNCTIONS
/////////////////////////////////////////////////////

template <typename T>
int List <T> :: SearchFirstOccurance(T iKey)
{
	int iCount = 1;
	node <T> *pTemp = pDummy->pNext;

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

template <typename T>
int List <T> :: SearchLastOccurance(T iKey)
{
	int iLast = 0;
	int iCount = 0;
	node <T> *pTemp = pDummy->pNext;
	
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

template <typename T>
int List <T> :: SearchAllOccurance(T iKey)
{
	int iCount = 0;
	node <T> *pTemp = pDummy->pNext;
	
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

/////////////////////////////////////////////////////
// BEGIN AND END FUNCTION
/////////////////////////////////////////////////////

template <typename T>
typename List <T>:: iterator List <T> :: begin()
{
	startobj.setiter(pDummy->pNext);
	return startobj;
}

template <typename T>
typename List <T>:: iterator <T> List :: end()
{
	
	endobj.setiter(pDummy);
	return endobj;
}

/////////////////////////////////////////////
//	SET ITERATOR FUNCTION
/////////////////////////////////////////////

template <typename T>
void typename List <T>:: iterator :: setiter(node <T> *pNode)
{
	pCurrentNode = pNode;
}

/////////////////////////////////////////////
//	OVERLOADED OPERATOR'S
/////////////////////////////////////////////

template <typename T>
ostream& operator<<(ostream &out, List <T> &refObj)
{
	node <T> *pTemp = NULL;
	
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

template <typename T>
typename List <T> :: iterator& <T> List :: iterator :: operator++()
{
	pCurrentNode = pCurrentNode->pNext;
	return *this; 
}
		
template <typename T>
typename List <T> :: iterator <T> List :: iterator :: operator++(int)
{
	iterator temp;
	temp.pCurrentNode = pCurrentNode;
	pCurrentNode = pCurrentNode->pNext;
	return temp;
}

template <typename T>		
typename List <T>:: iterator& <T> List :: iterator :: operator--()
{
	pCurrentNode = pCurrentNode->pPrev;
	return *this;
}
		
template <typename T>
typename List <T> :: iterator <T> List :: iterator ::  operator--(int)
{
	iterator temp;
	temp.pCurrentNode = pCurrentNode;
	pCurrentNode = pCurrentNode->pPrev;
	return temp;
}

template <typename T>
int typename List <T> :: iterator :: operator*()
{
	return pCurrentNode->iData;
}

template <typename T>
bool typename List <T> :: iterator :: operator!=(typename List <T>:: iterator obj)
{
	return (pCurrentNode != obj.pCurrentNode);
}
		
template <typename T>
{
bool typename List <T> :: iterator :: operator==(typename List <T> :: iterator obj)
	return (pCurrentNode == obj.pCurrentNode);
}