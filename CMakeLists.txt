cmake_minimum_required(VERSION 3.27)
project(language_and_automataP2)

set(CMAKE_CXX_STANDARD 17)

add_executable(language_and_automataP2 main.cpp
        system/Var_Ter/Variable.cpp
        system/Var_Ter/Terminal.cpp
        system/Var_Ter/Interface_Ter_Var.cpp
        system/Var_Ter/Variable.h
        system/Var_Ter/Terminal.h
        system/Var_Ter/Interface_Ter_Var.h
        system/Expression.h
        system/Expression.cpp
        system/Grammar.h
        system/Grammar.cpp
        system/Rule.cpp
)
