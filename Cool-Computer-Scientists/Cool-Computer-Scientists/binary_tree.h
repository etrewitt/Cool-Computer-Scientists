//
//  binary_tree.h
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef Cool_Computer_Scientists_binary_tree_h
#define Cool_Computer_Scientists_binary_tree_h

#include <memory>
#include <vector>
#include <string>

template <typename T>
struct TNode {
    T data_;
    TNode<T>* more_, less_, stem_;
    
    TNode(const T& data) {
        data_ = data;
    }
};

template <typename T, typename lessthan>
class binary_tree {
private:
    TNode<T>* root_;
    int size_;
    lessthan less;
public:
    binary_tree();
    ~binary_tree();
    
    // this returns the closest node to a given object
    // "closeness" is measued by the method the lessthan function uses
    TNode<T>* lookup(const std::shared_ptr<T>& data) const;
    
    // these do exactly what they sound like
    void insert(const T& data);
    void pop_min();
    void pop_max();
    
    // these access the min/max nodes
    const T& min() const;
    const T& max() const;
    
    // you can ignore this, at least for now, it's just a method to find
    // all elements in the tree that match an arbitrary equivalence function,
    // which is passed as a parameter
    typedef bool functype(const T& t) const;
    template <typename functype>
    std::vector<T>& visit(functype equalfunc);
    
    // this is like the visit function, except instead of returning the matching objects, it does things to them
    typedef bool funcdo(const T& t);
    template <typename functype, typename funcdo>
    void visit_do(functype equalfunc, funcdo dofunc);
    
    void print(std::string delimiter, bool ascending=true);
};

#endif
