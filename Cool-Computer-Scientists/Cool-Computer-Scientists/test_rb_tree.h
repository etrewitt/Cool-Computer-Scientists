//
//  test_rb_tree.h
//  Cool-Computer-Scientists
//
//  Created by Erik Trewitt on 3/5/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//


// DEPRECATED


#ifndef Cool_Computer_Scientists_test_rb_tree_h
#define Cool_Computer_Scientists_test_rb_tree_h

#include <cstdlib>
#include <iostream>
#include <vector>

//template <typename T, typename lessthan, typename equalto>
template <typename T, typename lessthan>
//template <typename T>
class new_rb_tree {
private:
    enum color { RED, BLACK };
    
    // found at basically the bottom of the file
    struct rb_node;
    
    rb_node* root_;
    int size_;
    
    // these are to be implemented at a later date
    lessthan less;
    //    equalto equal;
public:
    new_rb_tree() {
        root_ = NULL;
        size_ = 0;
    }
    //    ~rb_tree();
    
    
    const T& root() const {
        return root_->data_;
    }
    const T& min() const;
    const T& max() const;
    int size() const {
        return size_;
    }
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
                /*
                 if (nu->data_ == cursor->data_) {
                 ++(cursor->data_);
                 break;
                 } else if (nu->data_ < cursor->data_) {*/

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
    void remove(const T& data) {
        rb_node* node = find_node(data);
        
        if (node == NULL) {
            return;
        } else {
            if (node->less_ == NULL && node->more_ == NULL) {
                if (node->parent_->less_ == node) {
                    node->parent_->less_ = NULL;
                } else {
                    node->parent_->more_ = NULL;
                }
            } else if (node->less_ == NULL) {
                if (node->parent_->less_ == node) {
                    node->parent_->less_ = node->more_;
                    node->more_->parent_ = node->parent_;
                } else {
                    node->parent_->more_ = node->more_;
                    node->more_->parent_ = node->parent_;
                }
            } else if (node->more_ == NULL) {
                if (node->parent_->less_ == node) {
                    node->parent_->less_ = node->less_;
                    node->less_->parent_ = node->parent_;
                } else {
                    node->parent_->more_ = node->less_;
                    node->less_->parent_ = node->parent_;
                }
            } else {
                
                // !!!               // this needs to move pointers around
                rb_node* moreptr = node->more_;
                rb_node* tempptr;
                moreptr->parent_ = node->parent_;
                
                moreptr->more(node);
                
                remove();
                return;
            }
        }
        
        delete node;
    }
    
    void print(std::ostream& out, std::string& delimiter, bool ascending=true) const;
    void basic_print(std::ostream& out, std::string delimiter="\n") const {
        out << size_ << " elements in the tree:\n";
        basic_print(out, root_, delimiter);
        out << std::flush;
    }
    
    void clear();
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
    
    
    rb_node* find_node(const T& data) const {
        rb_node* cursor = root_;
        if (root_ != NULL) {
            while(true) {
                if (data == cursor->data_) {
                    break;
//                } else if (data < cursor->data_) {
                } else if (less(data, cursor->data_)) {
                    if (cursor->less_ == NULL) {
                        cursor == NULL;
                        break;
                    } else {
                        cursor = cursor->less_;
                    }
                } else {
                    if (cursor->more_ == NULL) {
                        cursor == NULL;
                        break;
                    } else {
                        cursor = cursor->more_;
                    }
                }
            }
        }
        return cursor;
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
    
    void clear(rb_node* node);
    void print_ascending(std::ostream& out, rb_node* node, std::string delimiter) const;
    void print_descending(std::ostream& out, rb_node* node, std::string delimiter) const;
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
