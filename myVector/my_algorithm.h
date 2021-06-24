//
//  my_algorithm.h
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#ifndef my_algorithm_h
#define my_algorithm_h

namespace MyStl {

//template<typename _RandomAccessIterator, typename functor>
template<typename _InputIterator, typename functor>
_InputIterator inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 for_each(_InputIterator first, _InputIterator end, functor __f)
{
    //可以通过以下方式得到迭代器的5个问题的答案
//    typedef typename _InputIterator::value_type  value_type;
    
    for (; first != end; ++first) {
        __f(*first);
    }
    return first;
}
    
}
#endif /* my_algorithm_h */
