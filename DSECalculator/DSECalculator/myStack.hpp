//
//  myStack.hpp
//  DSECalculator
//
//  Created by lyy on 2018/3/28.
//  Copyright © 2018年 lyy. All rights reserved.
//

#ifndef myStack_hpp
#define myStack_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

const int MaxStackSize = 50;
typedef double Stack_entry;
class MyStack{
private:
    Stack_entry entry[MaxStackSize];
    int count;
public:
    MyStack();
    bool empty();
    void push(Stack_entry item);
    void pop();
    Stack_entry top();
    
};
#endif /* myStack_hpp */
