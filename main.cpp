#include <iostream>
#include "vector"
#include "system/Grammar.h"


int main() {
    Grammar test;
    vector<Terminal*> list1;
    list1.push_back(new Terminal('a'));
    list1.push_back(new Terminal('b'));
    list1.push_back(new Terminal('@'));

    vector<Variable*> list2;
    list2.push_back(new Variable('S'));
    list2.push_back(new Variable('A'));
    list2.push_back(new Variable('B'));
    list2.push_back(new Variable('D'));
    test.setTerminals(list1);
    test.setVariables(list2);

    string  input = "S -> ASB";
    test.addRule(input);
    input = "A -> aAS | a | @";
    test.addRule(input);
    input = "B -> SbS | A | bb";
    test.addRule(input);
    input = "D -> SbS | A | bb";
    test.addRule(input);
    test.RemoveUseless();

    return 0;
}
