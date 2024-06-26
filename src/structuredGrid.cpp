#include "structuredGrid.hpp"

template<int DIM>
void StructuredGrid<DIM>::computeGridSpacing(){
               //   //TODO test for exceptions here, especially NAN in spacings for wrong inputs
               //   m_dx = (double)(m_domainX/m_Nx);
               //   m_dy = (double)(m_domainY/m_Ny);
               //   if constexpr (DIM == 3)
               //     m_dz = (double)(m_domainZ/m_Nz);
}

/*The grid storage convention is x, y, z: grid(i+)*/
template<int DIM>
void StructuredGrid<DIM>::createGrid(){
                 if constexpr (DIM == 2) {
                    gridArray.resize(m_Nx * m_Ny);
                    std::cout << "resizing 2D grid array\n";

                 }
                 else if constexpr (DIM == 3) {
                    gridArray.resize(m_Nx * m_Ny * m_Nz);
                    std::cout << "resizing 3D grid array\n";
                 }
                 else {
                    throw std::invalid_argument("Invalid value of DIM");
                 }
}

// Explicit instantiation of the required template types
template class StructuredGrid<2>;
template class StructuredGrid<3>;