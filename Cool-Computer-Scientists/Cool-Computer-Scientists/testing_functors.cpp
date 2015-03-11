//
//  testing_functors.cpp
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "testing_functors.h"

int pretend_main() {
    aClass myObj;
    
    aClass a, b, c;
    a.ivar_ = 4;
    b.ivar_ = -9;
    c.ivar_ = 16;
    
    coolClass<aClass> cc(a, c, b);
    
    myFunctorClass funct(b);
    
    std::cout << cc.find(funct) << std::endl;
    
    return 0;
}

int pretend_main_pointers() {
    aClass *aptr = new aClass(4);
    aClass *bptr = new aClass(-9);
    aClass *cptr = new aClass(16);
    
    aClass a, b, c;
    a.ivar_ = 4;
    b.ivar_ = -9;
    c.ivar_ = 16;
    
    int myvar;
    std::ifstream fin("myfile.txt");
    fin >> myvar;
    
    std::ifstream("myfile2.txt") >> myvar;
    
    std::vector<aClass> v;
    
    
//    coolClass<aClass> cc(a, b, c);
    coolClass_ptrs ccptr1(aptr, bptr, cptr);
    coolClass_ptrs ccptr2(&a, &b, &c);
    
    pointer_less ptrless;
    pointer_find ptrfind1(bptr);
    pointer_find ptrfind2(bptr);
    
    std::cout << ccptr1.find(ptrfind1) << std::endl;
    std::cout << ccptr2.find(ptrfind2) << std::endl;
    
    return 0;
}

#include "rb_tree.h"
#include "Team.h"

#include <vector>
#include <random>

//#include "test_rb_tree.h"

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

class less_wins {
public:
    bool operator() (const Team& t1, const Team& t2) {
        return t1.getWin() < t2.getWin();
    }
};
class equal_wins {
public:
    bool operator() (const Team& t1, const Team& t2) {
        return t1.getWin() == t2.getWin();
    }
};

int test_functor_tree() {
    rb_tree<Team, less_teamname, equal_teamname> nameleague;
    rb_tree<Team, less_wins, equal_wins> winsleague;
    
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
        winsleague.insert(pretendleague[i]);
    }
    
    nameleague.basic_print(std::cout);
    
    std::cout << "\n----------------\n\n" << std::flush;
    
    winsleague.basic_print(std::cout);
    
    return 0;
}



// these are all DEPRECATED; they use the old rb_tree (without functors)
// if you want to test them, use the "old_rb_tree.h" header file
/*
int test_rb_tree() {
    const int samplesize = 10;
    
    
    rb_tree<int> tree;
    
    std::vector<int> v;
    std::vector<int> input;
    for (int i = 0; i < samplesize; i++) {
        input.push_back(i);
    }
    
    std::random_shuffle(input.begin(), input.end());
    
    for (int i = 0; i < input.size(); i++) {
        tree.insert(input[i]);
    }
    
    std::cout << "input is of size " << input.size() << "\n";
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i];
        i < input.size()-1 ? std::cout << ", " : std::cout << "\n" << std::flush;
    }
    
    tree.basic_print(std::cout);
    
    tree.insert(11);
    tree.basic_print(std::cout);
    
    return 0;
}

#include "Team.h"

int test_rb_tree_with_teams() {
    
    rb_tree<Team> treeleague;
    
    vector<Team> pretendleague;
    Team barcelona("barcelona", 20, 17, 2, 1, 32);
    Team westsydney("western sydney", 20, 2, 16, 2, 4);
    Team sanjose("san jose earthquakes", 20, 10, 8, 2, 14);
    Team newyork("new york apples", 20, 13, 2, 5, 21);
    Team greece("greek debt crisis", 20, 5, 12, 3, 8);
    Team madrid("real madrid", 20, 0, 19, 1, 1);
    
    pretendleague.push_back(barcelona);
    pretendleague.push_back(westsydney);
    pretendleague.push_back(sanjose);
    pretendleague.push_back(newyork);
    pretendleague.push_back(greece);
    pretendleague.push_back(madrid);
    
    for (int i = 0; i < pretendleague.size(); i++) {
        treeleague.insert(pretendleague[i]);
    }
    
    treeleague.basic_print(std::cout);
    
    return 0;
}/*


// These were me messing around with function pointers; they can be safely ignored.

//#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

/*
 class iless {
 public:
 bool less(const aClass& a, const aClass& b) {
 return (a.ivar_ < b.ivar_);
 }
 };
 */

/*
 class i_equal {
 private:
 aClass obj_;
 public:
 i_equal(aClass& obj) {
 obj_ = obj;
 }
 bool eq(const aClass& b) const {
 return (obj_.ivar_ == b.ivar_);
 }
 };
 */

//typedef bool (aClass::*icmp)(const aClass& b) const;
