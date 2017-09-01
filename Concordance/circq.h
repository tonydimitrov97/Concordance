/****************************************************************************
 Programmer: Tim Wrenn/Antonio Dimitrov			

 Basic Operations:

	constructor: constructs an empty Queue
	empty	   : checks if the Queue is empty
	enqueue    : Inserts an element into the Queue
	front	   : Returns the top queue element
	dequeue	   : deletes the top element from the Queue
	display    : Displays the entire Queue

	Note: Program does not terminate if error conditions are met.
****************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef CIRCULARQ_H
#define CIRCULARQ_H

template <typename QueElement>
//typedef int QueElement;

class CircularQ{

private:
	class Node{
	public:
		QueElement data;
		Node * next;

		Node(QueElement d){
			data = d;
			next = NULL;
		}// end Node Constructor
	};
public:
   
	typedef Node * NodePointer;

	CircularQ(){ last = NULL; }				// Create an empty Q
/*****************************************************************************
Default Constructor creates an empty Queue

Pre: None

Post: An empty Queue is created and the last pointer is initialized to NULL
******************************************************************************/
	
	void display(ostream &out) const;		// Helper method
/*****************************************************************************
Display the entire Queue

Pre: Ostream out is open.

Post: Outputs the contents of the Queue in FIFO order
******************************************************************************/

	CircularQ(const CircularQ &origQ);		// Copy constructor
/*****************************************************************************
Copy Constructor: creates a copy of the original Queue

Pre: Original is the Queue to be copied and is received as a const reference
     parameter

Post: A copy of the original has been constructed
******************************************************************************/

	~CircularQ();							// Destructor
/*****************************************************************************
Destructor: deletes the Queue

Pre: None
     
Post: The queue is destroyed and empty queue is created
******************************************************************************/
	
	CircularQ &operator=(const CircularQ &rhs);
/*****************************************************************************
Overloaded Assignment Operator: Mimics the assignment operator

Pre: Original is the Queue to be copied and is received as a const reference
     parameter

Post: The current Queue is replaced by a copy of the Queue of rhs and 
	  a reference to it is returned.
******************************************************************************/
	
	void enqueue(QueElement item);			// put an item into the Q
/*****************************************************************************
enqueue: Inserts an item into the front of the Queue.

Pre: Queue must exist and the parameter item must be initialized.
  
Post: The item is inserted into the Queue.
	  
******************************************************************************/
	
	QueElement front();
/*****************************************************************************
front: Returns the first item in the queue.

Pre: Queue must exist
  
Post: Either an error message will be displayed if the Queue is empty or
	  the front of the Queue is returned.	  
******************************************************************************/

QueElement end();
/*****************************************************************************
front: Returns the last item in the queue.

Pre: Queue must exist

Post: Either an error message will be displayed if the Queue is empty or
the end of the Queue is returned.
******************************************************************************/
	
	void dequeue();
/*****************************************************************************
dequeue: Deletes the item located in the front of the Queue.

Pre: Checks to see if the Queue is empty
  
Post: Displays an error message if the Queue is empty otherwise the element
	  at the front of the Queue is deleted.	  
******************************************************************************/

bool empty(){return last == NULL;}
/*****************************************************************************
empty: Checks to see if the Queue is empty

Pre: A queue must be created
  
Post: Returns either true if the Queue is empty, false otherwise.
******************************************************************************/
private:

	NodePointer last;

};
template <typename QueElement>
ostream &operator<<(ostream& out, const CircularQ<QueElement> &q);
/*****************************************************************************
operator<<: Overloaded operator which allows you to display the contents
			of the entire Queue

Pre: ostream must be opened and the const parameter is passed by reference
  
Post: Calls the method display that displays the entire Queue.
	  
******************************************************************************/
	
#endif
template <typename QueElement>
void CircularQ<QueElement>::display(ostream &out) const {

	NodePointer first;			// Need a pointer

	if (last == NULL)
		cout << "Queue is empty \n\n";
	else {

		first = last->next;					// no, intialize to first item in the list
		do {
			out << first->data << "  ";		// output the item
			first = first->next;			// move along
		} while (first != last->next);		// have we traversed the entire list?
	}// end else
}//display method

template <typename QueElement>
CircularQ<QueElement>::~CircularQ() {

	NodePointer first;

	if (last != NULL) {					// empty list?
		first = last->next;				// no, intialize to first item in the list
		while (first != last) {
			last->next = first->next; // avoid memory leak
			delete first;				// get rid of first node	
			first = last->next;			// adjust to the first node.
		}
		delete first;					// make sure the last node is gone
		last = NULL;					// set to an empty list
	}// end if
	//cout << "Exiting Destructor " << endl;

}// end destructor

template <typename QueElement>
void CircularQ<QueElement>::enqueue(QueElement item) {

	NodePointer newNode = new Node(item);		// Need a node for the Q

	if (last == NULL) {				    // empty Q
		last = newNode;					// start constructing the Q
		last->next = last;		        // pointer to itself since one item
	}
	else {
		newNode->next = last->next;		// Chain it 
		last->next = newNode;
		last = newNode;
	}
}// end enqueue

template <typename QueElement>
CircularQ<QueElement>::CircularQ(const CircularQ<QueElement> &origQ) { // Copy constructor

	if (origQ.last != NULL) {					// empty? 

		NodePointer origLast = origQ.last,		// No. Create pointers to traverse Q's
			origFirst = origLast->next,
			newNode;

		last = new Node(origFirst->data);	// Initialize the new list
		last->next = last;					// set up the correct pointers

		origFirst = origFirst->next;		// Move to the next item in the list to copy

		while (origFirst != origLast->next) {	// Start traversing

			newNode = new Node(origFirst->data);	// create a new new node
			newNode->next = last->next;			// Start chaining it together
			last->next = newNode;
			last = newNode;
			origFirst = origFirst->next;			// go to the next one
		}// end while

	}// end if
}//end copy constructor

template <typename QueElement>
CircularQ<QueElement> &CircularQ<QueElement>::operator=(const CircularQ<QueElement> &rhs) {

	if (this != &rhs) {				// Self-referential Assignment?

		this->~CircularQ();			// No. Destoy LHS 

		if (rhs.last != NULL) {		// rhs empty? 

			NodePointer rhsLast = rhs.last,		// Create pointers for traversal
				rhsFirst = rhsLast->next,
				newNode;

			last = new Node(rhsFirst->data);	// Initialize the new LHS
			last->next = last;

			rhsFirst = rhsFirst->next;			// go to the next RHS item

			while (rhsFirst != rhsLast->next) {	// Start traversing

				newNode = new Node(rhsFirst->data);	// Start the process of duplication
				newNode->next = last->next;
				last->next = newNode;
				last = newNode;
				rhsFirst = rhsFirst->next;			// Go the next item in the RHS
			}// end while

		}// end if
	}

	return *this;									// Allow assignment chaining

}// end assignment operator

template <typename QueElement>
QueElement CircularQ<QueElement>::front() {

	QueElement garbage = NULL;

	if (empty()) {
		cout << "Queue is empty returning garbage" << endl;
		return garbage;
	}
	NodePointer first = last->next;
	return (first->data);

}// return front of Q

template <typename QueElement>
QueElement CircularQ<QueElement>::end() {

	QueElement garbage = NULL;

	if (empty()) {
		//cout << "Queue is empty returning garbage" << endl;
		return garbage;
	}
	return (last->data);

}// return end of Q

template <typename QueElement>
void CircularQ<QueElement>::dequeue() {

	if (empty())
		cout << "Error ----- Cannot delete an item from an empty Queue"
		<< endl << endl;
	else {
		NodePointer first = last->next;
		if (first == last)
			last = NULL;			// Queue will be empty
		else
			last->next = first->next;

		delete first;				// eliminate the node
	}
}// end dequeue

template <typename QueElement>
ostream &operator<<(ostream& out, const CircularQ<QueElement> &q) {
	q.display(out);
	return out;
}// end operator<<