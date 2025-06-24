//
// Created by my pc on 6/18/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_GRAMMER_H
#define LANGUAGE_AND_AUTOMATAP2_GRAMMER_H

#include "Rule.h"
#include "sstream"
#include "map"
#include "regex"

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

private:
    vector<Interface_Ter_Var*> getTypes(const string& input);
    bool isTerminal (const char& input)const;

    void CheckVar(map<char , bool>& reachable , Variable* current);
public:
    // Removing useless productions
    void RemoveUseless();
};


#endif //LANGUAGE_AND_AUTOMATAP2_GRAMMER_H
