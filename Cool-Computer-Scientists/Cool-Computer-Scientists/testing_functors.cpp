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
