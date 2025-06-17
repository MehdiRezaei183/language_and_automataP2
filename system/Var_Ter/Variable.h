//
// Created by my pc on 6/17/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_VARIABLE_H
#define LANGUAGE_AND_AUTOMATAP2_VARIABLE_H

#include "Interface_Ter_Var.h"

class Variable : public Interface_Ter_Var{

public:
    Variable() = default;
    explicit Variable(char input);
    bool isVar() override;
};


#endif //LANGUAGE_AND_AUTOMATAP2_VARIABLE_H
