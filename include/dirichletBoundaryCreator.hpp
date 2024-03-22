/*Class that creates the object that implements the dirichlet boundary condition.
Part of the factor method patter covering the bondary condition implementation*/

#ifndef _DIRICHLETBOUNDARYCREATOR_H
#define _DIRICHLETBOUNDARYCREATOR_H

#include<iostream>

#include "boundaryCreatorInterface.hpp"
#include "dirichletBoundaryTypeImpl.hpp"

template<int DIM>
class DirichletBoundaryCreator: public BoundaryCreatorInterface{
    public:
            //CTOR
            DirichletBoundaryCreator(float* _ptr2State, int _Nx, int _Ny, int _Nz=0, float _surfaceTemp=0.): BoundaryCreatorInterface(_ptr2State, _Nx, _Ny, _Nz, _surfaceTemp){}
            BoundaryConditionTypeInterface* createBoundaryType() override{return(new DirichletImpl<DIM>());}

};

#endif