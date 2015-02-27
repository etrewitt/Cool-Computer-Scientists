//
//  testing_functors.h
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef __Cool_Computer_Scientists__testing_functors__
#define __Cool_Computer_Scientists__testing_functors__

#include <string>

struct aClass {
    int ivar_;
    char cvar_;
    std::string svar_;
    
    bool iequal(const aClass& b) const {
        return (ivar_ == b.ivar_);
    }
};

class myFunctorClass {
private:
    aClass a_;
public:
    myFunctorClass(aClass& a) {
        a_ = a;
    }
    bool operator() (const aClass& b) const {
        return a_.ivar_ == b.ivar_;
    }
};

class myFunctorDoClass {
public:
    void operator() (aClass& ac) {
        ++(ac.ivar_);
    }
};

template <typename T>
class coolClass {
private:
    aClass arr[3];
    
public:
    coolClass(aClass& a, aClass& b, aClass& c) {
        arr[0] = a; arr[1] = b; arr[2] = c;
    }
    
    typedef bool functype(const aClass& b) const;
    
    template <typename functype>
    int find(functype equalfunc) {
        for (int i = 0; i < 3; i++) {
            if (equalfunc(arr[i])) {
                return i;
            }
        }
        return -1;
    }
};

int pretend_main();

int test_rb_tree();

#endif /* defined(__Cool_Computer_Scientists__testing_functors__) */
