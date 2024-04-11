/*Implementation for the methods in the dirichlet boundary type class*/
#include "dirichletBoundaryTypeImpl.hpp"

template<int DIM>
void DirichletImpl<DIM>::updateBoundaries(double* _ptr2State, int _Nx, int _Ny, int _Nz, double _surfaceTemperature){
   if constexpr(DIM==2){
      //Set surface temperature for all faces intersecting the x axis  at i=0 & i=Nx-1:
      //These constitute the Left and Right boundaries of the domain
      for(int j=0;j<_Ny;j++){
        _ptr2State[j*_Nx] = _surfaceTemperature;
        _ptr2State[(_Nx-1)+j*_Nx] = _surfaceTemperature;
      }
      //Set surface temperature for all faces intersecting the y axis at j=0 & j=Ny-1:
      //These constitute the Top and Bottom boundaries of the domain
      for(int i=0;i<_Nx;i++){
        _ptr2State[i] = _surfaceTemperature;
        _ptr2State[i+(_Ny-1)*_Nx] = _surfaceTemperature;
      }
    }
    else if constexpr(DIM==3){
    //Set surface temperature for all faces intersecting the x axis  at i=0 & i=Nx-1:
    //These constitute the Left and Right boundaries of the domain
      for(int k=0;k<_Nz;k++){
        for(int j=0;j<_Ny;j++){
            _ptr2State[j*_Nx+k*_Nx*_Ny] = _surfaceTemperature;
            _ptr2State[(_Nx-1)+j*_Nx+k*_Nx*_Ny] = _surfaceTemperature;
        }
      }
    //Set surface temperature for all faces intersecting the y axis at j=0 & j=Ny-1:
    //These constitute the Top and Bottom boundaries of the domain
      for(int k=0;k<_Nz;k++){
        for(int i=0;i<_Nx;i++){
            _ptr2State[i+k*_Nx*_Ny] = _surfaceTemperature;
            _ptr2State[i+(_Ny-1)*_Nx+k*_Nx*_Ny] = _surfaceTemperature;
        }
      }
      //TODO: DO this only for 3D cases
      //Set surface temperature for all faces intersecting the z axis at k=0 & k=Nz-1:
      //These constitute the Front and Back boundaries of the domain
        for(int j=0;j<_Ny;j++){
          for(int i=0;i<_Nx;i++){
             _ptr2State[i+j*_Nx] = _surfaceTemperature;
             _ptr2State[i+j*_Nx+(_Nz-1)*_Nx*_Ny] = _surfaceTemperature;
          }
        }
    }
    else
        throw std::runtime_error("Dimensionality in dirichlet boundary must be 2 or 3!");
  }

template class DirichletImpl<2>;
template class DirichletImpl<3>;