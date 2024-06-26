/*Implements the jacobi serial class methods*/

#include "jacobiSerialImpl.hpp"
template<int DIM>
double JacobiSerialImpl<DIM>::accumulatedErrorPerTimeStep=0.;

template<int DIM>
void JacobiSerialImpl<DIM>::processAndStoreComputationCoefficients(){
              if constexpr (DIM==2){
                m_diagx = -2.0 + m_Nx*m_Nx/(2.*m_thermalCoeff*m_dt);
                m_diagy = -2.0 + m_Ny*m_Ny/(2.*m_thermalCoeff*m_dt);

                m_weightx = m_thermalCoeff * m_dt/(m_Nx*m_Nx);
                m_weighty = m_thermalCoeff * m_dt/(m_Ny*m_Ny);
              }
              if constexpr (DIM==3){
                m_diagx = -2.0 + m_Nx*m_Nx/(2.*m_thermalCoeff*m_dt);
                m_diagy = -2.0 + m_Ny*m_Ny/(2.*m_thermalCoeff*m_dt);
                m_diagz = -2.0 + m_Nz*m_Nz/(2.*m_thermalCoeff*m_dt);

                m_weightx = m_thermalCoeff * m_dt/(m_Nx*m_Nx);
                m_weighty = m_thermalCoeff * m_dt/(m_Ny*m_Ny);
                m_weightz = m_thermalCoeff * m_dt/(m_Nz*m_Nz);
              }
           }


// Implement first order FD stencil scheme (derivative approx by 3-point stencil)
template<int DIM>
void JacobiSerialImpl<DIM>::updateSolution(double* _ptr2SolutionInitial, double* _ptr2SolutionUpdated){
            //std::cout<<" Begin computing the kernel\n";
            if constexpr (DIM==2){
                for(int j=1;j<m_Ny-1;j++){
                  for(int i=1;i<m_Nx-1;i++){
                    _ptr2SolutionUpdated[i+j*m_Nx] =
                        m_weightx*(_ptr2SolutionInitial[(i-1)+j*m_Nx]
                      + _ptr2SolutionInitial[(i+1)+j*m_Nx]
                      + _ptr2SolutionInitial[i+j*m_Nx]*m_diagx)

                      + m_weighty*(_ptr2SolutionInitial[i+(j-1)*m_Nx]
                      + _ptr2SolutionInitial[i+(j+1)*m_Nx]
                      + _ptr2SolutionInitial[i+j*m_Nx]*m_diagy);
                    }
                }
              //Accumulate error
              accumulatedErrorPerTimeStep =0;

              //Compute error and Swap data
              for(int j=1;j<m_Ny-1;j++){
                for(int i=1;i<m_Nx-1;i++){
                    errorAtEachPoint = _ptr2SolutionUpdated[i+j*m_Nx] - _ptr2SolutionInitial[i+j*m_Nx];
                    accumulatedErrorPerTimeStep += fabs(errorAtEachPoint*errorAtEachPoint);
                    //Copy arrays
                    //TODO: Would a operator overloading in the state class be an efficient option?
                    //OR would using std::swap() be a good option?
                    //OR would a simple loop based element-by-element copy be a good option?
                    _ptr2SolutionInitial[i+j*m_Nx] = _ptr2SolutionUpdated[i+j*m_Nx];
                }
              }
            }
            else if constexpr (DIM==3){
              for(int k=1;k<m_Nz-1;k++){
                for(int j=1;j<m_Ny-1;j++){
                  for(int i=1;i<m_Nx-1;i++){
                    _ptr2SolutionUpdated[i+j*m_Nx+k*m_Nx*m_Ny] =
                        m_weightx*(_ptr2SolutionInitial[(i-1)+j*m_Nx+k*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[(i+1)+j*m_Nx+k*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny]*m_diagx)

                      + m_weighty*(_ptr2SolutionInitial[i+(j-1)*m_Nx+k*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[i+(j+1)*m_Nx+k*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny]*m_diagy)

                      + m_weightz*(_ptr2SolutionInitial[i+j*m_Nx+(k-1)*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[i+j*m_Nx+(k+1)*m_Nx*m_Ny]
                      + _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny]*m_diagz);
                  }
                }
              }
              //Accumulate error
              accumulatedErrorPerTimeStep =0;

              //Compute error and Swap data
              for(int k=1;k<m_Nz-1;k++){
                for(int j=1;j<m_Ny-1;j++){
                  for(int i=1;i<m_Nx-1;i++){
                    errorAtEachPoint = _ptr2SolutionUpdated[i+j*m_Nx+k*m_Nx*m_Ny] - _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny];
                    //std::cout<<" Error At Each point="<<errorAtEachPoint<<"\n";
                    accumulatedErrorPerTimeStep += fabs(errorAtEachPoint*errorAtEachPoint);
                    //Copy arrays
                    //TODO: Would a operator overloading in the state class be an efficient option?
                    //OR would using std::swap() be a good option?
                    //OR would a simple loop based element-by-element copy be a good option?
                    _ptr2SolutionInitial[i+j*m_Nx+k*m_Nx*m_Ny] = _ptr2SolutionUpdated[i+j*m_Nx+k*m_Nx*m_Ny];
                  }
                }
               }
              //std::cout<<"accumulatedErrorPerTimeStep="<<accumulatedErrorPerTimeStep<<"\n";
            }
            else{
              throw std::runtime_error("Invalid dimensionality in kernel\n");
            }
            //TODO print statements should go under ifdebug flag
            //std::cout<<" Finished computing the kernel\n";
}

template class JacobiSerialImpl<2>;
template class JacobiSerialImpl<3>;