// hash table heaader file
#ifndef _HASHTABLE_H
#define _HASHTABLE_H


#include <string>
#include <iostream>
#include "TeamClass.h"

using namespace std;

class HashTable
{
private:
    Team **teamobject; //collection of data
    int size; // size of the table
    int max_probe; // the number of biggest collision
    int load ;
    Team topOfChain;
    
    // Function prototype
public:
    
    void printStat(); // print the load and how many max probs
    bool search(Team*,Team *); // search for a paticular data type
    HashTable() { size = 0; teamobject = new Team*(); max_probe = 0;load = 0;} // default constructor
    //double hash array
    
    HashTable(int s)  {
        load = 0 ;
        size = 2 * s; // double the size of the array less prob of collision
        teamobject = new Team* [size];
        max_probe = 0 ;
        for(int i = 0; i< size; i++) {
            teamobject[i] = 0; }
    }
    
    void add(Team * obj); // add the data
    void print(); // print the record
    int getKey(string words);  // Hashed function  -> get the home addresss
    int colSolution(string word, int index, int size); // when it collides, finds the next location
    
    int getSize() { return size; } // gets the size of the table
    Team** getTeamObject() {return teamobject;} // get the information
    bool remove(Team*); //remove a particular data type
};

#endif
