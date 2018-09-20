//
//  Calculator.hpp
//  DSECalculator
//
//  Created by lyy on 2018/3/28.
//  Copyright © 2018年 lyy. All rights reserved.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <stdio.h>
#include <math.h>
#include "myStack.hpp"
using namespace std;
class Caculator{
public:
    Caculator();
    Caculator(char* expr);
    bool isNum(char item);
    bool isOper(char item);
    char *preTreat();
    bool calculator();
    bool check(char *expr);
    bool operatorOperation(char item);
    int operEncode(char item);
    char operDecode(int item);
    bool compute(double firstNum, double secNum, char oper);
private:
    char *expression = new char[50];
    char opers[7] = {'+', '-', '*', '/', '(', ')', '#'};
    int priority[7][7] = {{0, 0, 1, 1, 1, 0, 0},
                          {0, 0, 1, 1, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0},
                          {1, 1, 1 ,1, 1, -1, -2},
                          {0, 0, 0, 0, -2, 0, 0},
                          {1, 1, 1, 1, 1, -2, -3}};
    double integerNumber = 0;
    double decimalNumber = 0;
    double num = 0;
    double result = 0;
    MyStack numbers;
    MyStack operators;
};
#endif /* Calculator_hpp */
