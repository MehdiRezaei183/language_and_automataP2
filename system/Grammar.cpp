//
// Created by my pc on 6/18/2025.
//

#include "Grammar.h"

bool Grammar::isExist(const std::string var,const  std::string rule) {
    if(var.size() == 1 && Rules.find(var[0]) != Rules.end()){
        if(var == rule)
            return true;

        for (const auto &item : Rules[var[0]]) {
            if(item->getRight().getLine() == rule){
                return true;
            }
        }
    }
    return false;
}

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

void Grammar::addRuleToVar(std::string var, std::string expr) {
    if(!isExist(var , expr)){
        Expression line = Expression(expr , this->getTypes(expr));
        Rule* rule = new Rule(new Variable(var[0]) , line);
        if(Rules.find(var[0]) == Rules.end()) {
            Rules[var[0]] = vector < Rule * > {rule};
        }
        else{
            Rules[var[0]].push_back(rule);
        }
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

    stringstream ss(expr);
    string temp;

    while (getline(ss , temp ,'|')){
        addRuleToVar(variable , temp);
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
    int isDone = line.size()+10;
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
// loop
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

bool Grammar::isUnit(Expression input) {
    if(input.getLine().size() == 1 && variables.find(input.getLine()[0]) != variables.end()){
        return true;
    }
    return false;
}

// unit
void Grammar::Remove_unit_production() {
    for (auto list = Rules.begin() ; list != Rules.end();list++) {
        for (int i = 0 ; i < (*list).second.size();i++) {
            if(isUnit((*list).second[i]->getRight())){
                if((*list).first == (*list).second[i]->getRight().getLine()[0]){
                    (*list).second.erase((*list).second.begin() + i);
                }
                else{
                    vector<Rule*> temp;
                    for (auto j = Rules[(*list).second[i]->getRight().getLine()[0]].begin();j != Rules[(*list).second[i]->getRight().getLine()[0]].end();j++) {
                        Expression line = Expression((*j)->getRight());
                        temp.push_back(new Rule(new Variable((*list).first),line));
                    }

                    (*list).second.insert((*list).second.end(),temp.begin(),temp.end());
                    (*list).second.erase((*list).second.begin() + i);
                }
                i--;
            }
        }
    }
}

void Grammar::Remove_Landa_Production() {
    for (auto &list : this->Rules) {
        for (auto &item : list.second) {
            if(item->getRight().isInLine(terminals['@'])){
                list.second.erase(std::find(list.second.begin(), list.second.end(),item));
                this->remove_lan(string(1,list.first));
                this->Remove_unit_production();
                break;
            }
        }
    }
    terminals.erase(terminals.find('@'));
}

bool Grammar::remove_lan(const string var ) {
    bool result = false;
    for (auto &list : Rules) {
        for (int item = 0 ; item != list.second.size();item++) {
            if((*(list.second.begin() + item))->getRight().isInLine(variables[var[0]])){
                string expr = (*(list.second.begin() + item))->getRight().getLine();
                expr.erase(remove(expr.begin() , expr.end(),var[0]),expr.end());
                addRuleToVar(string(1,list.first), expr);
                result = true;
            }
        }
    }
    return result;
}

void Grammar::Removing() {
    this->RemoveUseless();
    this->RemoveInfinite();
    this->Remove_unit_production();
    this->RemoveUseless();
    this->Remove_Landa_Production();
    for (auto const& item : variables) {
        if(Rules.find(item.first) == Rules.end()){
            variables.erase(variables.find(item.first));
        }
    }
}

void Grammar::transformToUpper() {
    char base = '1';
    for (auto const & term : terminals) {
        variables[base] = new Variable(base);
        this->addRuleToVar(string (1 , base) , string(1, term.first));
        for (auto const& list : Rules) {
            for (auto & item : list.second) {
                vector<Interface_Ter_Var*> mylist = item->getRight().getTypes();
                if(item->getRight().getLine().size() != 1 && any_of(mylist.begin() , mylist.end() , [term](Interface_Ter_Var* input){
                    return !input->isVar() && input->getTag() ==  term.first;
                })){
                    string line = item->getRight().getLine();
                    size_t pos = line.find(term.second->getTag());
                    while (pos != std::string::npos) {
                        line.replace(pos, 1, string(1 , base));
                        pos = line.find(term.second->getTag(), pos + 1);
                    }
                    Expression temp = Expression(line , this->getTypes(line));
                    item->setExp(temp);
                }
            }
        }
        base++;
    }
}

void Grammar::transformFinal() {
    char base = 'R';
    for (auto const & list : Rules) {
        for (auto const & item : list.second) {
            string line = item->getRight().getLine();
            while (line.size() > 2){
                string temp = line.substr(0 , 2);
                line.erase(0,2);
                line = base + line;
                Expression forLine = Expression(line , this->getTypes(line));
                item->setExp(forLine);
                variables[base] =  new Variable(base);
                addRuleToVar(string(1, base), temp);
                base--;
            }
        }
    }
}

void Grammar::printGrammar() {
    for (auto const& list : Rules) {
        cout << list.first << " -> ";
        for (auto const& item : list.second) {
            cout << item->getRight().getLine() << " | ";
        }
        cout << "\n";
    }
}