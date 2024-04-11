/* Implementation class for VTK writer that inherits from the VTKWriter class*/
#ifndef _STRUCTUREDVTKWRITER_H
#define _STRUCTUREDVTKWRITER_H

#include "VTKWriter.hpp"
#include <iostream>
#include <fstream>

class StructuredVTKWriter : public VTKWriter{

    public:
        //Default CTOR
        StructuredVTKWriter()=default;
        //Delete copy CTOR
        StructuredVTKWriter(StructuredVTKWriter& vtkwriter) = delete;
        //Delete assigment CTOR
        StructuredVTKWriter& operator =(const StructuredVTKWriter&) = delete;
        //Virtual destructor
        ~StructuredVTKWriter() = default;

        // Method to write structured grid format vtk files
        void writeFile()final {
         std::cout<<"Writing structured VTK files"<<std::endl;

         //Open a file to write
         std::ofstream out( "temp.vtk" );
         //Retrieve the parameters and state pointers
         auto const ptr2Params = getPtr2Parameters();
         auto const ptr2State = getPtr2State();
         if(ptr2Params->getDimensionality() ==2){
            int Nx = ptr2Params->getGridSize("x");
            int Ny = ptr2Params->getGridSize("y");
            double dx = ptr2Params->getGridSpacing("x");
            double dy = ptr2Params->getGridSpacing("y");
            int N = Nx * Ny;

            out << "# vtk DataFile Version 3.0\n";
            out << "Test file\n";
            out << "ASCII\n";

            out << "DATASET STRUCTURED_GRID\n";
            out << "DIMENSIONS " << ' ' << Nx << ' ' << Ny << ' ' << 1<< '\n';
            out << "POINTS " << N << " double\n";
            for(int j=0; j<Ny; j++){
                for(int i=0; i<Nx; i++){
                    out<< i*dx << " " << j*dy << " " << 0.0 << '\n';
                }
            }

            out << "POINT_DATA " << N << '\n';
            out << "SCALARS pressure double 1\n";
            out << "LOOKUP_TABLE default\n";
            for ( int i = 0; i < N; i++ )
              out << ptr2State->getStateAtPoint(i) << '\n';

         }
         if(ptr2Params->getDimensionality() ==3){
            int Nx = ptr2Params->getGridSize("x");
            int Ny = ptr2Params->getGridSize("y");
            int Nz = ptr2Params->getGridSize("z");
            double dx = ptr2Params->getGridSpacing("x");
            double dy = ptr2Params->getGridSpacing("y");
            double dz = ptr2Params->getGridSpacing("z");
            int N = Nx * Ny * Nz;

            out << "# vtk DataFile Version 3.0\n";
            out << "Test file\n";
            out << "ASCII\n";

            out << "DATASET STRUCTURED_GRID\n";
            out << "DIMENSIONS " << ' ' << Nx << ' ' << Ny << ' ' << Nz<< '\n';
            out << "POINTS " << N << " double\n";
            for(int k=0; k<Nz; k++){
              for(int j=0; j<Ny; j++){
                for(int i=0; i<Nx; i++){
                    out<< i*dx << " " << j*dy << " " << k*dz << '\n';
                }
              }
           }

            out << "POINT_DATA " << N << '\n';
            out << "SCALARS temperature double 1\n";
            out << "LOOKUP_TABLE default\n";
            for ( int i = 0; i < N; i++ )
              out << ptr2State->getStateAtPoint(i) << '\n';

         }

        }
};
#endif