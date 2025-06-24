//
// Created by my pc on 6/17/2025.
//

#ifndef LANGUAGE_AND_AUTOMATAP2_INTERFACE_TER_VAR_H
#define LANGUAGE_AND_AUTOMATAP2_INTERFACE_TER_VAR_H
using namespace std;

#include "vector"

class Interface_Ter_Var {
private:
    char tag;

public:
    Interface_Ter_Var() = default;
    Interface_Ter_Var(char input);
    void setTag(char input);
    char getTag()const;
    virtual bool isVar();
};


#endif //LANGUAGE_AND_AUTOMATAP2_INTERFACE_TER_VAR_H
