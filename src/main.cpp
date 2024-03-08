#include<iostream>
#include<string>
#include<memory>
#include <stdexcept>

#include "parameterObject.hpp"
#include "grid.hpp"
#include "structuredGrid.hpp"
#include "state.hpp"
#include "initializer.hpp"


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

    // Create the grid
    grid->createGrid();

    // Create an  flattened array to store the temperature data
    // Ownership of this temperature state can be shared if needed
    std::shared_ptr<State> temperature = std::make_shared<State>(params->getGridSize("x")*params->getGridSize("y")*params->getGridSize("z"));

    //Initialize using an initializer class
    Initializer initializationObject;
    initializationObject.initialize(temperature.get(), params->getGridSize("x")*params->getGridSize("y")*params->getGridSize("z"), 1.0);




    return 0;
}