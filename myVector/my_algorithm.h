//
//  my_algorithm.h
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#ifndef my_algorithm_h
#define my_algorithm_h

namespace MyStl {

template<typename _RandomAccessIterator, typename functor>
_RandomAccessIterator inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17 for_each(_RandomAccessIterator first, _RandomAccessIterator end, functor __f)
{
    typedef typename _RandomAccessIterator::value_type   Value_type;
    for (; first != end; ++first) {
        __f(*first);
    }
    return first;
}
    
}
#endif /* my_algorithm_h */
