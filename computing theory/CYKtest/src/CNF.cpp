#include "../include/CNF.h"

ProductionRuleWithNonterminal::ProductionRuleWithNonterminal() {
}

ProductionRuleWithNonterminal::ProductionRuleWithNonterminal(Variable name, Variable v1, Variable v2) {
	this->name = name;
	this->v1 = v1;
	this->v2 = v2;
}

//非终结符的产生式
void ProductionRuleWithNonterminal::changeRule(Variable name, Variable v1, Variable v2) {
	this->name = name;
	this->v1 = v1;
	this->v2 = v2;
}

//Judge whether two variables v1 and v2 can produce a variable through the production
//Return value: the name of the produced variable or "" if they can't
Variable ProductionRuleWithNonterminal::produce(Variable v1, Variable v2) const {
	if (v1 == this->v1 && v2 == this->v2)
		return name;
	else {
		Variable fail = "";
		return fail;
	}
}

void ProductionRuleWithNonterminal::print() const {
	std::cout << name << "->" << v1 << v2 << std::endl;
}

//获取产生式的变元名称
Variable ProductionRuleWithNonterminal::getName() const {
	return name;
}

ProductionRuleWithTerminal::ProductionRuleWithTerminal() {
}

ProductionRuleWithTerminal::ProductionRuleWithTerminal(Variable name, Terminal str) {
	this->name = name;
	this->str = str;
}

//Change the production rule
void ProductionRuleWithTerminal::changeRule(Variable name, Terminal str) {
	this->name = name;
	this->str = str;
}

//Judge whether a string str can produce a variable through the production
//Return value: the name of the produced variable or "" if it can't
Variable ProductionRuleWithTerminal::produce(Terminal str) const {
	if (this->str == str)
		return name;
	else {
		Variable fail = "";
		return fail;
	}
}

//打印产生式
void ProductionRuleWithTerminal::print() const {
	std::cout << name << "->" << str << std::endl;
}

//得到产生式所产生的所有变量的名称
Variable ProductionRuleWithTerminal::getName() const {
	return name;
}

//得到val1, val2所能推导出的变元的集合
std::set<Variable> CNF::produce(std::set<Variable> val1, std::set<Variable> val2) const {
	std::set<Variable> vals;
	for (auto rule = rulesWithNonterminal.begin(); rule != rulesWithNonterminal.end(); rule++) {
		for (auto i = val1.begin(); i != val1.end(); i++) {
			for (auto k = val2.begin(); k != val2.end(); k++) {
				Variable val = rule->produce(*i, *k);
				if (val != "")
					vals.insert(val);
			}
		}
	}
	return vals;
}

/* 得到字符串str能推出的所有变元
 * 遍历所有推导规则，如果str可以推出变元，则加入集合，返回
*/
std::set<Variable> CNF::produce(Terminal str) const {
	std::set<Variable> vals;
	for (auto i = rulesWithTerminal.begin(); i != rulesWithTerminal.end(); i++) {
		Variable val = i->produce(str);
		if (val != "")
			vals.insert(val);
	}
	return vals;
}

//非终结符的产生规则
void CNF::addRule(ProductionRuleWithNonterminal rule) {
	rulesWithNonterminal.push_back(rule);
}

//终结符的产生规则
void CNF::addRule(ProductionRuleWithTerminal rule) {
	rulesWithTerminal.push_back(rule);
}

//获得文法的start
Variable CNF::getStartSymbol() const {
	return rulesWithNonterminal[0].getName();
}

//打印文法
void CNF::print() const {
	for (auto i = rulesWithNonterminal.begin(); i != rulesWithNonterminal.end(); i++) {
		i->print();
	}
	for (auto i = rulesWithTerminal.begin(); i != rulesWithTerminal.end(); i++) {
		i->print();
	}
}
