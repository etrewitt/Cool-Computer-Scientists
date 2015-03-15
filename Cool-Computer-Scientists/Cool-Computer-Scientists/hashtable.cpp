// Hash implemtation for Hash Table class

#include <string>
#include <iostream>
#include "hashtable.h"
#include "TeamClass.h"
using namespace std;

int HashTable::getKey(string word)
// Create the key for the hashed table
{
    int hashed = 0;
    int length = word.length();
    for (int z =0; z < length; z++)
        hashed = ( hashed + (int)word[z] );
    hashed = hashed % size;
    
    return hashed;
}

int HashTable::colSolution(string word, int index, int size)
// collision Resolution
// use offset open addressing
// similar to hashing function
// offset is the the key / size
{
    int offset = (int)word[0]*word[1] / size;
    
	   int new_index = index + offset;
    new_index = new_index % size;
	   return new_index;
    
}

bool HashTable::search(Team *data, Team *returnedData)
// Search for a particular class,
// return true if it is found
// using the hashing function first
// May use collision resolution for the 2nd case
{
    bool found = false;
    int t = getKey(data->getName());
    
    if (teamobject[t] && (*teamobject[t]) == (*data)){
        found = true ;
        returnedData = teamobject[t] ;
    }
    else {
        for (int i = 0 ; i < max_probe ; i++) {
            t = colSolution(data->getName(), t, size);
            if (teamobject[t] && (*teamobject[t]) == (*data)){
                found =  true ;
                returnedData = teamobject[t] ;
            }
        }
    }
    return found ;
}


//void HashTable::print()
//// Print all the variables in the array
//// using display function
//{
//	   for (int i = 0; i < size; i++)
//       {
//           if (teamobject[i])
//               display(teamobject[i]) ;
//       }
//}

void HashTable::add(Team * obj)
// Add an Team title to the class
// Check if pointer is pointing to a class or not (empty)
// If yes use collision Resolution
{
    int location = getKey(obj->getName());
    int tempProbe = 0 ;
    
    while ( teamobject[location] != 0)   // If the element is not empty -> find a new element
    {
        location = colSolution(obj->getName(), location, size);
        tempProbe++ ;
    }
    if(tempProbe > max_probe){
        max_probe = tempProbe;
        topOfChain = *obj;
    }
    load ++ ;
    teamobject[location] = obj;
}


bool HashTable::remove(Team *entry)
// Remove an album Tittle from the array
// Search first to see it exists or not
{
    bool found = false;
    int t = getKey(entry->getName());
    
    if (teamobject[t] && (*teamobject[t]) == (*entry))
        found = true ;
    else {
        for (int i = 0 ; i < max_probe ; i++) {
            t = colSolution(entry->getName(), t, size);
            if (teamobject[t] && (*teamobject[t]) == (*entry))
                found =  true ;
            break ;
        }
    }
    
    teamobject[t] = 0 ;
    load--;
    if (topOfChain.getName() == entry->getName()){
        max_probe--;
    }
    
    return found;
}



//void HashTable::printStat()
//// Print all statistic about the the array
//// elements, max size, load factor, longest chain
//{
//    
//    cout << "Total number of Team " << load << endl;
//    cout << "The size of the array " << size << endl;
//    cout << "The load factor is " << (load *  100 / size) << "  %  " << endl;
//    cout << endl << "The highest probe is  " << max_probe << endl;
//    
//    cout << endl << "Longest Chain is:  " << endl;
//    
//    int t = getKey(topOfChain.getName());
//    if (teamobject[t]!=0)
//        display(teamobject[t]);
//    
//    for (int i = 0 ; i < max_probe ; i++) {
//        t = colSolution(topOfChain.getName(), t, size);
//        if (teamobject[t]!=0)
//            display(teamobject[t]);
//    }
//    
//    
//    
//}
