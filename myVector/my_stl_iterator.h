//
//  my_stl_iterator.h
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#ifndef my_stl_iterator_h
#define my_stl_iterator_h

//iterator category
struct input_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};

namespace MyStl{
    
}
#endif /* my_stl_iterator_h */
