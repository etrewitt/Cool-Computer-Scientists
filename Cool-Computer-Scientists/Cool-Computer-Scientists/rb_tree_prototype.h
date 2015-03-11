//
//  rb_tree_prototype.h
//  Cool-Computer-Scientists
//
//  Created by Erik Trewitt on 2/28/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef Cool_Computer_Scientists_rb_tree_prototype_h
#define Cool_Computer_Scientists_rb_tree_prototype_h

/* RULES
 1) all nodes are either red OR black
 2) root is black (arbitrary)
 3) NILs are black (same color as root)
 4) every red node has two black children
 5) every path from any node to any of its descendent NIL has the same number of black nodes
 */

#include <cstdlib>
#include <iostream>
#include <vector>

// these are to be implemented at a later date; they will allow more flexible sorting
//template <typename T, typename lessthan, typename equalto>
//template <typename T, typename lessthan>
template <typename T>
class rb_tree {
private:
    enum color { RED, BLACK };
    
    // found at the bottom of the file
    struct rb_node;
    
    rb_node* root_;
    int size_;
    
    // these are to be implemented at a later date; they will allow more flexible sorting
    //    lessthan less;
    //    equalto equal;
    
    // private methods are also at the bottom of the file
public:
    rb_tree() {
        root_ = NULL;
        size_ = 0;
    }
    ~rb_tree();
    
    
    const T& root() const;
    const T& min() const;
    const T& max() const;
    int size() const;
    int height() const;
    
    void insert(const T& data);
    
    // this returns the closest node to a given object
    // "closeness" is measued by the method the lessthan function uses
    rb_node* lookup(const T& data) const;
    
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
    
    // not yet fully implemented
    void remove(const T& data);
    
    // prints the tree; a far more basic print method than the one below, but it has the advantage of having been implemented already
    void basic_print(std::ostream& out, std::string delimiter="\n") const;
    
    void print(std::ostream& out, std::string& delimiter, bool ascending=true) const;
    
    void clear();
    void rebalance();
    
    int* count_branches() const;
    
private:
    void rotate_left(rb_node* node);
    void rotate_right(rb_node* node);
    
    void case_1(rb_node* node)      // if node is the root, set it to be black,
                                    // otherwise, call case2.
    void case_2(rb_node* node)      // if parent is black, return, otherwise, call case3
                                    // (we already know that if parent is black,
                                    // then adding a red to it won't change balance).
    void case_3(rb_node* node);     // if the uncle is red, set parent and uncle black, grandparent to be red
                                    // call case1 on grandparent
    void case_4(rb_node* node);     // rotates if inner
                                    // if rotated, call case5 on the respective child, otherwise, call case5
    void case_5(rb_node* node);     // sets parent to be black, grandparent to be red
                                    // rotates left or right depending on which side of the parent it's on
    
    // returns a pointer to a node containing the data being searched for
    rb_node* find_node(const T& data) const;
    
    // deletes all nodes in the tree
    void clear(rb_node* node);
    
    // recursively prints from least to greatest; placeholder until I implement the next two
    void basic_print(std::ostream& out, rb_node* node, std::string delimiter) const;
    
    // these two are yet to be implemented
    // recursively prints from least to greatest
    void print_ascending(std::ostream& out, rb_node* node, std::string delimiter) const;
    // recursively prints from greatest to least
    void print_descending(std::ostream& out, rb_node* node, std::string delimiter) const;
    
    // counts the number of NIL nodes
    int count_leaves(rb_node* node) const;
    
    
    struct rb_node {
        T data_;
        
        rb_node* less_;
        rb_node* more_;
        rb_node* parent_;
        color color_;
        
        // methods:
        rb_node(const T& data) {
            data_ = data;
            less_ = NULL;
            more_ = NULL;
            parent_ = NULL;
            
            color_ = RED;
        }
        
        void less(rb_node* child) {
            this->less_ = child;
            child->parent_ = this;
        }
        void more(rb_node* child) {
            this->more_ = child;
            child->parent_ = this;
        }
        
        rb_node* grandparent() const;
        rb_node* sibling() const;
        rb_node* uncle() const;
    };
};


#endif
