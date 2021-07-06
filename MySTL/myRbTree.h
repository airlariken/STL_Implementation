//
//  myRbTree.h
//  MySTL
//
//  Created by 陈梓玮 on 2021/7/6.
//

#ifndef myRbTree_h
#define myRbTree_h

namespace MyStl {

enum _Rb_tree_color{Red = false, Black = true};

struct _Rb_tree_node_base
{

    typedef         _Rb_tree_node_base*             base_pointer;
    typedef         const _Rb_tree_node_base*       const_base_pointer;
    _Rb_tree_color color;
    base_pointer _Rb_tree_parent;
    base_pointer _Rb_tree_left;
    base_pointer _Rb_tree_right;
};

class RbTree_iterator
{
};
}

#endif /* myRbTree_h */
