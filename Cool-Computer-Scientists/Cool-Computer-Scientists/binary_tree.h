//
//  binary_tree.h
//  Cool-Computer-Scientists
//
//  Created by etrewitt on 2/18/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef Cool_Computer_Scientists_binary_tree_h
#define Cool_Computer_Scientists_binary_tree_h

#include <iostream>
#include <vector>
#include <string>

class node_interface {
private:
    
public:
    virtual bool operator<(const node_interface&) const =0;
    virtual bool operator>(const node_interface&) const =0;
    
    virtual void print(std::ostream&) const =0;
};

template <typename T, typename lessthan>
class binary_tree {
private:
    struct TNode {
        T data_;
        TNode* more_, less_, stem_;
        
        TNode(const T& data) {
            data_ = data;
        }
    };
    
    TNode* root_;
    unsigned int size_;
    lessthan less;
    
// Public member functions:
public:
    binary_tree();
    ~binary_tree();
    
    // this returns the closest node to a given object
    // "closeness" is measued by the method the lessthan function uses
    TNode* lookup(const T& data) const;
    
    // these do exactly what they sound like
    void insert(const T& data);
    
    // these access the min/max nodes
    const T& min() const;
    const T& max() const;
    const T& root() const;
    unsigned int size() const;
    int height() const;
    
    // you can ignore this, at least for now, it's just a method to find
    // all elements in the tree that match an arbitrary equivalence function,
    // which is passed as a parameter
    typedef bool funcfind(const T& t) const;
    template <typename funcfind>
    std::vector<T>& visit(funcfind equalfunc);
    
    // this is like the visit function, except instead of returning the matching objects, it does things to them
    typedef void funcdo(T& t);
    template <typename funcfind, typename funcdo>
    void visit_do(funcfind equalfunc, funcdo dofunc);
    
    void rebalance();
    
    void print(std::ostream& out, std::string& delimiter, bool ascending=true) const;
    
    void clear();
    
    // returns a two-element int array, {number of less branches, number of greater branches}
    int* count_branches() const;
    
// Private member functions:
private:
    void clear(TNode* node);
    void print_ascending(std::ostream& out, TNode* node, std::string delimiter) const;
    void print_descending(std::ostream& out, TNode* node, std::string delimiter) const;
    int count_leaves(TNode* node) const;
};

#endif
