#include <iostream>
#include "vector"
#include "system/Grammar.h"


int main() {
    Grammar test;
    vector<Terminal*> list1;
    vector<Variable*> list2;
    int n;
    cin >> n;

    string line , temp;
    getline( cin >> ws ,line);
    stringstream ss(line);
    while (ss >> temp){
        list1.push_back(new Terminal(temp[0]));
    }
    list1.push_back(new Terminal('@'));

    getline(cin >> ws , line);
    stringstream ss1(line);
    while (ss1 >> temp){
        list2.push_back(new Variable(temp[0]));
    }

    test.setTerminals(list1);
    test.setVariables(list2);

    for (int i = 0; i < n; ++i) {
        string input;
        getline(cin >> ws , input);
        test.addRule(input);
    }
    test.Removing();
    test.transformToUpper();
    test.transformFinal();
    test.printGrammar();

    return 0;
}
