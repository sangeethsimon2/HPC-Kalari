/* Virtual base class that is tasked with instantiating the correct
boundary condition implementation through the 'factory method' pattern
and using it to update the boundaries.
The interface of this class interacts with the main*/

#ifndef _BOUNDARYUPDATERINTERFACE_H
#define _BOUNDARYUPDATERINTERFACE_H

#include "boundaryConditionTypeInterface.hpp"


class BoundaryUpdaterInterface{
    public:
           //CTOR
           BoundaryUpdaterInterface(float* _ptr2State): m_ptr2State(_ptr2State){}
           //Method to set the boundary condition strategy
           void setBoundaryConditionType(){m_BCType =this->createBoundaryType();}

           //Method to call the update method generated from the factory method
           void updateBoundaries(){
            m_BCType->updateBoundaries(m_ptr2State);
           }
           virtual BoundaryConditionTypeInterface* createBoundaryType()=0;
           virtual ~BoundaryUpdaterInterface() = default;
    protected:
           //Member to store a pointer to the state whose boundary has to be updated
           float* m_ptr2State;
           //Member to store the type of boundary condition that must be used.
           // The factory method must return the updateBoundaries() of this type
           BoundaryConditionTypeInterface* m_BCType;
};

#endif