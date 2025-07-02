//
// Created by my pc on 6/18/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_GRAMMER_H
#define LANGUAGE_AND_AUTOMATAP2_GRAMMER_H

#include "Rule.h"
#include "sstream"
#include "map"
#include "algorithm"
#include "regex"
#include "iostream"
#include "queue"

class Grammar {
private:
    Variable* head;
    map<char , Terminal*> terminals;
    map<char ,Variable*> variables;
    map<char , vector<Rule*>> Rules;


public:
    void setTerminals(const vector<Terminal*>& list);
    void setVariables(const vector<Variable*>& list);

    void addRule(string& input);
    void addRuleToVar(string var , string expr);

private:
    vector<Interface_Ter_Var*> getTypes(const string& input);
    bool isTerminal (const char& input)const;

    void CheckVarUseLess(map<char , bool>& reachable , Variable* current);
    void CheckRuleLoop(map<char , bool>& Finals );



    bool all_of_M(vector<Interface_Ter_Var *> list, map<char, bool> &finals);
    bool isUnit(Expression input);
    bool isExist(const string var , const string rule);

    bool remove_lan(const string );
public:
    // Removing useless productions
    void RemoveUseless();
    // Removing loop
    void RemoveInfinite();
    // Removing unit position
    void Remove_unit_production();
    // Removing landa from ruls
    void Remove_Landa_Production();

    void Removing();

    //////////////////////////////////////
    void transformToUpper();

    void transformFinal();

    //////////////////////
    void printGrammar();
};


#endif //LANGUAGE_AND_AUTOMATAP2_GRAMMER_H
