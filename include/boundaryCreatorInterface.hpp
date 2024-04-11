/* Virtual base class that is tasked with instantiating the correct
boundary condition implementation through the 'factory method' pattern
and using it to update the boundaries.
The interface of this class interacts with the main*/

#ifndef _BOUNDARYUPDATERINTERFACE_H
#define _BOUNDARYUPDATERINTERFACE_H

#include "boundaryConditionTypeInterface.hpp"


class BoundaryCreatorInterface{
    public:
           //CTOR
           BoundaryCreatorInterface(double* _ptr2State, int _Nx, int _Ny, int _Nz=0, double _surfaceTemp=0.): m_ptr2State(_ptr2State),
           m_Nx(_Nx), m_Ny(_Ny), m_Nz(_Nz), m_surfaceTemp(_surfaceTemp){}
           //Method to set the boundary condition strategy
           void setBoundaryConditionType(){
              m_BCType =this->createBoundaryType();
              std::cout<<"Setting up Dirichlet boundary condition\n";
       }

           //Method to call the update method generated from the factory method
           void updateBoundaries(){
            m_BCType->updateBoundaries(m_ptr2State, m_Nx, m_Ny, m_Nz, m_surfaceTemp);
           }
           virtual BoundaryConditionTypeInterface* createBoundaryType()=0;
           virtual ~BoundaryCreatorInterface() = default;
    protected:
           //Member to store a pointer to the state whose boundary has to be updated
           double* m_ptr2State;
           //Member to store the grid size in 3 directions
           int m_Nx, m_Ny, m_Nz;
           //TODO Get rid of the need to store the surface temp here - it only belongs to the
           //dirichlet class?
           //Member to store the surface temperature
           double m_surfaceTemp;
           //Member to store the type of boundary condition that must be used.
           // The factory method must return the updateBoundaries() of this type
           BoundaryConditionTypeInterface* m_BCType;
};

#endif