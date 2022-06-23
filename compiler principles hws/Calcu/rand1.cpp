#include<iostream>
#include<string>
#include<sstream>
#include<stack>
#include<queue>
#include<map>
#include<fstream>
using namespace std;

int genNum() {
    return rand()%31;
}
//生成随机运算符
char genOp() { //随机生成运算符号
    char c;
    int q = rand() % 4;//生成一个0-3之间的随机数来代表运算符号
    switch (q) {
        case 0:
            c = '+';
            break;
        case 1:
            c = '-';
            break;
        case 2:
            c = '*';
            break;
        case 3:
            c = '/';
            break;
        default:
            printf("wrong");
    }
    return c;
}

//生成左括号
int GenerateLeftBracket()
{
    int result = 0;
    int whether_bracket = rand() % 7;
    if (whether_bracket ==1)
    {
        result = 1;
    }
    return result;
}

//生成右括号
int GenerateRightBracket()
{
    int result = 0;
    int whether_bracket = rand() % 7;
    if (whether_bracket <= 5) {
        result = 1;
    }
    return result;
}

//生成表达式
string genCal()
{
    string expression = "";
    string temp_string;
    int count_right_bracket = 0;
    int length = 3;
    int location_for_last_bracket = 0;
    length += 2*(rand() % 15);
    stringstream ss;
    double temp_num;
    int whether_int = 0;
    int whether_bracket = 0;
    for (int i = 0; i < length; i++)
    {
        whether_int = rand() % 5;
        if (i % 2 == 0) {
            //生成整数
            temp_num = genNum();
            ss << temp_num;
            ss >> temp_string;
            expression += temp_string;
            ss.clear();
            if (count_right_bracket&&i>=location_for_last_bracket+3) {
                if (GenerateRightBracket()) {
                    count_right_bracket -= 1;
                    expression += ')';
                }
            }
        }
        else {
            expression += genOp();
            whether_bracket= GenerateLeftBracket();
            if (whether_bracket == 1) {
                expression += '(';
                count_right_bracket += whether_bracket;
                location_for_last_bracket = i;
            }
        }
    }
    while ((count_right_bracket--) != 0) {
        expression += ')';
    }
    return expression;
}

int main() {
    for(int i=0; i<5; i++) {
        cout<<genCal()<<endl;
    }
    return 0;
}