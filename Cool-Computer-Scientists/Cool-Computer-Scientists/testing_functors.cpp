//
//  testing_functors.cpp
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#include <iostream>

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

#include "rb_tree.h"

#include <vector>
#include <random>

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
}

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
