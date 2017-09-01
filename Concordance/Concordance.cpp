/*Program that reads in a file of words, inserts into a BST of
words followed by a Queue of line numbers, this is a called a concordance

Author: Antonio Dimitrov
*/

#include "circq.h"
#include "BST.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

/*Constants*/
const int NUMOFLETTERS = 26;

/****************************************************************************
Programmer: Antonio Dimitrov			

Basic Operations:

Constructor: constructs an explicit value constructor
addToQ	   : adds integer to queue
display    : Sends Concordance into output stream
getQ	   : Returns the queue
getWord	   : Returns the word string
****************************************************************************/
class Concordance {
	
public:
	void addToQ(int lineNumber) 
	{ if(lineNumber != lineQ.end()) lineQ.enqueue(lineNumber); }
	/**************************************************************************
	Add integer to the queue

	Pre: Integer is defined

	Post: Integer is added to the lineQ
	**************************************************************************/

	void display(ostream &out) const { out << word << " - " << lineQ; }
	/**************************************************************************
	Displays the concordance object

	Pre: The word string and the lineQ are properly defined

	Post: The word following the Queue are put into the outout stream
	**************************************************************************/

	CircularQ<int> getQ() const { return lineQ; }
	/**************************************************************************
	Return the queue

	Pre: None

	Post: Queue is returned
	**************************************************************************/

	string getWord() const { return word; }
	/**************************************************************************
	Return the word

	Pre: None

	Post: Word is returned
	**************************************************************************/

	Concordance(string myWord, int myLineNumber) 
	{ word = myWord; addToQ(myLineNumber); }
	/**************************************************************************
	Explicit value constructor for the Concordance object 

	Pre: Proper string and integer are passed in

	Post: The local variable word is declared and the integer is enqueued onto the 
		  local lineQ
	**************************************************************************/

private:
	string word;
	CircularQ<int> lineQ;
};

ostream &operator<<(ostream& out, const Concordance &concord) {
	
	concord.display(out);
	return out;
}//end <<
/*****************************************************************************
Overloads insertion operator for concordance object

Pre: The concordance object is properly defined

Post: The word following the Queue are put into the outout stream
*****************************************************************************/

bool operator<(const Concordance &word1, const Concordance &word2) {

	return word1.getWord() < word2.getWord();
}//end <
/*****************************************************************************
Overloads relational operator for the concordance object

Pre: The concordance object is properly defined

Post: Returns true if ascii value of word2 is greater than word1
*****************************************************************************/

string removeInvalidChars(string origWord);
/*****************************************************************************
Removes invalid characters (nonalpha) from word

Pre: The string is properly defined

Post: A string with only alpha characters is returned
******************************************************************************/

void stringToUpperCase(string &word); 
/*****************************************************************************
Converts string to all uppercase

Pre: The string is ahifted to uppercase

Post: Modifies the string so that it is only uppercase
******************************************************************************/

void displayBSTArray(int numOfElements, BST<Concordance> bstArray[]);
/*****************************************************************************
Displays the Concordance BST array to the console

Pre: Number of elements in the array and the array itself are passed in

Post: Displays the BST array to console
******************************************************************************/

int main() {
	/*Declaring variables*/
	ifstream infile("Alphabet.txt");
	string line, word;
	int lineNumber = 1;
	BST<Concordance> bstArray[NUMOFLETTERS];

	/*Check if the input file exists*/
	if (!infile) {
		cout << "Error - no file found" << endl;
		exit(1107);
	}//end if

	/*Loop through the file and grabs line per line*/
	while (getline(infile, line)) {

		istringstream ss(line);
		/*Loops through each line word per words*/
		while (ss >> word) {

			stringToUpperCase(word);				//Converts to uppercase
			word = removeInvalidChars(word);		//removes non alpha chars

			/*If the word is not empty insert the concordance object into 
			proper index location based on the first letter*/
			if (word != "") 
				bstArray[word[0] % 65].insertConcordance
				(Concordance(word, lineNumber));
			
		}//end while
		lineNumber++;		
	}//end while
	displayBSTArray(NUMOFLETTERS, bstArray);
	infile.close();
	return 0;
}//end main

//removeInvalidChars
string removeInvalidChars(string origWord) {
	string newWord = "";

	for (unsigned i = 0; i < origWord.length(); i++)
		if(isalpha(origWord[i]))
			newWord += origWord[i];

	return newWord;
}//end removeInvalidChars

//stringToUpperCase
void stringToUpperCase(string &word) {
	for (unsigned i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);
}//end stringToUpperCase

//displayBSTArray
void displayBSTArray(int numOfElements, BST<Concordance> bstArray[]) {
	for (int i = 0; i < numOfElements; i++) {
		cout << "---------------------------- INDEX " << (char)(65 + i)
			<< " ----------------------------" << endl;
		bstArray[i].graph(cout);
	}//end for
}//end displayBSTArray