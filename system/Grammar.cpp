//
// Created by my pc on 6/18/2025.
//

#include "Grammar.h"

void Grammar::setTerminals(const vector <Terminal*> &list) {
    for (auto const & item : list) {
        terminals[item->getTag()] = item;
    }
}

void Grammar ::setVariables(const vector <Variable*> &list) {
    for (auto const & item : list) {
        variables[item->getTag()] = item;
    }
}

void Grammar::addRule(std::string &input) {
    try{
        // excption  must be added hear;
    }
    catch (...){

    }
    string variable = input.substr(0 , input.find('-') - 1);
    string expr = input.substr(input.find('>')+2);
    expr.erase(remove(expr.begin() , expr.end(),' '),expr.end());
    auto var = new Variable(variable[0]);


    stringstream ss(expr);
    string temp;



    while (getline(ss , temp ,'|')){
        Expression line = Expression(temp , this->getTypes(temp));
        Rule* rule = new Rule(var , line);
        if(Rules.find(var->getTag()) == Rules.end()) {
            Rules[var->getTag()] = vector < Rule * > {rule};
        }
        else{
            Rules[var->getTag()].push_back(rule);
        }
    }
}

vector <Interface_Ter_Var*> Grammar::getTypes(const std::string &input) {
    vector<Interface_Ter_Var*> types;
    for (auto const & item : input) {
        if(terminals.find(item) != terminals.end()){
            types.push_back(terminals[item]);
        }else{
            types.push_back(variables[item]);
        }
    }
    return types;
}

bool Grammar::isTerminal(const char &input) const {return terminals.find(input) != terminals.end();}

void Grammar::CheckVarUseLess(map<char, bool> &reachable , Variable* current) {
    for (auto const & item : Rules[current->getTag()]) {
        for (auto const& rule : item->getRight().getTypes()) {
            if(rule->isVar()){
                if(!reachable[rule->getTag()]){
                    reachable[rule->getTag()] = true;
                    CheckVarUseLess(reachable , variables[rule->getTag()]);
                }

            }
        }
    }
}

// Deleting:
void Grammar::RemoveUseless() {
    map<char , bool> reachable;
    for(auto const& item  : this->variables){
        reachable[item.first] = false;
    }
    reachable['S'] = true;
    CheckVarUseLess(reachable , variables['S']);
    for (auto const item : reachable) {
        if(!item.second){
            variables.erase(item.first);
            Rules.erase(item.first);
        }

    }
}

bool Grammar::all_of_M(vector<Interface_Ter_Var *> list, map<char, bool> &finals) {
    for (auto first = list.begin(); first != list.end() ; first++) {
        if((*first)->isVar() && !finals[(*first)->getTag()]){
            return false;
        }
    }
    return true;
}

void Grammar::CheckRuleLoop(map<char, bool>& Finals) {
    queue<Variable*> line;
    for (auto const & item : this->variables) {
        line.push(item.second);
    }
    int isDone = line.size();
    while (!line.empty() && isDone >= 0){
        Variable* temp = line.front();
        line.pop();
        for (auto const& item : Rules[temp->getTag()]) {
            if(item->getRight().isFinal() || all_of_M(item->getRight().getTypes(),Finals)){
                Finals[temp->getTag()] = true;
                isDone = line.size();
                break;
            }
        }

        if(!Finals[temp->getTag()]){
            line.push(temp);
            isDone--;
        }

    }
}

void Grammar::RemoveInfinite() {
    map<char , bool> Finals;
    for (auto const & item : variables) {
        Finals[item.first] = false;
    }
    CheckRuleLoop(Finals);
    for (auto const& item : Finals) {
        if(!item.second){
            variables.erase(item.first);
            Rules.erase(item.first);
        }
    }
}