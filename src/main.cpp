#include<iostream>
#include<string>
#include "parameterObject.hpp"

int main(int argc, char **argv){
    std::string fileName = argv[1];
    parameters* params = parameters::getInstance(fileName);
    return 0;
}