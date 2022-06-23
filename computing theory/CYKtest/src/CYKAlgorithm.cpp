#include <string>
#include <iostream>
#include <fstream>
#include "../include/CNF.h"
using namespace std;

//�и��ַ���
vector<string> split(string str, char c) {
	vector<string> segments;
	string tmp;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == c) {
			if (tmp != "") //��ֹ���ڵķָ������»��ֳ��մ�
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

//���ļ��м�����ķ˹����ʽ��CFG
void loadCNF(CNF& cnf, string file) {
	fstream fin(file);
	//�򲻿�
	if (fin.fail()) {
		cout << "Cannot open input file!\n";
		exit(1);
	}
	string rule;
	//һ�ζ�һ��
	while (getline(fin, rule)) {
		int namePos = rule.find("->");
		//�Ҳ�����ͷ�򱨴�
		if (namePos == string::npos) {
			cout << "Invalid input file!\n";
			exit(2);
		}
		Variable name;
		//��ȡ����ʽ��ߵı�Ԫ
		for (int i = 0; i < namePos; i++) {
			name = name + rule[i];
		}
		Variable restRule;
		//��ȡ����ʽ���Ҳ�
		for (size_t i = namePos + 2; i < rule.length(); i++) {
			restRule = restRule + rule[i];
		}
		//����'|'�ָ����ʽ���Ҳ�
		vector<string> rules = split(restRule, '|');

		//���ɱ��ʽ
		for (auto rule:rules) {
            //������ȳ���1�����Ƿ��ս�����ʽ
		    if (rule.size() > 1) {
		        //�ַ�ת�ַ���
		        string var1, var2 = "";
                ProductionRuleWithNonterminal p(name, var1.append(1, rule[0]), var2.append(1, rule[1]));
                cnf.addRule(p);
		    }
            //������Ȳ�����1�������ս�����ʽ
		    else {
                ProductionRuleWithTerminal p(name, rule);
                cnf.addRule(p);
		    }
		}
	}
}

//�ж��Ƿ�����ķ˹����ʽ
bool judge(string str, const CNF& cnf) {
	//��ȡ�ַ���
	vector<string> sentence;
	for (auto c:str) {
	    string temp = "";
	    temp.append(1, c);
        sentence.push_back(temp);
	}
	int wordCount = sentence.size();

	//Ϊ�˷��㣬����Ĵ�СΪ(wordCount+1)*(wordCount+1)����������[0,0], ��[1,1]��ʼ��
	set<Variable>** judgeMat = new set<Variable>*[wordCount + 1];
	for (int i = 0; i <= wordCount; i++) {
		judgeMat[i] = new set<Variable>[wordCount + 1];
	}

	//���������ɵı�Ԫ����judgeMat[i][i]
	//[i,i]�������ĵ�i���ַ��������������ַ���
	for (int i = 1; i <= wordCount; i++) {
		judgeMat[i][i] = cnf.produce(sentence[i - 1]);
	}

	//����judgeMat��ʣ�ಿ��
	for (int length = 2; length <= wordCount; length++) {
		for (int i = 1; i <= wordCount - length + 1; i++) {
			for (int k = i; k < i + length - 1; k++) {
				set<Variable> tmp = cnf.produce(judgeMat[i][k], judgeMat[k + 1][i + length - 1]);
				//������ȡ������
				judgeMat[i][i + length - 1].insert(tmp.begin(), tmp.end());
			}
		}
	}

	//��ӡ�жϾ������������
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
        cout << "��������!\n";
        exit(3);
    }
    CNF cnf;
    loadCNF(cnf, argv[1]);
//    ���ڲ����Ƿ�����ȷ������ķ˹����ʽ
//    cnf.print();
    while (1) {
        string str;
        cout << "���������ַ���: ";
        getline(cin, str);
        if (str == "-1")
            break;
        else if (judge(str, cnf)) {
            cout << str << "���ڸ��ķ�\n" << endl;
        }
        else {
            cout << str << "�����ڸ��ķ�\n" << endl;
        }
    }
    return 0;
}
