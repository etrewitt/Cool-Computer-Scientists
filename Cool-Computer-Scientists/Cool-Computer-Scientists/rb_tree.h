//
//  rb_tree.h
//  Cool-Computer-Scientists
//
//  Created by Erik Trewitt on 2/27/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef Cool_Computer_Scientists_rb_tree_h
#define Cool_Computer_Scientists_rb_tree_h

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

template <typename T, typename lessthan, typename equalto>
//template <typename T, typename lessthan>
//template <typename T>
class rb_tree {
private:
    enum color { RED, BLACK };
    
    // found at basically the bottom of the file
    struct rb_node;
    
    rb_node* root_;
    int size_;
    
    // these are to be implemented at a later date
    lessthan less;
    equalto equal;
public:
    rb_tree() {
        root_ = NULL;
        size_ = 0;
    }
    ~rb_tree() {
        clear();
    }
    
    const T& root() const {
        return root_->data_;
    }
    const T& min() const {
        return min(root_)->data_;
    }
    const T& max() const {
        return max(root_)->data_;
    }
    int size() const {
        return size_;
    }
    
    // not sure how to implement this yet
    int height() const;
    
    void insert(const T& data) {
        rb_node* nu = new rb_node(data);
        if (root_ == NULL) {
            root_ = nu;
            ++size_;
//            std::cerr << "created root to be " << nu << "\n";
        } else {
            rb_node* cursor = root_;
            while (true) {
//                if (nu->data_ < cursor->data_) {
                if (less(nu->data_, cursor->data_)) {
                    if (cursor->less_ == NULL) {
                        cursor->less(nu);
//                        std::cerr << "created " << cursor->less_ << "\n";
                        ++size_;
                        break;
                    } else {
                        cursor = cursor->less_;
                    }
                } else {
                    if (cursor->more_ == NULL) {
                        cursor->more(nu);
//                        std::cerr << "created " << cursor->more_ << "\n";
                        ++size_;
                        break;
                    } else {
                        cursor = cursor->more_;
                    }
                }
            }
        }
        case_1(nu);
    }
    
    // this returns the closest node to a given object
    // "closeness" is measued by the method the lessthan function uses
    // not sure how to implement this yet; I don't think it's even needed (or wanted)
    rb_node* lookup(const T& data) const;
    
    rb_node* find(const T& data) const {
        rb_node* iter = root_;
        while (iter != NULL) {
            if (equal(data, iter->data_)) {
                break;
            } else if (less(data, iter->data_)) {
                iter = iter->less_;
            } else {
                iter = iter->more_;
            }
        }
        
        return iter;
    }
    
    // you can ignore this, at least for now, it's just a method to find
    // all elements in the tree that match an arbitrary equivalence function,
    // which is passed as a parameter
    typedef bool funcfind(const T& t) const;
    template <typename funcfind>
    std::vector<T> visit_find(funcfind equalfunc, bool preorder=1) {
        std::vector<T> vect;
        
        if (preorder) {
            previsit_find(root_, vect, equalfunc);
        } else {
            postvisit_find(root_, vect, equalfunc);
        }
    }
    
    // this is like the visit function, except instead of returning the matching objects, it does things to them
    typedef void funcdo(T& t);
    template <typename funcfind, typename funcdo>
    void visit_do(funcfind equalfunc, funcdo dofunc, bool preorder=1) {
        if (preorder) {
            previsit_do(root_, equalfunc, dofunc);
        } else {
            postvisit_do(root_, equalfunc, dofunc);
        }
    }
    
    // this one I just made and it can do either and/or both if you write a good enough function
    typedef void visitfunc(T& t);
    template <typename visitfunc>
    void visit(visitfunc func, bool preorder=1) {
        if (preorder) {
            previsit(root_, func);
        } else {
            postvisit(root_, func);
        }
    }
    
    
    // FINALLY fully implemented
    void remove(const T& data) {
        rb_node* node = find(data);
        
        if (node != NULL) {
            del_node(node);
        }
    }
    
    void print(std::ostream& out, std::string& delimiter, bool ascending=true) const;
    
    void basic_print(std::ostream& out, std::string delimiter="\n") const {
        out << size_ << " elements in the tree:\n";
        basic_print(out, root_, delimiter);
        out << std::flush;
    }
    
    void clear() {
        clear(root_);
    }
    void rebalance();
    
    int* count_branches() const;
    
private:
    void rotate_left(rb_node* node) {
        bool node_on_parent_less = true;
        if (node != root_) {
            if (node->parent_->less_ == node) {
                node_on_parent_less = true;
            } else {
                node_on_parent_less = false;
            }
        }
        rb_node* right = node->more_;
        
        right->parent_ = node->parent_;
        node->parent_ = right;
        
        node->more_ = right->less_;
        if (node->more_) {
            node->more_->parent_ = node;
        }
        right->less_ = node;
        
        if (node == root_) {
            root_ = right;
        } else {
            if (node_on_parent_less) {
                right->parent_->less_ = right;
            } else {
                right->parent_->more_ = right;
            }
        }
    }
    void rotate_right(rb_node* node) {
        bool node_on_parent_less = true;
        if (node != root_) {
            if (node->parent_->less_ == node) {
                node_on_parent_less = true;
            } else {
                node_on_parent_less = false;
            }
        }
        
        rb_node* left = node->less_;
        left->parent_ = node->parent_;
        node->parent_ = left;
        
        node->less_ = left->more_;
        if (node->less_) {
            node->less_->parent_ = node;
        }
        left->more_ = node;
        
        if (node == root_) {
            root_ = left;
        } else {
            if (node_on_parent_less) {
                left->parent_->less_ = left;
            } else {
                left->parent_->more_ = left;
            }
        }
    }
    
    void case_1(rb_node* node) {
//        std::cerr << "case_1; ";
        if (node->parent_ == NULL) {
            node->color_ = BLACK;
//            std::cerr << "set " << node->data_ << " to be BLACK";
        } else {
            case_2(node);
        }
    }
    void case_2(rb_node* node) {
//        std::cerr << "case_2; ";
        if (node->parent_->color_ == BLACK) {
            return;
        } else {
            case_3(node);
        }
    }
    void case_3(rb_node* node) {
//        std::cerr << "case_3; ";
        // already know that parent is RED
        if ((node->uncle() != NULL) && (node->uncle()->color_ == RED)) {
            node->parent_->color_ = BLACK;
            node->uncle()->color_ = BLACK;
            node->grandparent()->color_ = RED;
            case_1(node->grandparent());
            //            std::cerr << "set " << node->grandparent()->data_ << " to be RED; ";
        } else {
            case_4(node);
        }
    }
    void case_4(rb_node* node) {     // rotates if inner
//        std::cerr << "case_4, node = " << node->data_ << "\n";
        // we know that parent is RED and uncle is BLACK
        
        // check if node is on its parent's 'more', and that
        if ((node->parent_->more_ == node) && (node->parent_ == node->grandparent()->less_)) {
//            std::cerr << "l-rot about " << node->parent_->data_ << "; ";
            rotate_left(node->parent_);
            
            node = node->less_;
        } else if ((node->parent_->less_ == node) && (node->parent_ == node->grandparent()->more_)) {
//            std::cerr << "r-rot about " << node->parent_->data_ << "; ";
            rotate_right(node->parent_);
            
            node = node->more_;
        }
        case_5(node);
    }
    void case_5(rb_node* node) {
//        std::cerr << "case_5; ";
//        std::cerr << "set " << node->parent_->data_ << " to be BLACK, set ";
        node->parent_->color_ = BLACK;
//        std::cerr << node->parent_->parent_->data_ << " to be RED\n";
        node->grandparent()->color_ = RED;
        if (node->parent_->less_ == node) {
//            std::cerr << "r-rot about " << node->parent_->parent_->data_ <<"; ";
            rotate_right(node->grandparent());
        } else {
//            std::cerr << "l-rot about " << node->parent_->parent_->data_ <<"; ";
            rotate_left(node->grandparent());
        }
    }
    
    rb_node* max(rb_node* node) const {
        while (node->more_ != NULL) {
            node = node->more_;
        }
        return node;
    }
    rb_node* min(rb_node* node) const {
        while (node->less_ != NULL) {
            node = node->less_;
        }
        return node;
    }
    
    rb_node* find_node(const T& data) const {
        rb_node* cursor = root_;
        if (root_ != NULL) {
            while(true) {
                if (equal(data, cursor->data_)) {
                    break;
                } else if (less(data, cursor->data_)) {
                    if (cursor->less_ == NULL) {
                        cursor = NULL;
                        break;
                    } else {
                        cursor = cursor->less_;
                    }
                } else {
                    if (cursor->more_ == NULL) {
                        cursor = NULL;
                        break;
                    } else {
                        cursor = cursor->more_;
                    }
                }
            }
        }
        return cursor;
    }
    
    template <typename visitfunc>
    void previsit(rb_node* node, visitfunc func) {
        if (node == NULL) {
            return;
        } else {
            previsit(node->less_, func);
            func(node->data_);
            previsit(node->more_, func);
        }
    }
    template <typename visitfunc>
    void postvisit(rb_node* node, visitfunc func) {
        if (node == NULL) {
            return;
        } else {
            postvisit(node->more_, func);
            func(node->data_);
            postvisit(node->less_, func);
        }
    }
    
    template <typename funcfind>
    void previsit_find(rb_node* node, std::vector<T>& vect, funcfind equalfunc) const {
        if (node == NULL) {
            return;
        } else {
            previsit_find(node->less_, vect, equalfunc);
            if (equalfunc(node->data_)) {
                vect.push_back(node->data_);
            }
            previsit_find(node->more_, vect, equalfunc);
        }
    }
    template <typename funcfind>
    void postvisit_find(rb_node* node, std::vector<T>& vect, funcfind equalfunc) const {
        if (node == NULL) {
            return;
        } else {
            postvisit_find(node->more_, vect, equalfunc);
            if (equalfunc(node->data_)) {
                vect.push_back(node->data_);
            }
            postvisit_find(node->less_, vect, equalfunc);
        }
    }
    
    template <typename funcfind>
    void previsit_do(rb_node* node, funcfind equalfunc, funcdo dofunc) {
        if (node == NULL) {
            return;
        } else {
            previsit_do(node->less_, equalfunc);
            if (equalfunc(node->data_)) {
                dofunc(node->data_);
            }
            previsit_do(node->more_, equalfunc);
        }
    }
    template <typename funcfind>
    void postvisit_do(rb_node* node, funcfind equalfunc, funcdo dofunc) {
        if (node == NULL) {
            return;
        } else {
            postvisit_do(node->more_, equalfunc, dofunc);
            if (equalfunc(node->data_)) {
                dofunc(node->data_);
            }
            postvisit_do(node->less_, equalfunc, dofunc);
        }
    }
    
    void basic_print(std::ostream& out, rb_node* node, std::string delimiter) const {
        if (node == NULL) {
            return;
        }
        
        if (node->less_ == NULL && node->more_ == NULL) {
            out << node->data_ << delimiter;
            return;
        }
        
        if (node->less_ == NULL) {
            out << node->data_ << delimiter;
        } else {
            basic_print(out, node->less_, delimiter);
        }
        
        if (node->less_ != NULL && node->more_ != NULL) {
            out << node->data_ << delimiter;
        }
        
        if (node->more_ == NULL) {
            out << node->data_ << delimiter;
        } else {
            basic_print(out, node->more_, delimiter);
        }
    }
    
    void del_node(rb_node* node) {
        rb_node* temp;
        if (node->less_ != NULL && node->more_ != NULL) {
            // node has 2 leaves; time to fix that
            // (swap node with the greatest node less than it)
            temp = max(node->less_);
            swap_nodes(temp, node);
            
            // now node has at most 1 leaf (color balance at temp unchanged)
        }
        del_twig(node);
    }
    
    
    void del_twig(rb_node* node) {
        if (node->color_ == BLACK) {
            del1(node);
        }
        
        --size_;
        if (node->parent_ != NULL) {
            if (node == node->parent_->more_) {
                node->parent_->more_ = NULL;
            } else {
                node->parent_->less_ = NULL;
            }
        }
        delete node;
    }
    void del1(rb_node* n) {
        if (n->parent_ != NULL) {
            del2(n);
        }
    }
    void del2(rb_node* n) {
        // we know n must have a sibling, as n is black
        rb_node* s = n->sibling();
        
        if (s->color_ == RED) {
            n->parent_->color_ = RED;
            s->color_ = BLACK;
            if (n == n->parent_->less_) {
                rotate_left(n->parent_);
            } else {
                rotate_right(n->parent_);
            }
        }
        del3(n);
    }
    void del3(rb_node* n) {
        // n->parent_, S, and S's children are black.
        
        rb_node* s = n->sibling();
        
        if (n->parent_->color_ == BLACK &&
            s->color_ == BLACK &&
            s->less_color() == BLACK &&
            s->more_color() == BLACK) {
            s->color_ = RED;
            del1(n->parent_);
        } else {
            del4(n);
        }
    }
    void del4(rb_node* n) {
        // S and S's children are black, but n->parent_ is red.
        
        rb_node* s = n->sibling();
        
        if (n->parent_->color_ == BLACK &&
            s->color_ == BLACK &&
            s->less_color() == BLACK &&
            s->more_color() == BLACK)
        {
            s->color_ = RED;
            s->parent_->color_ = BLACK;
        } else {
            del5(n);
        }
    }
    void del5(rb_node* n) {
        rb_node* s = n->sibling();
        
        if (s->color_ == BLACK) {
            if (n == n->parent_->more_ &&
                s->more_color() == BLACK &&
                s->less_color() == RED)
            {
                s->color_ = RED;
                s->less_->color_ = BLACK;
                rotate_right(s);
            } else if (n == n->parent_->more_ &&
                s->less_color() == BLACK &&
                s->more_color() == RED)
            {
                s->color_ = RED;
                s->more_->color_ = BLACK;
                rotate_left(s);
            }
        }
        del6(n);
    }
    void del6(rb_node* n) {
        rb_node* s = n->sibling();
        
        s->color_ = n->parent_->color_;
        n->parent_->color_ = BLACK;
        
        if (n == n->parent_->less_) {
            s->more_->color_ = BLACK;
            rotate_left(n->parent_);
        } else {
            s->less_->color_ = BLACK;
            rotate_right(n->parent_);
        }
    }
    
    void swap_nodes(rb_node* n1, rb_node* n2) {
/*        // neither of these should be happening, buuuut
        if (n1 == NULL) {
            remove(n2);
            return;
        } else if (n2 == NULL) {
            remove(n1);
            return;
        }*/
        
        rb_node* temp = new rb_node(T());
        
        temp->color_ = n1->color_;
        temp->parent_ = n1->parent_;
        if (n1->parent_ != NULL) {
            if (n1->parent_->more_ == n1) {
            n1->parent_->more_ = n2;
            } else {
            n1->parent_->less_ = n2;
            }
        } else {
            root_ = n2;
        }
        
        temp->less_ = n1->less_;
        temp->more_ = n1->more_;
        if (temp->more_ != NULL) {
            temp->more_->parent_ = n2;
        }
        if (temp->less_ != NULL) {
            temp->less_->parent_ = n2;
        }
        
        
        n1->color_ = n2->color_;
        n1->parent_ = n2->parent_;
        if (n2->parent_ != NULL) {
            if (n2->parent_->more_ == n2) {
                n2->parent_->more_ = n1;
            } else {
                n2->parent_->less_ = n1;
            }
        } else {
            root_ = n1;
        }
        
        n1->more_ = n2->more_;
        n1->less_ = n2->less_;
        if (n1->more_ != NULL) {
            n1->more_->parent_ = n1;
        }
        if (n1->less_ != NULL) {
            n1->less_->parent_ = n1;
        }
        
        
        n2->color_ = temp->color_;
        n2->parent_ = temp->parent_;
        
        n2->more_ = temp->more_;
        n2->less_ = temp->less_;
        
        delete temp;
    }
    
    // use the visit method instead
    void print_ascending(std::ostream& out, rb_node* node, std::string delimiter) const;
    void print_descending(std::ostream& out, rb_node* node, std::string delimiter) const;
    
    void clear(rb_node* node) {
        if (node == NULL) {
            return;
        } else {
//            std::cerr << "clearing " << node->more_ << std::endl;
            clear(node->more_);
//            std::cerr << "clearing " << node->less_ << std::endl;
            clear(node->less_);
            delete node;
            --size_;
        }
    }
    
    
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
        
        color less_color() {
            if (less_ == NULL) {
                return BLACK;
            } else {
                return less_->color_;
            }
        }
        color more_color() {
            if (more_ == NULL) {
                return BLACK;
            } else {
                return more_->color_;
            }
        }
        
        void less(rb_node* child) {
            this->less_ = child;
            child->parent_ = this;
        }
        void more(rb_node* child) {
            this->more_ = child;
            child->parent_ = this;
        }
        
        rb_node* grandparent() const {
//            std::cerr << "calling 'grandparent' on " << data_ << ": ";
            if (parent_->parent_) {
//                std::cerr << "return " << parent_->parent_->data_ << "\n";
            } else {
//                std::cerr << "return NULL\n";
            }
            return parent_->parent_;
        }
        rb_node* sibling() const {
//            std::cerr << "calling 'sibling' on " << data_ << ": ";
            if (parent_->less_ == this) {
//                std::cerr << "return " << parent_->more_->data_ << "\n";
                return parent_->more_;
            } else {
//                std::cerr << "return " << parent_->less_->data_ << "\n";
                return parent_->less_;
            }
        }
        rb_node* uncle() const {
//            std::cerr << "calling 'uncle' on " << data_ << ": ";
            if (grandparent()->less_ == parent_) {
                if (parent_->parent_->more_) {
//                    std::cerr << "return " << parent_->parent_->more_->data_ << "\n";
                } else {
//                    std::cerr << "return NULL\n";
                }
                return grandparent()->more_;
            } else {
                if (parent_->parent_->less_) {
//                    std::cerr << "return " << parent_->parent_->less_->data_ << "\n";
                } else {
//                    std::cerr << "return NULL\n";
                }
                return grandparent()->less_;
            }
        }
    };
};

#endif
