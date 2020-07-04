/* WordList source file
*
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias m_list in any way that would result
*	in undefined behavior. 
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



// Do not include any other libraries

// #include"debugmem.h" 

#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;



/* Function: Wordlist Constructor
*
*	Constructs an empty Wordlist that is allocated enough space to store 
*	max_words many words.  If max_words is less than 1, set m_list to nullptr
*	and the other member variables should be made consistent with this state.  
*/
WordList::WordList(const int max_words) {

	if (max_words < 1) {				
		m_count = 0;
		m_max = 0;
		m_list = nullptr;
	}
	else {								
		m_list = new char* [max_words];
		for (int i = 0; i < max_words; i++) 
			m_list[i] = new char[MAX_WORD_SIZE];
		m_count = 0;
		m_max = max_words;
	}
	

}


/* Function: Wordlist Copy Constructor
*
*	Constructs a Wordlist that is a copy of an existing WordList
*/
WordList::WordList(const WordList &other) {
	
	m_count = other.m_count;
	m_max = other.m_max;
	m_list = new char* [m_max];
	for (int i = 0; i < m_max; i++) {
		m_list[i] = new char[MAX_WORD_SIZE];
		strcpy(m_list[i],other.m_list[i]);
	}
}


/* Function: Wordlist Destructor
*
*	Cleans up WordList's dynamically allocated memory.
*/
WordList::~WordList() {
	
	m_count = 0;
	m_max = 0;
	for (int i = 0; i < m_max; i++) 
		delete[] m_list[i];
	delete[] m_list;
	
}

/* Function: printList
*
*	Prints all the words in WordList in a single line with spaces between each
*	word, then followed by a newline after the last word. Returns the number 
*	of words printed.  If m_list is nullptr there is nothing to print, return -1. 
*/
int	WordList::print() const {

	if (m_list == nullptr)
		return -1;

	//Prints each word but only prints a space if the word exists
	for (int i = 0; i < m_count; i++) {
		cout << m_list[i];
		int check = strcmp(m_list[i], "");				
		if (check != 0) {
			cout << " ";
		}
	}
	return m_count;
	

}



/* Function: at
*
*	Returns the word at the index position in the WordList.
*	return nullptr if the index is out of bounds.
*/
char* WordList::at(const int index) const {

	if (index > m_count)
		return nullptr;
	return m_list[index];

}


/* Function: count
*
*	Returns the number of words currently stored in WordList.
*/
int	WordList::count() const {

	return m_count;

}


/* Function: add
*
*	Adds the word into WordList (words have no spaces).  If WordList does not have
*	enough space to add word, addWord will resize with just enough space to allow for 
*	the addition of word. If addWord needed to resize then return 1, otherwise if there 
*	already enough space to add word without resizing, return 0. If word is empty  
*	do nothing return -1. If m_list was nullptr, everything above still holds true except
*	return -2.  
*/
int	WordList::add(const char word[]) {
	
	int check = strcmp(word, "");
	if (check == 0) 
		return -1;
	
	//If not enough memory, copies original list to temp list, recreates original list with proper size, and copies temp back in to original
	if (m_count >= m_max) {
		char** temp_list = new char*[m_max + 1];
		for (int i = 0; i < m_max; i++) {
			temp_list[i] = new char[MAX_WORD_SIZE];
			strcpy(temp_list[i], m_list[i]);
		}
		temp_list[m_max] = new char[MAX_WORD_SIZE];
		m_list = new char* [m_max+1];
		for (int i = 0; i < m_max+1; i++) {
			m_list[i] = new char[MAX_WORD_SIZE];
			strcpy(m_list[i], temp_list[i]);
		}
		strcpy(m_list[m_count], word);
		m_count++;
		m_max++;
		if (m_list == nullptr) 
			return -2;
		return 1;
	}
	else {
		strcpy(m_list[m_count], word);
		m_count++;
		return 0;
	}
}


/* Funtion: remove
*
*	If m_list is nullptr, returns -1.  Otherwise, searches for every
*	occurrence of word[], and removes that word off the list, returns
*	the number of words removed.
*/
int	WordList::remove(const char word[]) {

	if (m_list == nullptr) 
		return -1;
	int count = 0;
	for (int i = 0; i < m_max; i++) {
		int check = strcmp(m_list[i], word);
		if (check == 0) {
			strcpy(m_list[i], "");
			count++;
		}
	}
	return count;
}


/* Funtion: append
*
*
*	Appends the contents of other to the WordList.  If WordList does 
*	not have enough space appendList should dynamically allocate enough space
*	to append the contents of other to WordList, returns number of words 
*	appended.  If other is nullptr or empty appendList does nothing and 
*	returns -1. If this WordList::m_list is nullptr everything above still 
*	holds but returns -2.
*
*	Note the pointer parameter type as opposed to reference type.
*/
int	WordList::append(const WordList* other) {

	if (other->m_list == nullptr)
		return -1;

	//If not enough memory, create temporary list of size original count + other count, and copy all words from the original and new into it
	if (m_max < m_count + other->m_count) {
		char** temp_list = new char* [m_count + other->m_count];
		for (int i = 0; i < m_count; i++) {
			temp_list[i] = new char[MAX_WORD_SIZE];
			strcpy(temp_list[i],m_list[i]);
		}
		for (int i = 0; i < other->m_count; i++) {
			temp_list[i + m_count] = new char[MAX_WORD_SIZE];
			strcpy(temp_list[i + m_count],other->m_list[i]); //Warning "Reading invalid data from 'temp_list':  the readable size is '(m_count+m_count)*4' bytes, but '8' bytes may be read." no idea what this is :/
		}

		m_list = new char* [m_count + other->m_count];
		for (int i = 0; i < m_count + other->m_count; i++) {
			m_list[i] = new char[MAX_WORD_SIZE];
			strcpy(m_list[i], temp_list[i]); 
		}
		m_count = m_count + other->m_count;
		m_max = m_count;
		return other->m_count;
	}
	else {
		for (int i = m_count; i < m_count + other->m_count; i++) {
			strcpy(m_list[i],other->m_list[i]);
		}
	}
	if (m_list == nullptr)
		return -2;

}


/* Funtion: find
*
*	Finds the first occurrence of the word in the WordList
*	returns the position of that word in the list.  Otherwise, 
*	if the word is not in the WordList or if m_list is nullptr
*	return -1. 
*/
int WordList::find(const char word[]) const {

	if (m_list == nullptr)
		return -1;
	for (int i = 0; i < m_max; i++) {
		int check = strcmp(m_list[i], word);
		if (check == 0)
			return i;
	}
	return -1;

}


/* Funtion: sort
*
*	If m_list is nullptr return -1.  If there is only one word
*	in the list return 1.  Otherwise, sortList sorts the
*	words in WordList in ascending order.  Returns 0 on
*	success.
*/
int	WordList::sort() { //USE BUBBLE SORT

	if (m_list == nullptr)
		return -1;
	if (m_count == 1)
		return 1;
	
	bool swap;
	do {
		swap = false;
		for (int i = 0; i < m_count-1; i++) {
			int check = strcmp(m_list[i], m_list[i + 1]);
				if (check > 0) {
					char* temp = new char[MAX_WORD_SIZE];
					strcpy(temp, m_list[i]);
					strcpy(m_list[i], m_list[i + 1]);
					strcpy(m_list[i + 1], temp);
					swap = true;
			}
		}
	} while (swap);
	
	return 0;
}


/* Funtion: Assignment Operator
*
*	Overload the assignment operator for WordList.  Makes a deep 
*	copy from other to this WordList.  
*/
WordList& WordList::operator=(const WordList &other) {
	
	m_list = new char*[other.m_max];
	for (int i = 0; i < other.m_max; i++) {
		m_list[i] = new char[MAX_WORD_SIZE]; //another warning, the writable size is '(m_count+m_count)*4' bytes, but '8' bytes may be read.
		strcpy(m_list[i],other.m_list[i]); //another warning, reading invalid 
	}
	
	m_max = other.m_max;
	m_count = other.m_count;
	
	return *this;
}