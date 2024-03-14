/* Virtual base class for all variants of boundary condition implementations for the heat equation */
/*Part of the 'factory method design pattern' to call the correct updateboundary method
depending on the user choice*/
#ifndef _BOUNDARYCONDITIONTYPEINTERFACE_H
#define _BOUNDARYCONDITIONTYPEINTERFACE_H

class BoundaryConditionTypeInterface{
    public:
           virtual void updateBoundaries(float* _ptr2SolutionInitial)=0;
           virtual ~BoundaryConditionTypeInterface() = default;
};

#endif