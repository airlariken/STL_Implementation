//
//  main.cpp
//  myVector
//
//  Created by 陈梓玮 on 2021/6/23.
//

#include <iostream>
#include "myVector.h"
using namespace std;
int main(int argc, const char * argv[]) {
    
    std::cout << "Hello, World!\n";
    ptrdiff_t a;
    try {
        vec::vector<int> mv(2);
        cout<<"size:"<<mv.size()<<endl;
        cout<<"capacity: "<<mv.capacity()<<endl;
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
