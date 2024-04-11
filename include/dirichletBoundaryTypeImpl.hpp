/*Class that implements the dirichlet boundary condition*/
/*This class implements the specific 'update' method
that will be called by the factory method in the BC updater class*/

#ifndef _DIRICHLETIMPL_H
#define _DIRICHLETIMPL_H

#include<iostream>

#include "boundaryConditionTypeInterface.hpp"

template<int DIM>
class DirichletImpl: public BoundaryConditionTypeInterface{

    public:
            //CTOR
            DirichletImpl(){};
            void updateBoundaries(double*, int, int, int, double);


};
#endif