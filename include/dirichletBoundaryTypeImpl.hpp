/*Class that implements the dirichlet boundary condition*/
/*This class implements the specific 'update' method
that will be called by the factory method in the BC updater class*/

#ifndef _DIRICHLETIMPL_H
#define _DIRICHLETIMPL_H

#include<iostream>

#include "boundaryConditionTypeInterface.hpp"

class DirichletImpl: public BoundaryConditionTypeInterface{

    public:
            //CTOR
            DirichletImpl(){};

            void updateBoundaries(float* _ptr2State, int _Nx, int _Ny, int _Nz, float _surfaceTemperature){

              //Set surface temperature for all faces intersecting the x axis  at i=0 & i=Nx-1:
              //Left and Right boundaries of the domain
              for(int k=0;k<_Nz;k++)
               for(int j=0;j<_Ny;j++){
                 _ptr2State[j*_Nx+k*_Nx*_Ny] = _surfaceTemperature;
                 _ptr2State[_Nx-1+j*_Nx+k*_Nx*_Ny] = _surfaceTemperature;
                }

              //Set surface temperature for all faces intersecting the y axis at j=0 & j=Ny-1:
              //Top and Bottom boundaries of the domain
              for(int k=0;k<_Nz;k++)
               for(int i=0;i<_Nx;i++){
                _ptr2State[i+k*_Nx*_Ny] = _surfaceTemperature;
                _ptr2State[i+_Ny-1+k*_Nx*_Ny] = _surfaceTemperature;
               }

              //Set surface temperature for all faces intersecting the z axis at k=0 & k=Nz-1:
              //Front and Back boundaries of the domain
              for(int j=0;j<_Ny;j++)
               for(int i=0;i<_Nx;i++){
                _ptr2State[i+j*_Nx] = _surfaceTemperature;
                _ptr2State[i+j*_Nx+_Nz-1] = _surfaceTemperature;
               }
           }

};
#endif