//
// Created by my pc on 6/17/2025.
//

#include "Expression.h"

#include <utility>

Expression ::Expression(string input , vector<Interface_Ter_Var*> type) : line(std::move(input)),types(std::move(type)){}

void Expression::setLine(std::string input) { this->line = std::move(input);}

bool Expression::isInLine(const Interface_Ter_Var* input) {
    for(auto const& item : this->types){
        if(item->getTag() == input->getTag()){
            return true;
        }
    }
    return false;
}

