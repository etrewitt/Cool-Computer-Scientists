//
//  oldremoval.h
//  Cool-Computer-Scientists
//
//  Created by Erik Trewitt on 3/15/15.
//  Copyright (c) 2015 etrewitt. All rights reserved.
//

#ifndef __Cool_Computer_Scientists__oldremoval__
#define __Cool_Computer_Scientists__oldremoval__

void remove(rb_node* node) {
    rem_case1(node);
    delete node;
    --size_;
}

void rem_case1(rb_node* node) {
    rb_node* temp;
    if (node->less_ != NULL && node->more_ != NULL) {
        // node has 2 leaves; time to fix that
        // (swap node with the greatest node less than it)
        temp = max(node->less_);
        swap_nodes(temp, node);
        
        // now node has at most 1 leaf (color balance at temp unchanged)
    }
    
    // node has 1 or fewer leaves, and must be deleted
    rem_case2(node);
}

// we know that node has at most one leaf
// that the child is on the 'less_' side
// and that node is on its parent's 'more_' side
void rem_case2(rb_node* node) {
    // if node is RED, then its child leaf must be BLACK - and since it only has one child, its child is NULL
    if (node->color_ == RED) {
        node->parent_->more_ = NULL;
        //            delete node;
        return;
    } else {
        // we know node is BLACK, and has at most one child
        rem_case3(node);
    }
    
}

// we know node is BLACK, and has at most one child leaf, which is on the 'less_' side
void rem_case3(rb_node* node) {
    if (node->less_ != NULL) {
        // if it has a child, then the child MUST be RED
        node->parent_->more_ = node->less_;
        node->less_->parent_ = node->parent_;
        //            delete node;
        return;
    } else {
        // we know that node is both BLACK and childless; this is harder
        // (because node is BLACK, its sibling tree must have BLACK as well)
        rem_case4(node);
    }
}

// node is BLACK and childless; node's sibling tree has at most depth 2 and has one level of BLACK
// there are two cases:
//// 1) the sibling is RED (and so parent must be BLACK), and has two BLACK children
//// 2) the sibling is BLACK, and has RED children (if any)
////// 2.1) the parent is BLACK
////// 2.2) the parent is RED
//
// 1) is solved by making sibling BLACK, rotating about the parent, then making the new sibling RED
// 2) is harder
void rem_case4(rb_node* node) {
    if (node->sibling()->color_ == RED) {
        // check for 1)
        node->sibling()->color_ = BLACK;
        rotate_right(node->parent_);
        node->sibling()->color_ = RED;
    } else {
        // so 2) is the case
        rem_case5(node);
    }
}

void rem_case5(rb_node* node) {
    if (node->parent_->color_ == BLACK) {
        // 2.1) is the case
        rem_case5_1(node);
    } else {
        // 2.2) is the case
        rem_case5_2(node);
    }
}

// 2.1a) sibling has 2 RED child nodes
// 2.1b) sibling has 1 RED child node on the less_ side
// 2.1c) sibling has 1 RED child node on the more_ side
// 2.1d) sibling has 0 children

// 2.1a) is solved by rotating right about the parent, and making the parent's new sibling BLACK
// 2.1b) is solved by rotating right about the parent, and making the parent's new sibling BLACK
// 2.1c) is solved by rotating left about the sibling, right about the parent, and making the grandparent BLACK
// 2.1d) is solved by making the sibling RED and calling rem_case1() on the parent
void rem_case5_1(rb_node* node) {
    if (node->sibling()->less_ != NULL && node->sibling()->more_ != NULL) {
        // 2.1a)
        rotate_right(node->parent_);
        node->parent_->sibling()->color_ = BLACK;
    } else if (node->sibling()->less_ != NULL) {
        // 2.1b)
        rotate_right(node->parent_);
        node->parent_->sibling()->color_ = BLACK;
    } else if (node->sibling()->more_ != NULL) {
        // 2.1c)
        rotate_left(node->sibling());
        rotate_right(node->parent_);
        node->grandparent()->color_ = BLACK;
    } else {
        // 2.1d)
        node->sibling()->color_ = RED;
        rem_case5_1(node->parent_);
    }
}

// 2.2a) sibling has 2 RED child nodes
// 2.2b) sibling has 1 RED child node on the less_ side
// 2.2c) sibling has 1 RED child node on the more_ side
// 2.2d) sibling has 0 children

// 2.2a) is solved by rotating right about the parent, making the parent BLACK, the uncle BLACK, and the grandparent RED
// 2.2b) is solved by rotating right about the parent, making the parent BLACK, the uncle BLACK, and the grandparent RED
// 2.2c) is solved by rotating left about the sibling, right about the parent, and making the parent BLACK
// 2.2d) is solved by making the parent BLACK and the sibling RED
void rem_case5_2(rb_node* node) {
    if (node->sibling()->less_ != NULL && node->sibling()->more_ != NULL) {
        // 2.2a)
        rotate_right(node->parent_);
        node->parent_->color_ = BLACK;
        node->uncle()->color_ = BLACK;
        node->grandparent()->color_ = RED;
    } else if (node->sibling()->less_ != NULL) {
        // 2.2b)
        rotate_right(node->parent_);
        node->parent_->color_ = BLACK;
        node->uncle()->color_ = BLACK;
        node->grandparent()->color_ = RED;
    } else if (node->sibling()->more_ != NULL) {
        // 2.2c)
        rotate_left(node->sibling());
        rotate_right(node->parent_);
        node->parent_->color_ = BLACK;
    } else {
        // 2.2d)
        node->parent_->color_ = BLACK;
        node->sibling()->color_ = RED;
    }
}

#endif /* defined(__Cool_Computer_Scientists__oldremoval__) */
