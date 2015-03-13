//
//  notes_for_others.cpp
//  Cool-Computer-Scientists
//
//  Created by Erik Trewitt on 3/12/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#include "notes_for_others.h"

#include "testing_functors.h"

#include "rb_tree.h"
#include "Team.h"

#include <iostream>
#include <fstream>
#include <vector>


// print functors (for visit())
class simpleprint {
public:
    bool operator() (const Team& t1) {
        // replace simpleprint(), normalprint(), and/or detailedprint() with whatever print methods the Team class actually has
        t1.simpleprint();
    }
};
class normalprint {
public:
    bool operator() (const Team& t1) {
        t1.normalprint();
    }
};
class detailedprint {
public:
    bool operator() (const Team& t1) {
        t1.detailedprint();
    }
};


// comparison functors
class less_teamname {
public:
    bool operator() (const Team& t1, const Team& t2) {
        return t1.getName() < t2.getName();
    }
};
class equal_teamname {
public:
    bool operator() (const Team& t1, const Team& t2) {
        return t1.getName() == t2.getName();
    }
};


int test_functor_tree() {
    rb_tree<Team, less_teamname, equal_teamname> nameleague;
    
    Team barcelona("barcelona", 20, 17, 2, 1, 32);
    Team westsydney("western sydney", 20, 2, 16, 2, 4);
    Team sanjose("san jose earthquakes", 20, 10, 8, 2, 14);
    Team newyork("new york apples", 20, 13, 2, 5, 21);
    Team greece("greek debt crisis", 20, 5, 12, 3, 8);
    Team madrid("real madrid", 20, 0, 19, 1, 1);
    vector<Team> pretendleague = {barcelona, westsydney, sanjose, newyork, greece, madrid};
    
    /*
     pretendleague.push_back(barcelona);
     pretendleague.push_back(westsydney);
     pretendleague.push_back(sanjose);
     pretendleague.push_back(newyork);
     pretendleague.push_back(greece);
     pretendleague.push_back(madrid);*/
    
    for (int i = 0; i < pretendleague.size(); i++) {
        nameleague.insert(pretendleague[i]);
    }
    
    nameleague.basic_print(std::cout);
    
    std::cout << "\n----------------\n\n" << std::flush;
    
// this is how I'd currently have you print things
    nameleague.visit(simpleprint);
    nameleague.visit(normalprint);
    nameleague.visit(detailedprint);
    
    return 0;
}