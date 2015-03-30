//
//  main.cpp
//  synchronizedVar
//
//  Created by Yu Chen on 3/30/15.
//
//

#include <iostream>
#include <dsf/SynchronizedVar.h>

int main(int argc, const char * argv[]) {
    dsf::SynchronizedVar myInt(int(0));
    myInt = int(8); // value == NULL, next == 8
    myInt.synchronise(); // value == 8, next == 8
    std::cout << myInt.to<int>() << std::endl; // output 8
    myInt = int(9); // value == 8, next == 9
    std::cout << myInt.to<int>() << std::endl; // output 8
    myInt.synchronise(); // value == 9, next == 9
    std::cout << myInt.to<int>() << std::endl; // output 9
}