/*Class that implements the jacobi method interface with a serial algorithm*/
/*This class represents the specific 'strategy' and
participates in the strategy design pattern by interacting with its
base class, the kernel class and the main()*/

#ifndef _JACOBIIMPL_H
#define _JACOBIIMPL_H

#include<iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include "jacobiInterface.hpp"

template<int DIM>
class JacobiSerialImpl: public JacobiInterface{

    public:
           //Member that stores the accumulated error per iteration
            static double accumulatedErrorPerTimeStep;
           //CTOR
           JacobiSerialImpl(int _Nx=0, int _Ny=0, int _Nz=0, double _dt=0, double _thermalCoeff=0):
             m_Nx(_Nx), m_Ny(_Ny), m_Nz(_Nz), m_dt(_dt), m_thermalCoeff(_thermalCoeff){
              processAndStoreComputationCoefficients();
              std::cout<<" Finished setting up JacobiSerial Kernel\n";
             }

           //Method to compute some kernel parameters
           void processAndStoreComputationCoefficients();

           //Method that implements the jacobi kernel
           void updateSolution(double*, double*);

          private:
                 int m_Nx, m_Ny, m_Nz;
                 double m_dt;
                 double m_thermalCoeff;

                 //Derived coefficients to render the computations less flops
                 double m_diagx=0., m_diagy=0., m_diagz=0.;
                 double m_weightx=0., m_weighty=0., m_weightz=0.;

                 double errorAtEachPoint=0;
};


#endif