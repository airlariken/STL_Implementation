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
struct output_iterator_tag{}; 
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};


namespace MyStl{
template<typename Category, typename _Tp, typename Distance = ptrdiff_t>
class Iterator{
    //五个问题
    typedef     Category   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     Distance                difference_type;
    
    
//    typedef Iterator<Category, _Tp, Distance>            __self;

};

template<typename  _Iterator>
//自定义类的迭代器应该自己能回答5个问题
class IteratorTraits{
public:
    typedef typename _Iterator::value_type                  value_type;
    typedef typename _Iterator::iterator_category           iterator_category;
    typedef typename _Iterator::reference                   reference;
    typedef typename _Iterator::pointer                     pointer;
    typedef typename _Iterator::difference_type             difference_type;
};

template<typename _Tp>
class IteratorTraits<_Tp*>  //native pointer
{
public:
    typedef     random_access_iterator_tag   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     unsigned int                 difference_type;
};

template<typename _Tp>
class IteratorTraits<const _Tp*>  //native pointer
{
    typedef     random_access_iterator_tag   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     unsigned int                 difference_type;
};
}
#endif /* my_stl_iterator_h */
