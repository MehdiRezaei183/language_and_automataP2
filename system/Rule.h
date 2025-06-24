//
// Created by my pc on 6/17/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_RULE_H
#define LANGUAGE_AND_AUTOMATAP2_RULE_H

#include "Var_Ter/Variable.h"
#include "Var_Ter/Terminal.h"
#include "Expression.h"

class Rule {
private:
    Variable* LeftSide;
    Expression RightSide;
public:
    Rule(Variable* , Expression&);
    Variable* getLeft();
    Expression getRight();

    void setVar(Variable*);
    void setExp(Expression&);

};


#endif //LANGUAGE_AND_AUTOMATAP2_RULE_H
