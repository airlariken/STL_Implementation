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
#include "myDeque.h"
using namespace std;

struct A{
    char b = 'c';
    double c = 2333;
    int d = 2;
};
int main(int argc, const char * argv[]) {
//    A a;
//    cout<<( (A*)((char*)&a.c-(char*)&(((A*)0)->c)) )->d<<endl;
    
//    std::cout << "Hello, World!\n";
//    ptrdiff_t a;

//    cout<<sizeof(void*)<<endl;
    try {
        using namespace MyStl;
        vec::vector<int> mv(2);
        
        
        deque<int, 2> m_deq(5);
        int cnt = 0;
        for (auto it1 = m_deq.begin(); it1 != m_deq.end(); ++it1) {
            *it1 = cnt++;
        }
        for (auto it1 = m_deq.begin(); it1 != m_deq.end(); ++it1) {
            cout<<*it1<<'\t';
        }
        for (int i = 0; i < 10; ++i) {
            m_deq.push_back(i*10);
            for (auto it1 = m_deq.begin(); it1 != m_deq.end(); ++it1) {
                cout<<*it1<<'\t';
            }
            cout<<endl;
//            cout<<*(m_deq.end()-1)<<'\t';
        }
        for (auto it1 = m_deq.begin(); it1 != m_deq.end(); ++it1) {
            cout<<*it1<<'\t';
        }
//        cout<<*(m_deq.begin()+5)<<endl;
        cout<<"size:"<<mv.size()<<endl;
        cout<<"capacity: "<<mv.capacity()<<endl;
        
        vec::vector<int>::iterator my_it;


//        std::__void_t<vec::vector<int>::iterator::difference_type>::type* a;

        auto l_f2 = [](int& n){n*3;};
        auto l_f1 = [](const int& n){cout<<n<<'\t';};
//        MyStl::for_each(mv.begin(), mv.end(), fun1());
        for (int i = 0; i < 50; ++i) {
            MyStl::for_each(mv.begin(), mv.end(), l_f2);  cout<<endl;
//            mv.erase(mv.end()-1);
//            MyStl::for_each(mv.begin(), mv.end(), fun2());  cout<<endl;
            mv.push_back(11);
//            MyStl::for_each(mv.begin(), mv.end(), fun2());  cout<<endl;
//            cout<<"size:"<<mv.size()<<endl;
//            cout<<"capacity: "<<mv.capacity()<<endl;
        }
        cout<<"capacity: "<<mv.capacity()<<endl;
//        mv.clear();
        cout<<"capacity: "<<mv.capacity()<<endl;
//        ::sort(mv.begin(), mv.end());  cout<<endl;
        
        typedef IteratorTraits<int*>::value_type i;
        i a = 1;

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
    cout<<"finish"<<endl;
    return 0;
}
