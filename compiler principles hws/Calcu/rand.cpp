#include <iostream>
#include <fstream>
using namespace std;
int genNum() {
    return rand()%31;
}
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

void genCal1() { //随机生成，两个运算符，不带括号
    ofstream fout;
    fout.open("C:\\Users\\99288\\Desktop\\Calcu\\file.txt", ios::app);
    fout<<genNum()<<genOp()<<genNum()<<genOp()<<genNum()<<endl;
    fout.close();
}

void genCal2() { //随机生成，三个运算符，带一个括号
    ofstream fout;
    fout.open("C:\\Users\\99288\\Desktop\\Calcu\\file.txt", ios::app);
    int calType = rand()%5;
    switch (calType) {
        case 0:
            fout<<'('<<genNum()<<genOp()<<genNum()<<')'<<genOp()<<genNum()<<genOp()<<genNum()<<endl;
            break;
        case 1: //(1+2+3)+4类型
            fout<<'('<<genNum()<<genOp()<<genNum()<<genOp()<<genNum()<<')'<<genOp()<<genNum()<<endl;
            break;
        case 2: //1+(2+3)+4类型
            fout<<genNum()<<genOp()<<'('<<genNum()<<genOp()<<genNum()<<')'<<genOp()<<genNum()<<endl;
            break;
        case 3: //1+(2+3+4)类型
            fout<<genNum()<<genOp()<<'('<<genNum()<<genOp()<<genNum()<<genOp()<<genNum()<<')'<<endl;
            break;
        case 4: //1+2+(3+4)类型
            fout<<genNum()<<genOp()<<genNum()<<genOp()<<'('<<genNum()<<genOp()<<genNum()<<')'<<endl;
            break;
        default:
            printf("calculation type wrong\n");
    }
    fout.close();
}

int main() {
    string cal;
    for(int i=0; i<30; i++)
        genCal1();
    for(int i=0; i<30; i++)
        genCal2();
    return 0;
}
