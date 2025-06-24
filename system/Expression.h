//
// Created by my pc on 6/17/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_EXPRESSION_H
#define LANGUAGE_AND_AUTOMATAP2_EXPRESSION_H

#include <string>
#include "Var_Ter/Terminal.h"
#include "Var_Ter/Variable.h"

class Expression {
private:
    string line;
    vector<Interface_Ter_Var*> types;
public:
    Expression() = default;
    explicit Expression(string input , vector<Interface_Ter_Var*> type);

    string getLine(){ return this->line;}
    void setLine(string input);

    vector<Interface_Ter_Var*> getTypes(){return this->types;}

    bool isInLine(const Interface_Ter_Var* input);
};


#endif //LANGUAGE_AND_AUTOMATAP2_EXPRESSION_H
