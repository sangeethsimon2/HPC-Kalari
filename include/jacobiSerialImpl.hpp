/*Class that implements the jacobi method interface with a serial algorithm*/
/*This class represents the specific 'strategy' and
participates in the strategy design pattern by interacting with its
base class, the kernel class and the main()*/

#ifndef _JACOBIIMPL_H
#define _JACOBIIMPL_H

#include<iostream>

#include "jacobiInterface.hpp"

class JacobiSerialImpl: public JacobiInterface{

    public:
           //CTOR
           JacobiSerialImpl(int _Nx=0, int _Ny=0, int _Nz=0, float _dt=0, float _thermalCoeff=0):
             m_Nx(_Nx), m_Ny(_Ny), m_Nz(_Nz), m_dt(_dt), m_thermalCoeff(_thermalCoeff){
              processAndStoreComputationCoefficients();
             }
           void processAndStoreComputationCoefficients(){
              m_diagx = -2.0 + m_Nx*m_Nx/(2.*m_thermalCoeff*m_dt);
              m_diagy = -2.0 + m_Ny*m_Ny/(2.*m_thermalCoeff*m_dt);
              m_diagz = -2.0 + m_Nz*m_Nz/(2.*m_thermalCoeff*m_dt);
              m_weightx = m_thermalCoeff * m_dt/(m_Nx*m_Nx);
              m_weighty = m_thermalCoeff * m_dt/(m_Ny*m_Ny);
              m_weightz = m_thermalCoeff * m_dt/(m_Nz*m_Nz);
           }
           // Implement first order FD stencil scheme (derivative approx by 3-point stencil)
           void updateSolution(float* _ptr2SolutionInitial=nullptr, float* _ptr2SolutionUpdated=nullptr){
             for(int k=1;k<m_Nz-1;k++)
               for(int j=1;j<m_Ny-1;j++)
                 for(int i=1;i<m_Nx-1;i++){
                   _ptr2SolutionUpdated[i+j*m_Nx+k*m_Nx*m_Ny] =
                       m_weightx*(_ptr2SolutionInitial[i-1+j*m_Nx+k*m_Nx*m_Ny]
                     + _ptr2SolutionInitial[i+1+j*m_Nx+k*m_Nx*m_Ny]
                     + _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny]*m_diagx)

                     + m_weighty*(_ptr2SolutionInitial[i+(j-1)*m_Nx+k*m_Nx*m_Ny]
                     + _ptr2SolutionInitial[i+(j+1)*m_Nx+k*m_Nx*m_Ny]
                     + _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny]*m_diagy);
                  }
            std::cout<<" Finished computing the kernel\n";
           }
          private:
                 int m_Nx, m_Ny, m_Nz;
                 float m_dt;
                 float m_thermalCoeff;

                 //Derived coefficients to render the computations less flops
                 float m_diagx=0., m_diagy=0., m_diagz=0.;
                 float m_weightx=0., m_weighty=0., m_weightz=0.;
};


#endif