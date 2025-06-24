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

// Deleting:
void Grammar::RemoveUseless() {
    map<char , bool> reachable;
    for(auto const& item  : this->variables){
        reachable[item.first] = false;
    }
    reachable['S'] = true;
    CheckVar(reachable , variables['S']);
    for (auto const item : reachable) {
        if(!item.second){
            variables.erase(item.first);
            Rules.erase(item.first);
        }

    }
}

void Grammar::CheckVar(map<char, bool> &reachable , Variable* current) {
    for (auto const & item : Rules[current->getTag()]) {
        for (auto const& rule : item->getRight().getTypes()) {
            if(rule->isVar()){
                if(!reachable[rule->getTag()]){
                    reachable[rule->getTag()] = true;
                    CheckVar(reachable , variables[rule->getTag()]);
                }

            }
        }
    }
}