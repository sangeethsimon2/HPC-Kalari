#include<iostream>
#include<string>
#include<memory>
#include<stdexcept>
#include<cmath>

#include "solver.hpp"
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
#include "IOManagerFactory.hpp"
#include "IOManager.hpp"
#include "VTKWriter.hpp"


int main(int argc, char **argv){
    std::string fileName = argv[1];

    // Create an instance of the Solver class
    Solver solver;

    //create a parameter class instance
    solver.createParameters(fileName);

    //Create a structured grid instance and pass its ownership to a Grid smart pointer
    solver.createGrid();

    // Create an  flattened array to store the temperature data
    solver.createState();

    //Initialize using an initializer class
    solver.initializeStates();

    //Create boundary updater and update boundaries
    solver.createBoundaryCondition();

    //Create a Kernel instance
    solver.createKernel();

    //Instantiate a host timer
    hostTimer hostTimer;
    hostTimer.startClock();
    int iter=0;
    do{
      //For dirichlet boundary conditions, call this only once; for other types, call in convergence loop
      solver.updateBoundaries();

      //Call the update method
      solver.updateSolution();

      // //Compute error
      solver.computeError();
      //Check for convergence
      /* Break if convergence reached or step greater than maxStep */
      if (solver.getError()<solver.getConvergenceTolerance()) break;
      iter++;
    }while(true);
    hostTimer.stopClock();
    hostTimer.printElapsedTime();


    // Create IOManager using Factory
    std::shared_ptr<IOManager> ioManager = IOManagerFactory::createIOManager(solver.getPtr2Parameters());
    if (ioManager) {
        ioManager->setParameter(solver.getPtr2Parameters());
        ioManager->setState(solver.getPtr2Temperature_updated());
        ioManager->writeOutput();
    }
    return 0;
}