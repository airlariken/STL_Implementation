//
//  myDeque.h
//  myVector
//
//  Created by 陈梓玮 on 2021/7/3.
//

#ifndef myDeque_h
#define myDeque_h
#include "my_stl_iterator.h"
#include "myVector.h"
#define DEQUE_DEFAULT_BUFF_BYTES 512
#define DEQUE_ 8
namespace MyStl {

inline size_t __deque_buf_size(size_t buf_size, size_t ele_size) {
    //n表示bufSize的大小,sz表示变量类型的大小
    if (buf_size != 0)
    {
        return buf_size;
    }
    else
    {
        if (ele_size < DEQUE_DEFAULT_BUFF_BYTES)
            return size_t(DEQUE_DEFAULT_BUFF_BYTES / ele_size);
        else
            return size_t(1);
    }
}



template<typename _Tp, typename _Ref, typename _Ptr, size_t Bufsize= 0>//为什么要_Ref和_Ptr呢？因为如果需要const的话无需在写一个const iterator实现
class _Deque_iterator
{
public:
    //五个问题
    typedef     random_access_iterator_tag   iterator_category;
    typedef     _Tp                          value_type;
    typedef     _Ptr                         pointer;
    typedef     _Ref                         reference;
    typedef     unsigned int                 difference_type;
    
    typedef     pointer*                     map_pointer;
    typedef _Deque_iterator<_Tp, _Ref, _Ptr, Bufsize>                        __self;
    typedef _Deque_iterator<_Tp, const _Ref, const _Ptr, Bufsize>            __const_self;
public:
    pointer first;
    pointer cur;
    pointer last;
    map_pointer node;   //指回控制中心
    
public:
    static size_t __S_deque_buff_size(){return __deque_buf_size(Bufsize, sizeof(_Tp));}
    
    _Deque_iterator(map_pointer new_node):first(*new_node), cur(*new_node), last(*new_node+__S_deque_buff_size()), node(new_node){/*last += __S_deque_buff_size();*/}
    _Deque_iterator():first(nullptr), cur(nullptr), last(nullptr), node(nullptr){}
    _Deque_iterator(const __self& it) = default;//值拷贝即可
    void set_node(map_pointer new_node, size_t buff_size) {
        node = new_node;
        cur = first = *new_node;
        last = *new_node + buff_size;
    }

    //operator overide
    reference operator*()const{return *cur;}
    pointer operator->()const{return &(operator*());}

    __self& operator+=(const int& n){
//        __self temp(*this);
        long off_set = n + (this->cur - this->first);
        size_t buff_size = __S_deque_buff_size();
        if(off_set > 0 && off_set < buff_size) {
            this->cur += n;
            return *this;
        }
        
        int node_off_set =
        off_set > 0 ? off_set/(int)buff_size:
        -(-off_set-1)/(int)buff_size - 1;
//        map_pointer new_node = this->node;
        //判定是否越界?应该不需要
        
//        new_node += node_off_set / buff_size;
        this->set_node(this->node+node_off_set, buff_size);
        this->cur = this->first + node_off_set % buff_size;
        return *this;
    }
    __self& operator-=(const int& n) {
        return operator+=(-n);
    }
    __self operator+(const int& n) {
        __self temp(*this);
        return temp+=n;
    }
    __self operator-(const int& n) {
        __self temp(*this);
        return temp-=n;
    }
    
    __self& operator++() {
        if (this->last -1 != this->cur) {
            this->cur += 1;
            return *this;
        }
        
        this->set_node(this->node+1, __S_deque_buff_size());
        return *this;
    }
    
    __self operator++(int n)const{
        __self temp = this;
        ++*this;
        return temp;
    }
    __self& operator--(){
        if (this->first != this->cur) {
            this->cur = this->cur - 1;
            return *this;
        }
        this->node = this->node-1;
        this->set_node(this->node, __S_deque_buff_size());
        this->cur = this->last - 1;
        return *this;
    }
    __self operator--(int n) const{
        __self temp = this;
        --*this;
        return temp;
    }
    __self& operator[](int n) {
        this->cur += n;
        return *this;
    }
    difference_type operator-(const __self& it) const {//it必须在*this之后
        return (difference_type)(this->cur - this->first) + (it.last - it.cur) + (this->node - it.node - 1)*__S_deque_buff_size();
    }
    bool operator==(const __self& it) {return this->cur == it.cur;}
    bool operator!=(const __self& it) {return this->cur != it.cur;}
    bool operator>=(const __self& it) {return this->cur >= it.cur;}
    bool operator<=(const __self& it) {return this->cur <= it.cur;}
    bool operator<(const __self& it) {return this->cur < it.cur;}
    bool operator>(const __self& it) {return this->cur > it.cur;}
    
    
    
    
};
template<typename _Tp, size_t BufSiz = 0>
class _Deque_base
{
public:
    typedef     _Tp                          value_type;
    typedef     _Tp*                         pointer;
    typedef     _Tp&                         reference;
    typedef     unsigned int                 difference_type;
    typedef     _Deque_iterator<_Tp, _Tp&, _Tp*, BufSiz>                    iterator;
    typedef     _Deque_iterator<_Tp, const _Tp&, const _Tp*, BufSiz>        const_iterator;
    typedef     pointer*                     map_pointer;
    
    
protected:

    map_pointer map;
    iterator start;
    iterator finish;
    size_t map_size;
    
protected:
    //ctor
    _Deque_base():start(),finish(),map_size(0){initialize_map(0);}
    _Deque_base(size_t num_elements):start(), finish() {
        initialize_map(num_elements);
    }
    
    void initialize_map(size_t num_elements){
        size_t buff_size = iterator::__S_deque_buff_size();
        if (num_elements == 0) {
            map = new pointer[10];
            this->start.set_node(map + (difference_type)map_size / 2, buff_size);
            this->finish = start;
            return ;
        }
//        size_t buff_size = BufSiz == 0 ? DEQUE_DEFAULT_BUFF_SIZE : BufSiz;
        
        map_size = num_elements / buff_size;
        map_size = map_size == 0 ? 1 : map_size * 2;            //未指定数组大小
        map = new pointer[map_size];
        
        for (int i = 0; i < map_size; ++i)
            map[i] = new value_type[buff_size];
        
        
        size_t start_first_offset_elements = (map_size * buff_size - num_elements) / 2;//从start.last开始向左的偏移量
        difference_type offset = (difference_type) start_first_offset_elements / buff_size;
        //确定start位置以及start.cur的位置
        this->start.set_node(map + offset, buff_size);
//        std::cout<<map + offset<<std::endl;
//        std::cout<<sizeof(map)<<std::endl;
        this->start.cur = this->start.first + (start_first_offset_elements % buff_size);
        
        //确定finish的位置以及finish.cur的位置
//        std::cout<<map + offset + num_elements/buff_size - 1<<std::endl;
        this->finish.set_node(map + offset + num_elements/buff_size, buff_size);
        size_t finish_last_offset_elements = (map_size * buff_size - num_elements) - start_first_offset_elements;//从start.last开始向左的偏移量
        this->finish.cur = this->finish.last - (finish_last_offset_elements % buff_size) - 1;
    }

};


template<typename _Tp, size_t BufSiz = 0>
class deque : protected _Deque_base<_Tp, BufSiz>
{
private:
    typedef             _Deque_base< _Tp, BufSiz>                   base;
public:
    typedef             _Tp                                         value_type;
    typedef             _Tp*                                        pointer;
    typedef             _Tp&                                        reference;
    typedef             const _Tp&                                  const_reference;
    typedef             unsigned int                                difference_type;
    typedef  typename   _Deque_base< _Tp, BufSiz>::iterator         iterator;
    typedef  typename   _Deque_base< _Tp, BufSiz>::const_iterator   const_iterator;
    
    typedef  typename   base::map_pointer                           map_pointer;
public:
    //ctor
    deque() = default;
    deque(size_t size):_Deque_base<_Tp, BufSiz>(size){}
    //operator override
    const_reference operator[](const int& n) const {//有必要const吗
        iterator it = this->start;
        return *it[n];
    }
    reference operator[](const int& n)  {//有必要const吗
        iterator it = this->start;
        return *it[n];
    }
    
    //functions
    void push_back(const value_type& n) {
        if(this->finish.last-1 != this->finish.cur) {
            *(this->finish.cur) = n;
            ++(this->finish.cur);
        }
        else {
            if (this->finish.cur == iterator(this->map + this->map_size - 1).last-1) {
                //扩容
                push_back_aux(n);
            }
            else {
                map_pointer new_node = this->finish.node + 1;
                if (*new_node == nullptr)
                    *new_node = new value_type[iterator::__S_deque_buff_size()];
                *(this->finish.cur) = n;
                this->finish.set_node(new_node, iterator::__S_deque_buff_size());
            }
        }
    }
    void push_front(const value_type& n) {
        if(this->start.first != this->start.cur) {
            --(this->start.cur);
            *(this->start.cur) = n;
        }
        else {
            if (this->start.cur == iterator(this->map).first) {
                //扩容
                push_front_aux(n);
            }
            else {
                map_pointer new_node = this->start.node - 1;
                if (*new_node == nullptr)
                    *new_node = new value_type[iterator::__S_deque_buff_size()];
                
                this->start.set_node(new_node, iterator::__S_deque_buff_size());
                this->start.cur = this->start.last-1;
                *(this->start.cur) = n;
            }
        }
    }
    void push_front_aux(const value_type& n) {//扩容翻倍
        reallocate();
        //开一块新空间给finish作为超尾位置
        *(this->start.node-1) = new value_type[iterator::__S_deque_buff_size()];
        //赋值并且将finish挪到超尾位置
        this->start.set_node(this->start.node - 1, iterator::__S_deque_buff_size());
        this->start.cur = this->start.last-1;
        *(this->start.cur) = n;
    }
    void push_back_aux(const value_type& n) {//扩容翻倍
        reallocate();
        //开一块新空间给finish作为超尾位置
        *(this->finish.node+1) = new value_type[iterator::__S_deque_buff_size()];
        //赋值并且将finish挪到超尾位置
        *(this->finish.cur) = n;
        this->finish.set_node(this->finish.node + 1, iterator::__S_deque_buff_size());
    }
    void reallocate() {
        //记录两个偏移值
        size_t start_offset = this->start.node - this->map;
        size_t finish_offset = this->finish.node - this->map;
        size_t node_cnt = finish_offset - start_offset;
        
        map_pointer new_map = new pointer[this->map_size*2];//开辟一个更大的数组map， 两倍扩容
        size_t new_map_start_offset = (this->map_size*2 - node_cnt) / 2;
        for (int i = 0; i < this->map_size*2; ++i)  new_map[i] = nullptr;       //ini
        std::copy(this->map+start_offset, this->map+finish_offset+1, new_map+new_map_start_offset);                //copy
        //更新map和mapsize
        this->map_size *= 2;
        this->map = new_map;
        //记录偏移值
        this->start.node = this->map + new_map_start_offset;
        this->finish.node = this->start.node + node_cnt;
    }
public:
    iterator begin() const{
        return this->start;
    }
    iterator end() const{
        return this->finish;
    }
    difference_type size() const{return this->finish - this->start;}
    difference_type capacity() const{return this->map_size * iterator::__S_deque_buff_size();}
    
};




}




#endif /* myDeque_h */
