//
//  myStack.cpp
//  DSECalculator
//
//  Created by lyy on 2018/3/28.
//  Copyright © 2018年 lyy. All rights reserved.
//

#include "myStack.hpp"
MyStack::MyStack(){
    count = 0;
}
bool MyStack::empty(){
    if(count == 0){
        return true;
    }
    return false;
}
void MyStack::push(Stack_entry item){
    if(count > MaxStackSize){
        cout << "stackoverflow";
    }else{
        entry[count++] = item;
    }
}
void MyStack::pop(){
    if(count <= 0){
        cout << "stackunderflow";
    }else{
        --count;
    }
}
Stack_entry MyStack::top(){
    Stack_entry item;
    if(count <= 0){
        cout << "stackunderflow";
        return 0;
    }else{
        item = entry[count-1];
    }
    return item;
}
