#ifndef _CNF_H_
#define _CNF_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>

typedef std::string Variable;
typedef std::string Terminal;

class ProductionRuleWithNonterminal {
private:
	Variable name;
	Variable v1, v2;

public:
	ProductionRuleWithNonterminal();
	ProductionRuleWithNonterminal(Variable name, Variable v1, Variable v2);

	void changeRule(Variable name, Variable v1, Variable v2);

	Variable produce(Variable v1, Variable v2) const;

	void print() const;

	Variable getName() const;
};

class ProductionRuleWithTerminal {
private:
	Variable name;
	Terminal str;

public:
	ProductionRuleWithTerminal();
	ProductionRuleWithTerminal(Variable name, Terminal str);
	void changeRule(Variable name, Terminal str);
	Variable produce(Terminal str) const;
	void print() const;
	Variable getName() const;
};

//实现CFG
class CNF {
private:
	std::vector<ProductionRuleWithNonterminal> rulesWithNonterminal;
	std::vector<ProductionRuleWithTerminal> rulesWithTerminal;
	Variable startSymbol;

public:
	//得到val1, val2能产生的变元集合
	std::set<Variable> produce(std::set<Variable> val1, std::set<Variable> val2) const;
	//得到字符串str能产生的变元集合
	std::set<Variable> produce(Terminal str) const;
	//增加非终结符产生式
	void addRule(ProductionRuleWithNonterminal rule);
	//增加终结符产生式
	void addRule(ProductionRuleWithTerminal rule);
	//获取CFG的初始变元
	Variable getStartSymbol() const;
	//打印CFG，用于测试
	void print() const;
};

#endif
