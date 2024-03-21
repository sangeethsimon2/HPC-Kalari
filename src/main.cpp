#include<iostream>
#include<string>
#include<memory>
#include<stdexcept>
#include<cmath>

#include "parameterObject.hpp"
#include "grid.hpp"
#include "structuredGrid.hpp"
#include "state.hpp"
#include "initializer.hpp"
#include "hostTimer.hpp"
#include "kernel.hpp"
#include "jacobiSerialImpl.hpp"
#include "boundaryCreatorInterface.hpp"
#include "dirichletBoundaryCreator.hpp"




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
    std::shared_ptr<State> temperature_initial = std::make_shared<State>(params->getTotalGridSize());
    std::shared_ptr<State> temperature_updated = std::make_shared<State>(params->getTotalGridSize());

    //Initialize using an initializer class
    Initializer initializationObject;
    initializationObject.initialize(temperature_initial.get(), params->getTotalGridSize(), 1.0);
    initializationObject.initialize(temperature_updated.get(), params->getTotalGridSize(), 0.0);

    //Create boundary updater and update boundaries
    BoundaryCreatorInterface* boundaryUpdater = new DirichletBoundaryCreator(temperature_initial.get()->getState(),
    params->getGridSize("x"), params->getGridSize("y"), params->getGridSize("z"), 10.0);
    //Set the boundary condition type (in the background the factory method is called)
    boundaryUpdater->setBoundaryConditionType();
    //Call the update method of the correct boundary type

    //Create a Kernel instance
    Kernel<2> heatKernel(std::make_unique<JacobiSerialImpl<2>>(params->getGridSize("x"), params->getGridSize("y"), params->getGridSize("z"),
    params->getTimeStep(), params->getConductivityCoeff()));

    //Instantiate a host timer
    hostTimer hostTimer;
    hostTimer.startClock();
    int iter=0;
    //while(iter<1)
    do{
      //For dirichlet boundary conditions, call this only once; for other types, call in convergence loop
      boundaryUpdater->updateBoundaries();

      //Call the update method
      heatKernel.updateSolution(temperature_initial.get(), temperature_updated.get());

      //Compute error
      float error = sqrt(heatKernel.computeError());
      std::cout<<"Error="<<error<<"\n";
      //Check for convergence
      /* Break if convergence reached or step greater than maxStep */
      if (error<params->getConvergenceTolerance()) break;
      iter++;
    //}
    }while(true);
    hostTimer.stopClock();
    hostTimer.printElapsedTime();
    return 0;
}