/*A non-Abstract class that will own pointers to various components of a solver like grid, initializer, boundary updater, kernel etc
and instantiates them with the right objects*/

#ifndef _SOLVER_H
#define _SOLVER_H

#include "parameterObject.hpp"
#include "grid.hpp"
#include "structuredGrid.hpp"
#include "state.hpp"
#include "initializer.hpp"
#include "boundaryCreatorInterface.hpp"
#include "dirichletBoundaryCreator.hpp"
#include "kernel.hpp"
#include "jacobiSerialImpl.hpp"

class Solver {
    public:
        //Default CTOR
        Solver()=default;
        //Delete copy CTOR
        Solver(Solver& solver) = delete;
        //Delete assigment CTOR
        Solver& operator =(const Solver&) = delete;
        //Virtual destructor
        virtual ~Solver() = default;

        //Getter functions to pointers
        std::shared_ptr<parameters> getPtr2Parameters() const {return m_ptr2Parameters;}
        std::shared_ptr<Grid> getPtr2Grid() const {return m_ptr2Grid;}
        std::shared_ptr<State> getPtr2Temperature_initial() const {return m_ptr2Temperature_initial;}
        std::shared_ptr<State> getPtr2Temperature_updated() const {return m_ptr2Temperature_updated;}



        //Interface function that sets the parameters object
        void createParameters(const std::string& fileName){
          m_ptr2Parameters = parameters::getInstance(fileName);

          m_convergenceTolerance = m_ptr2Parameters->getConvergenceTolerance();
        }
        //Interface method to create the grid instance and pass its ownership to a Grid smart pointer
        void createGrid(){
            if(m_ptr2Parameters){
                if(m_ptr2Parameters->getDimensionality()==2){
                    m_ptr2Grid = std::make_unique<StructuredGrid<2>>(m_ptr2Parameters->getDomainLength("x"),
                    m_ptr2Parameters->getDomainLength("y"), m_ptr2Parameters->getGridSize("x"), m_ptr2Parameters->getGridSize("y"));
                }
                else if(m_ptr2Parameters->getDimensionality()==3){
                    m_ptr2Grid = std::make_unique<StructuredGrid<3>>(m_ptr2Parameters->getDomainLength("x"),
                    m_ptr2Parameters->getDomainLength("y"), m_ptr2Parameters->getDomainLength("z"), m_ptr2Parameters->getGridSize("x"),
                    m_ptr2Parameters->getGridSize("y"), m_ptr2Parameters->getGridSize("z"));
                }
                else {
                    throw std::invalid_argument("Invalid value of DIM. Unable to initialize grid\n");
                }
            }
            // Create the grid
            m_ptr2Grid->createGrid();
        }

        //Interface method to create the states and pass its ownership to a State smart pointer
        void createState(){
            // Create an  flattened array to store the temperature data
            // Ownership of this temperature state can be shared if needed
            m_ptr2Temperature_initial = std::make_shared<State>(m_ptr2Parameters->getTotalGridSize());
            m_ptr2Temperature_updated = std::make_shared<State>(m_ptr2Parameters->getTotalGridSize());
        }

        //Interface method to initiate the states
        //Initialize using an initializer class
        void initializeStates(){
            m_ptr2Initializer->initialize(m_ptr2Temperature_initial.get(), m_ptr2Parameters->getTotalGridSize(), 1.0);
            m_ptr2Initializer->initialize(m_ptr2Temperature_updated.get(), m_ptr2Parameters->getTotalGridSize(), 0.0);
        }

        //Interface method to create the boundary condition
        void createBoundaryCondition(){
            //Create boundary updater
            if(m_ptr2Parameters->getDimensionality()==2){
                m_ptr2BoundaryUpdater = std::make_unique<DirichletBoundaryCreator<2>>(m_ptr2Temperature_initial.get()->getState(),
                m_ptr2Parameters->getGridSize("x"), m_ptr2Parameters->getGridSize("y"), 0, 10.0);
            }
            else if (m_ptr2Parameters->getDimensionality()==3) {
                m_ptr2BoundaryUpdater = std::make_unique<DirichletBoundaryCreator<3>>(m_ptr2Temperature_initial.get()->getState(),
                m_ptr2Parameters->getGridSize("x"), m_ptr2Parameters->getGridSize("y"), m_ptr2Parameters->getGridSize("z"), 10.0);
            }
            //Set the boundary condition type (in the background the factory method is called)
            m_ptr2BoundaryUpdater->setBoundaryConditionType();
        }

        //Interface method to create the kernel and pass its ownership to a Kernel smart pointer
        void createKernel(){
            //Create a Kernel instance
            if(m_ptr2Parameters->getDimensionality()==2){
                m_ptr2HeatKernel2D = std::make_unique<Kernel<2>>(std::make_unique<JacobiSerialImpl<2>>(m_ptr2Parameters->getGridSize("x"),
                m_ptr2Parameters->getGridSize("y"), 0, m_ptr2Parameters->getTimeStep(), m_ptr2Parameters->getConductivityCoeff()));
            }
            else if (m_ptr2Parameters->getDimensionality()==3) {
                m_ptr2HeatKernel3D =  std::make_unique<Kernel<3>>(std::make_unique<JacobiSerialImpl<3>>(m_ptr2Parameters->getGridSize("x"),
                m_ptr2Parameters->getGridSize("y"), m_ptr2Parameters->getGridSize("z"), m_ptr2Parameters->getTimeStep(), m_ptr2Parameters->getConductivityCoeff()));
            }
            else
               throw std::runtime_error("Invalid value of DIM, unable to initialize kernel\n");
        }

        //Interface method to update boundaries
        void updateBoundaries(){
            m_ptr2BoundaryUpdater->updateBoundaries();
        }


        //Interface method to update solution states
        void updateSolution(){
            m_ptr2HeatKernel2D->updateSolution(m_ptr2Temperature_initial.get(), m_ptr2Temperature_updated.get());
        }

        void computeError(){
            //Compute error
            m_error = sqrt(m_ptr2HeatKernel2D->computeError());
        }

        const float& getError() const{ return(m_error);}

        const float& getConvergenceTolerance()const {return(m_convergenceTolerance) ;}

    protected:
        std::shared_ptr<parameters> m_ptr2Parameters;
        std::shared_ptr<Grid> m_ptr2Grid;
        std::shared_ptr<State> m_ptr2Temperature_initial;
        std::shared_ptr<State> m_ptr2Temperature_updated;
        std::shared_ptr<Initializer> m_ptr2Initializer;

        std::unique_ptr<BoundaryCreatorInterface> m_ptr2BoundaryUpdater;

        // TODO How do I avoid creating two unique ptrs here and instead do this depending only on the dimensionality?
        std::unique_ptr<Kernel<2>> m_ptr2HeatKernel2D;
        std::unique_ptr<Kernel<3>> m_ptr2HeatKernel3D;

        float m_error=0.;
        float m_convergenceTolerance=0.;

};
#endif