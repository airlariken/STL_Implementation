//
//  myVector.h
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#ifndef myVector_h
#define myVector_h
#include "my_stl_iterator.h"
#include <exception>
//declaratoin
namespace MyStl{


namespace vec {

template<typename _Tp>
class _vector_iterator
{
public:
    //五个问题
    typedef     random_access_iterator_tag   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     unsigned int                 difference_type;
    
    
    typedef _vector_iterator<_Tp>            __self;
private:
    pointer node;
public:
    _vector_iterator(pointer x):node(x){}
    _vector_iterator():node(nullptr){}
    reference operator*(){return *this->node;}
    pointer operator->(){return &(operator*());}
    bool operator!=(const __self& x){return node != x.node;}
    __self& operator++(){
        node = node+1;
        return *this;
    }
    __self operator +(const int& n) const{
        __self t = this->node + n;
        return t;}
    friend __self operator+(const int& n, const __self& it) {
        __self t = it.node + n;
        return t;
    }
    __self operator -(const int& n) const {
        __self t = this->node - n;
        return t;}
    difference_type operator -(const __self& it) const {
 
        return (difference_type)(this->node - it.node);
    }
//    friend __self operator+(const int& n, const __self& it)//1-it好像没啥意义啊
};

//类中嵌套类实现namespace的作用域效果
template<typename _Tp>
class _vector_base
{
public:
    typedef      _Tp*                pointer;
    
    struct myVector_impl_data{
    public:
        pointer    start;
        pointer    end_of_storage;
        pointer    finish;
    };
    
    struct myVector_impl: public myVector_impl_data         //inheritance
    {
        //没有alloca所以无需ini，我也不知道要干嘛。。笑死
    };
    
protected:
    //composition
    myVector_impl _impl;
    

};

template<typename _Tp>
class vector: public _vector_base<_Tp>
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
//            this->_impl.finish = this->_impl.start = new Value_type[1];
            _impl.end_of_storage = _impl.finish = _impl.start = nullptr;
        }
        else{
            this->_impl.finish = this->_impl.start = new Value_type[_size];
            if (this->_impl.finish == nullptr)
                throw std::bad_alloc();
            this->_impl.end_of_storage = this->_impl.start + _size;
        }
    }
    long unsigned int size()const {return this->_impl.finish - this->_impl.start;}
    long unsigned int capacity()const {return this->_impl.end_of_storage - this->_impl.start;}
    iterator begin()const {return (iterator)this->_impl.start;}
    iterator end()const {return this->_impl.finish;}
    reference front()const {return *this->_impl.start;}
    reference back()const {return *(this->_impl.finish-1);}
    
    void push_back(const Value_type& val){
        if (_impl.start == nullptr) {
            _impl.finish = _impl.start = new Value_type[1];
            _impl.end_of_storage = _impl.start + 1;
        }
        if (_impl.finish == _impl.end_of_storage) {
            long unsigned int original_size = _impl.end_of_storage-_impl.start;
            pointer t_start = new Value_type[original_size*2];
            if (t_start == nullptr) {
                throw std::bad_alloc();
            }
            std::copy(_impl.start, _impl.end_of_storage, t_start);
            delete [] _impl.start;
            _impl.start = t_start;
            _impl.finish = t_start + original_size;
            _impl.end_of_storage = t_start + original_size*2;
            
        }
        *_impl.finish = val;
        ++_impl.finish;
    }
    void erase(iterator it){
        std::copy(it+1, end(), it);
        --_impl.finish;
    }
    void clear(){
        delete [] _impl.start;
        _impl.end_of_storage = _impl.finish = _impl.start = nullptr;
    }
};
}
}

#endif /* myVector_h */
