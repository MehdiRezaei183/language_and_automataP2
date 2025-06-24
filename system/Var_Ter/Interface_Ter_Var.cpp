//
// Created by my pc on 6/17/2025.
//

#include "Interface_Ter_Var.h"
char Interface_Ter_Var::getTag() const {return this->tag;}

void Interface_Ter_Var::setTag(char input) { this->tag = input;}

Interface_Ter_Var::Interface_Ter_Var(char input) : tag(input){}

bool Interface_Ter_Var::isVar() {return false;}