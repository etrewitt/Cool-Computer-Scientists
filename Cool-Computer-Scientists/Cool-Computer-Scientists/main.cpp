//
//  main.cpp
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//
//  Commit #1

// This has an example of a simple functor.
//#include "testing_functors.h"

#include <iostream>
#include <string>

#include "rb_tree.h"

class int_less {
public:
    bool operator()(const int x, const int y) const {
        return x < y;
    }
};
class int_equal {
public:
    bool operator()(const int x, const int y) const {
        return x == y;
    }
};

class simpleprint {
    std::ostream* out_;
    int max_;
public:
    simpleprint(std::ostream& out, int max) {
        out_ = &out;
        max_ = max;
    }
    void operator()(int i) const {
        if (i != max_) {
            *out_ << i << ", ";
        } else {
            *out_ << i << "\n" << std::flush;
        }
    }
};

int main(int argc, const char * argv[]) {
    //    pretend_main();
    
    //    test_rb_tree();
    
    //    test_rb_tree_with_teams();
    
    //    pretend_main_pointers();
    
    //    test_functor_tree();
    
    rb_tree<int, int_less, int_equal> itree;
    
    int arr[19] = {40, 20, 60, 10, 30, 50, 70, 5, 15, 25, 35, 45, 55, 65, 75, 2, 7, 12, 27};
    
    for (int i = 0; i < 19; i++) {
        itree.insert(arr[i]);
    }
    
    simpleprint sp(std::cout, itree.max());
    
    
    itree.visit(sp);
    
    itree.remove(35);
    
    itree.visit(sp);
    
    return 0;
}
