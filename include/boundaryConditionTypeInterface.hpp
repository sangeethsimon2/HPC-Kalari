/* Virtual base class for all variants of boundary condition implementations for the heat equation */
/*Part of the 'factory method design pattern' to call the correct updateboundary method
depending on the user choice*/
#ifndef _BOUNDARYCONDITIONTYPEINTERFACE_H
#define _BOUNDARYCONDITIONTYPEINTERFACE_H

class BoundaryConditionTypeInterface{
    public:
           virtual void updateBoundaries(float* _ptr2SolutionInitial, int _Nx=0, int _Ny=0, int _Nz=0, float _surfaceTemperature=0.)=0;
           virtual ~BoundaryConditionTypeInterface() = default;
};

#endif