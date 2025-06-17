#include <iostream>
#include "vector"
#include "system/Rule.h"


int main() {
    Terminal* temp = new Terminal('1');
    Variable* temp1 = new Variable('A');
    vector<Interface_Ter_Var*> list;
    list.push_back(temp);
    list.push_back(temp1);
    for(auto  item : list){
        cout << item->isVar() << endl;
    }

    return 0;
}
