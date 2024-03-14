/*Class that creates the object that implements the dirichlet boundary condition.
Part of the factor method patter covering the bondary condition implementation*/

#ifndef _DIRICHLETBOUNDARYCREATOR_H
#define _DIRICHLETBOUNDARYCREATOR_H

#include<iostream>

#include "boundaryUpdaterInterface.hpp"
#include "dirichletBoundaryConditionImpl.hpp"


class DirichletBoundaryCreator: public BoundaryUpdaterInterface{
    public:
            //CTOR
            DirichletBoundaryCreator(float* _ptr2State): BoundaryUpdaterInterface(_ptr2State){}
            BoundaryConditionTypeInterface* createBoundaryType() override{return(new DirichletImpl());}

};

#endif