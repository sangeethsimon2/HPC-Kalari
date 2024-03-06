#include<iostream>
#include<string>
#include<memory>
#include <stdexcept>

#include "parameterObject.hpp"
#include "grid.hpp"
#include "structuredGrid.hpp"


int main(int argc, char **argv){
    std::string fileName = argv[1];

    //create a parameter class instance
    parameters* params = parameters::getInstance(fileName);


    //Create a structured grid instance and pass its ownership to a Grid smart pointer
    std::unique_ptr<Grid> grid;
    if(params->getDimensionality()==2){
    grid = std::make_unique<StructuredGrid<2>>(params->getDomainLength("x"),
    params->getDomainLength("y"), params->getGridSize("x"), params->getGridSize("y"));
    }
    else if(params->getDimensionality()==3){
    grid = std::make_unique<StructuredGrid<3>>(params->getDomainLength("x"),
    params->getDomainLength("y"), params->getDomainLength("z"), params->getGridSize("x"),
    params->getGridSize("y"), params->getGridSize("z"));
    }
    else {
         throw std::invalid_argument("Invalid value of DIM. Unable to initialize grid\n");
    }
    grid->createGrid();

    return 0;
}