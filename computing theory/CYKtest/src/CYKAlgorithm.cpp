#include <string>
#include <iostream>
#include <fstream>
#include "../include/CNF.h"
using namespace std;

//切割字符串
vector<string> split(string str, char c) {
	vector<string> segments;
	string tmp;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == c) {
			if (tmp != "") //防止相邻的分隔符导致划分出空串
				segments.push_back(tmp);
			tmp = "";
		}
		else {
			tmp = tmp + str[i];
		}
	}
	if (tmp != "")
		segments.push_back(tmp);
	return segments;
}

//从文件中加载乔姆斯基范式的CFG
void loadCNF(CNF& cnf, string file) {
	fstream fin(file);
	//打不开
	if (fin.fail()) {
		cout << "Cannot open input file!\n";
		exit(1);
	}
	string rule;
	//一次读一行
	while (getline(fin, rule)) {
		int namePos = rule.find("->");
		//找不到箭头则报错
		if (namePos == string::npos) {
			cout << "Invalid input file!\n";
			exit(2);
		}
		Variable name;
		//读取产生式左边的变元
		for (int i = 0; i < namePos; i++) {
			name = name + rule[i];
		}
		Variable restRule;
		//读取产生式的右部
		for (size_t i = namePos + 2; i < rule.length(); i++) {
			restRule = restRule + rule[i];
		}
		//按照'|'分割产生式的右部
		vector<string> rules = split(restRule, '|');

		//归纳表达式
		for (auto rule:rules) {
            //如果长度超过1，就是非终结符表达式
		    if (rule.size() > 1) {
		        //字符转字符串
		        string var1, var2 = "";
                ProductionRuleWithNonterminal p(name, var1.append(1, rule[0]), var2.append(1, rule[1]));
                cnf.addRule(p);
		    }
            //如果长度不超过1，就是终结符表达式
		    else {
                ProductionRuleWithTerminal p(name, rule);
                cnf.addRule(p);
		    }
		}
	}
}

//判断是否是乔姆斯基范式
bool judge(string str, const CNF& cnf) {
	//读取字符串
	vector<string> sentence;
	for (auto c:str) {
	    string temp = "";
	    temp.append(1, c);
        sentence.push_back(temp);
	}
	int wordCount = sentence.size();

	//为了方便，矩阵的大小为(wordCount+1)*(wordCount+1)，丢弃丢弃[0,0], 从[1,1]开始存
	set<Variable>** judgeMat = new set<Variable>*[wordCount + 1];
	for (int i = 0; i <= wordCount; i++) {
		judgeMat[i] = new set<Variable>[wordCount + 1];
	}

	//把所有生成的变元存入judgeMat[i][i]
	//[i,i]存放输入的第i个字符所产生的所有字符串
	for (int i = 1; i <= wordCount; i++) {
		judgeMat[i][i] = cnf.produce(sentence[i - 1]);
	}

	//计算judgeMat的剩余部分
	for (int length = 2; length <= wordCount; length++) {
		for (int i = 1; i <= wordCount - length + 1; i++) {
			for (int k = i; k < i + length - 1; k++) {
				set<Variable> tmp = cnf.produce(judgeMat[i][k], judgeMat[k + 1][i + length - 1]);
				//新增（取交集）
				judgeMat[i][i + length - 1].insert(tmp.begin(), tmp.end());
			}
		}
	}

	//打印判断矩阵的所有内容
	for (int stringLen = 1; stringLen <= wordCount; stringLen++) {
        int i,j;
        j = wordCount-stringLen+1;
	    for (i = 1; i <= stringLen; i++) {
//            cout << "judgeMat[" << i << "][" << j << "]";
            for (auto temp:judgeMat[i][j])
                cout << temp;
            cout << " ";
            j++;
	    }
	    cout << endl;
	}

	if (judgeMat[1][wordCount].find(cnf.getStartSymbol()) != judgeMat[1][wordCount].end()) {
        return true;
	}
	else
        return false;
}

int main(int argc, const char** argv) {
    if (argc != 2) {
        cout << "输入有误!\n";
        exit(3);
    }
    CNF cnf;
    loadCNF(cnf, argv[1]);
//    用于测试是否能正确解析乔姆斯基范式
//    cnf.print();
    while (1) {
        string str;
        cout << "输入待检测字符串: ";
        getline(cin, str);
        if (str == "-1")
            break;
        else if (judge(str, cnf)) {
            cout << str << "属于该文法\n" << endl;
        }
        else {
            cout << str << "不属于该文法\n" << endl;
        }
    }
    return 0;
}
