//
//  myVector.h
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#ifndef myVector_h
#define myVector_h

#include <exception>
//declaratoin

namespace vec {
//iterator category
struct input_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};

template<typename _Tp>
class _vector_iterator
{
    //五个问题
    typedef     random_access_iterator_tag   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     unsigned int                 difference_type;
private:
    pointer node;
public:
    _vector_iterator(pointer x):node(x){}
    _vector_iterator():node(nullptr){}
    reference operator*(){return *this->node;}
    pointer operator->(){return &(operator*());}
};


template<typename _Tp>
class _vector_base
{
public:
    typedef      _Tp*               pointer;
    
    struct myVector_impl_data{
    public:
        pointer    start;
        pointer    end_of_storage;
        pointer    finish;
    };
    
    struct myVector_impl: public myVector_impl_data
    {
        //没有alloca所以无需ini，我也不知道要干嘛。。笑死
    };
    
protected:
    //composition
    myVector_impl _impl;
    

};

template<typename _Tp>
class vector:public _vector_base<_Tp>
{
public:
    typedef     _vector_base<_Tp>                _Base;
    typedef     _Tp                              Value_type;
    typedef     Value_type&                      reference;
    typedef     const Value_type&                const_reference;
    typedef     typename _Base::pointer          pointer;
    typedef     const Value_type*                const_iterator;
//    typedef     Value_type*                      iterator;
    typedef      _vector_iterator<_Tp>           iterator;
    typedef     unsigned int                     difference_type;
    using _Base::_impl;
public:
    explicit vector(const int& _size) {
        if (_size < 0)
            throw "size is nagative (invalid)";
        else if (_size == 0) {
            this->_impl.finish = this->_impl.start = new Value_type[1];
        }
        else{
            this->_impl.finish = this->_impl.start = new Value_type[_size];
            if (this->_impl.finish == nullptr)
                throw std::bad_alloc();
            this->_impl.end_of_storage = this->_impl.start + _size;
        }
    }
    long unsigned int size(){return this->_impl.finish - this->_impl.start;}
    long unsigned int capacity(){return this->_impl.end_of_storage - this->_impl.start;}
    iterator begin(){return (iterator)this->_impl.start;}
    iterator end(){return this->_impl.end();}
    reference front(){return *this->_impl.start;}
    reference back(){return *(this->_impl.finish-1);}
};

}

#endif /* myVector_h */
