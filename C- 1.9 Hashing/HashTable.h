/*********************************************************************
    Author:        Dana Vrajitoru, IUSB, CS
    Class:         C243 Data Structures
    File name:     HashTable.h
    Last updated:  October 1, 2018
    Description:   Definition of a hash table.
**********************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <string>

#include "WordCounter.h"

// Default capacity if the table is created with the default constructor.
const int DEF_CAPACITY = 200;

typedef list<WordCounter> ListWordC;
typedef ListWordC::iterator ListIter;

class HashTable {
private:
    vector<ListWordC> storage;
    int capacity;
    int numObjects;
    
    // Checks if the access to a given position is safe in the
    // storage. This means if the position is smaller than the
    // capacity and non negative.
    bool isValid(int position);
    
    // This function inserts an object in the table when we already know
    // what position we want it to be inserted at. It is declared as
    // private because the user should not be able to call it. It is
    // designed to be called internally by the public insertion function
    // after getting the position from the hashing function.
    //
    // If the key of wordc has been used in the table at this position,
    // then the function returns false without modifying wordc. If not, it
    // inserts wordc into the list at this position and returns true.
    bool insert(WordCounter &wordc, int position);
    
    // This function removes the word counter object from the list at
    // the given position. The key k is a separate parameter from the
    // object because we don't know what the object is yet. It is also
    // intended to be called internally because public remove function
    // should determine the position based on the hash function before
    // it calls this one.
    // wordc is an output parameter: the removed object must be copied
    // into it.
    bool remove(WordCounter &wordc, string k, int position);
    
    // Private functions to be implemented by the student.

    // This private function should find if any object stored in the list
    // linked from the given position contains the key k. If yes, then it
    // should copy that object into the object wordc and return true. If
    // not, it should return false.
    //
    // wordc is an output parameter: if the key can be found, the object
    // containing it should be copied into wordc.
    bool access(WordCounter &wordc, string k, int position);
    
    // The most important function of the class. This function takes a
    // string (a key) and determines the index in the storage array
    // where a object with that key should go.
    int hashing(string k);
    
public:
    // Constructor with given initial capacity.
    HashTable(int size = DEF_CAPACITY);
    // Destructor.
    ~HashTable();
    // Delete all the objects without deleting the storage array.
    void makeEmpty();
    
    // Prints all the objects in the table.
    void print();
    
    // Public functions to be implemented by the student.
    
    // This function should first get the hash index for the key of the
    // object wordc, then call the private function insert with that
    // index and the same object wordc.
    //
    // The function checks if an object with the key of wordc exists
    // in the table already, and returns false if so without changing
    // the table. 
    // If the key has not been used in the table before, it inserts
    // wordc in the table and returns true.
    bool insert(WordCounter &wordc);
    
    // This function should first get the hash index for the string,
    // then call the private function access with this index. 
    //
    // If the an object containing the key k exists in the table, the
    // function returns true and a copy of the object in the parameter
    // wordc. If such an object does not exist, the function returns
    // false and wordc is not changed.
    //
    // wordc is an output parameter: the object found containing k
    // must be copied into it.
    bool access(WordCounter &wordc, string k);
    
    // This function should first get the hash index for the string k,
    // then call the private remove function with this index. 
    //
    // The function returns true if an object containing the key k can
    // be found in the table and is removed from it, and false if not.
    //
    // wordc is an output parameter: the removed object must be copied
    // into it.
    bool remove(WordCounter &wordc, string k);

    // Resizes the table and rehashes it, moving each stored element
    // at the index corresponding to the resized hash function.
    void resize(int newSize);
    
    // This function should print a statistic of usage of each index in
    // the table as the number of objects stored at each index. It
    // should not output individual elements.
    void statistic();
};

#endif