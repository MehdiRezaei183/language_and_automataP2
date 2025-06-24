//
// Created by my pc on 6/17/2025.
//

#include "Rule.h"

Variable* Rule::getLeft() {
    return this->LeftSide;
}

Expression Rule::getRight() {
    return this->RightSide;
}
Rule ::Rule(Variable* variable, Expression& expression) : LeftSide(variable) , RightSide(expression){}

void Rule::setExp(Expression & input) { this->RightSide = input;}

void Rule::setVar(Variable *input) { this->LeftSide = input;}

