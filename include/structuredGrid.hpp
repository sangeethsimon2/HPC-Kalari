/*Child class that inherits from the Grid class and implements some of its virtual functions to achieve structured grid creation*/
#ifndef _STRUCTUREDGRID_H
#define _STRUCTUREDGRID_H

#include <vector>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

template<int DIM>
class StructuredGrid:public Grid{

    public:
          //Delete copy CTOR
          StructuredGrid(StructuredGrid& param) = delete;

          //Delete assigment CTOR
          void operator =(const StructuredGrid&) = delete;

          //CTOR
          StructuredGrid(double _domainX=1, double _domainY=1, double _domainZ=0, int _Nx=1, int _Ny=1, int _Nz=1):
                         Grid(_domainX, _domainY, _domainZ, _Nx, _Ny, _Nz){

                // Method call to compute the grid spacing
                //computeGridSpacing();
            }
          //DTOR
          ~StructuredGrid(){
                gridArray.resize(0);
            }

          //Method to compute grid spacing
          void computeGridSpacing();

          //Override the interfaces of the base class
          //Override the create grid class
          void createGrid()override final;

    private:
          std::vector<double> gridArray;
};


#endif