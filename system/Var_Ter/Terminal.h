//
// Created by my pc on 6/17/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_TERMINAL_H
#define LANGUAGE_AND_AUTOMATAP2_TERMINAL_H

#include "Interface_Ter_Var.h"

class Terminal : public Interface_Ter_Var{
public:
    Terminal() = default;
    explicit Terminal(char  input);
    bool isVar() override;
};


#endif //LANGUAGE_AND_AUTOMATAP2_TERMINAL_H
