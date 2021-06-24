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
//struct fun1{
//    void operator()(int& a){a *= 3;}
//};
//struct fun2{
//    void operator()(int& a){cout<<a<<'\t';}
//};
int main(int argc, const char * argv[]) {
    
//    std::cout << "Hello, World!\n";
//    ptrdiff_t a;
    try {
        using namespace MyStl;
        vec::vector<int> mv(2);
        mv.push_back(1);
        mv.push_back(3);
        mv.push_back(5);
        mv.push_back(7);
        mv.push_back(11);
        
        cout<<"size:"<<mv.size()<<endl;
        cout<<"capacity: "<<mv.capacity()<<endl;
        
        vec::vector<int>::iterator my_it;
        my_it = mv.begin();
        auto my_it_end = mv.end();
        cout<<"iterator distance :"<<mv.end()-mv.begin()<<endl;
//        cout<<*my_it;
//        auto it = 9 + my_it;
//        auto it = my_it + 9;
//        *my_it = 233;
//        cout<<*my_it;
//        cout<<*mv.begin()<<endl;
//        cout<<mv.back()<<endl;
//        vec::vector<int>::iterator it;
//        it = mv.begin();
//        *it = 1;
//        cout<<mv.front()<<endl;

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
