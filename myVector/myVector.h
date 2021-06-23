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
template<typename _Tp>
class myVector_impl;

template<typename _Tp>
class vector
{
    typedef     myVector_impl<_Tp> _Base;
public:
    typedef     _Tp                Value_type;
    typedef     typename _Base::reference        reference;
    typedef     const Value_type&  const_reference;
    typedef     Value_type*        pointer;
    typedef     const Value_type*  const_iterator;
    typedef     Value_type*        iterator;
    typedef     unsigned int       difference_type;
protected:
    //bridge design mode(handle_body)
    myVector_impl<_Tp> _impl;
public:
    explicit vector(const int& _size):_impl(_size){}
    vector() = delete;
    unsigned int size(){return _impl.size();}
    unsigned int capacity(){return _impl.capacity();}
    iterator begin(){return _impl.begin();}
    iterator end(){return _impl.end();}
    reference front(){return _impl.fornt();}
    reference back(){return _impl.back();}
};

template <typename _Tp>
class myVector_impl_data{
public:
    typedef      _Tp*           pointer;
    pointer    start;
    pointer    end_of_storage;
    pointer    finish;
};
template<typename _Tp>
class myVector_impl: public myVector_impl_data<_Tp>
{
    
public:
    typedef     _Tp                Value_type;
    typedef     Value_type&        reference;
    typedef     const Value_type&  const_reference;
    typedef  typename   myVector_impl_data<_Tp>::pointer    pointer;
    typedef     const Value_type*  const_iterator;
    typedef     Value_type*        iterator;
    typedef     unsigned int       difference_type;
    
    
public:
    //constructor
    explicit myVector_impl(const int &_size);
    //destructor
    ~myVector_impl() {
        if (this->start != nullptr) {
            delete []this->start;
        }
    }
    
    
    unsigned int size(){return (unsigned int)(this->finish - this->start);}
    unsigned int capacity(){return (unsigned int)(this->end_of_storage - this->start);}
    iterator begin(){return this->start;}
    iterator end(){return this->finish;}
    reference front(){return *this->start;}
    reference back(){return *(this->finish-1);}
};
template <typename _Tp>
myVector_impl<_Tp>::myVector_impl(const int &_size)
{
    if (_size < 0)
        throw "size is nagative (invalid)";
    else if (_size == 0) {
        this->finish = this->start = new Value_type[1];
    }
    else{
        this->finish = this->start = new Value_type[_size];
        if (this->finish == nullptr)
            throw std::bad_alloc();
        this->end_of_storage = this->start + _size;
    }
}
}

#endif /* myVector_h */
