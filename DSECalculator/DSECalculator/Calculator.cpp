//
//  Calculator.cpp
//  DSECalculator
//
//  Created by lyy on 2018/3/28.
//  Copyright © 2018年 lyy. All rights reserved.
//

#include "Calculator.hpp"
Caculator::Caculator(){
    cout << "Please enter an expression: ";
    cin >> expression;
    cout << "=====> ";
    //cout << expression;
}
Caculator::Caculator(char* expr){
    this->expression = expr;
    cout << expression << endl;
    cout << "=====> ";
}
bool Caculator::isNum(char item){
    if(item >= '0' && item <= '9'){
        return true;
    }
    return false;
}
bool Caculator::isOper(char item){
    if(item == '+' || item == '-' || item == '*' || item == '/' || item == '(' || item == ')' || item == '#'){
        return true;
    }
    return false;
}
char* Caculator::preTreat(){
    char *tempExpression = new char[50];
    char *tempExpression2 = new char[50];
    int j = 0;
    for(int i = 0; i <strlen(expression); i++){
        if(isOper(expression[i]) || isNum(expression[i]) || expression[i] == '.' || expression[i] == '#'){
            tempExpression[j++] = expression[i];
        }
    }
    j = 0;
    for(int i = 0; i < strlen(tempExpression); i++){
        if(tempExpression[i] == '.' && tempExpression[i+1] == '.'){
        }else{
            tempExpression2[j++] = tempExpression[i];
        }
    }
//    cout << tempExpression << endl << tempExpression2 << endl;
    return tempExpression2;
}
bool Caculator::calculator(){
    char *newExpression = new char[50];
    newExpression = preTreat();
    operators.push(6);
    if(!check(newExpression)){
        return false;
    }
    for(int i = 0; i < strlen(newExpression); i++){
        if(isOper(newExpression[i])){
            if(!operatorOperation(newExpression[i])){
                return false;
            }
        } else if (isNum(newExpression[i])){
            while(isNum(newExpression[i])){
                if(!isNum(newExpression[i+1]) && newExpression[i+1] != '.'){
                    integerNumber = integerNumber * 10 + (int)newExpression[i] - 48;
                    num = integerNumber + decimalNumber;
                    numbers.push(num);
                    cout << numbers.top() << " ";
                    num = integerNumber = decimalNumber = 0;
                } else {
                    integerNumber = integerNumber * 10 + (int)newExpression[i] - 48;
                    if(newExpression[i+1] == '.'){
                        i += 2;
                        int count = 1;
                        while(isNum(newExpression[i])){
                            decimalNumber += ((int)newExpression[i] - 48) * pow(10, -count);
                            count+=1;
                            i++;
                        }
                        count = 1;
                        num = integerNumber + decimalNumber;
                        numbers.push(num);
                        cout << numbers.top() << " ";
                        i--;
                        num = integerNumber = decimalNumber = 0;
                    }
                }
                i++;
            }
            i--;
        }
    }
    cout << endl <<  "The result is " ;
    printf("%.5lf", numbers.top());
    cout << endl;
    return true;
}
bool Caculator::operatorOperation(char item){
    int col = 0;
    int row = 0;
    for(int i = 0; i < strlen(opers); i++){
        if(opers[i] == item){
            col = i;
            break;
        }
    }
    for(int i = 0; i < strlen(opers); i++){
        if(opers[i] == operDecode(operators.top())){
            row = i;
            break;
        }
    }
    if (priority[row][col] == 1){
        operators.push(operEncode(item));
    } else if(priority[row][col] == 0){
        if(item != ')' || item != '('){
            cout << operDecode(operators.top()) << " ";
        }
        double firNum, secNum;
        secNum = numbers.top();
        numbers.pop();
        firNum = numbers.top();
        numbers.pop();
        if(!compute(firNum, secNum, operDecode(operators.top()))){
            return false;
        }
        operators.pop();
        operatorOperation(item);
    }else if (priority[row][col] == -1){
        operators.pop();
    }else if (priority[row][col] == -2){
        return false;
    }else if (priority[row][col] == -3){
        
    }
    
    return true;
}
int Caculator::operEncode(char item){
    int code = 0;
    switch (item) {
        case '+':
            code = 0;
            break;
        case '-':
            code = 1;
            break;
        case '*':
            code = 2;
            break;
        case '/':
            code = 3;
            break;
        case '(':
            code = 4;
            break;
        case ')':
            code = 5;
            break;
        case '#':
            code = 6;
            break;
    }
    return code;
}
char Caculator::operDecode(int item){
    char code = ' ';
    switch (item) {
        case 0:
            code = '+';
            break;
        case 1:
            code = '-';
            break;
        case 2:
            code = '*';
            break;
        case 3:
            code = '/';
            break;
        case 4:
            code = '(';
            break;
        case 5:
            code = ')';
            break;
        case 6:
            code = '#';
            break;
    }
    return code;
}
bool Caculator::compute(double sNum, double fNum, char oper){
    switch(oper) {
        case '+':
            result = (sNum * 1.0 + fNum * 1.0) *1.0;
            numbers.push(result);
            break;
        case '-':
            result = (sNum * 1.0 - fNum * 1.0) * 1.0;
            numbers.push(result);
            break;
        case '*':
            result = (sNum * 1.0 * fNum * 1.0) * 1.0;
            numbers.push(result);
            break;
        case '/':
            if(fNum == 0) {
                return false;
            }
            result = (sNum * 1.0) / (fNum *1.0 );
            numbers.push(result);
            break;
    }
    return true;
}
bool Caculator::check(char *expr){
    if(expr[strlen(expr) - 1] != '#'){
        cout << "Unexpected ending" << endl;
        return false;
    }
    int bracketCount = 0;
    for(int i = 0; i < strlen(expr); i++){
        if(expr[i] == '(' && expr[i+1] != ')'){
            bracketCount += 1;
        }else if (expr[i] == ')' && expr[i+1] != '('){
            bracketCount -= 1;
        }
        if(bracketCount < 0 || (expr[i] == '(' && expr[i+1] == ')') || (expr[i] == ')' && expr[i+1] == '(')){
            cout << "Wrong bracket count" << endl;
            return false;
        }
    }
    if(bracketCount != 0){
        cout << "Wrong bracket count" << endl;
        return false;
    }
    for(int i = 0; i < strlen(expr); i++){
        if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
            if(isNum(expr[i-1]) || expr[i-1] == ')'){
                if(isNum(expr[i+1]) || expr[i+1] == '('){
                }else{
                    cout << "Error";
                    return false;
                }
            }else{
                cout << "Error";
                return false;
            }
        }
    }
    return true;
}
