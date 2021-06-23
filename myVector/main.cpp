//
//  main.cpp
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#include <iostream>
#include "myVector.h"
#include "my_stl_iterator.h"
#include "my_algorithm.h"
using namespace std;
struct fun1{
    void operator()(int& a){a = 3;}
};
struct fun2{
    void operator()(int& a){cout<<a<<'\t';}
};
int main(int argc, const char * argv[]) {
    
//    std::cout << "Hello, World!\n";
//    ptrdiff_t a;
    try {
        using namespace MyStl;
        vec::vector<int> mv(2);
        cout<<"size:"<<mv.size()<<endl;
        cout<<"capacity: "<<mv.capacity()<<endl;
        cout<<*mv.begin()<<endl;
        cout<<mv.front()<<endl;
        vec::vector<int>::iterator it;
        it = mv.begin();
        *it = 1;
        cout<<mv.front()<<endl;

        MyStl::for_each(mv.begin(), mv.end(), fun1());
        MyStl::for_each(mv.begin(), mv.end(), fun2());
    }
    catch (std::exception& e) {
        cout<<e.what();
    }
    catch (const char* e){
        cout<<e<<endl;
    }
    catch (...){
        cout<<"catch unexpected exception..."<<endl;
    }
    
    return 0;
}
