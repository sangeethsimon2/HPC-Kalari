/* Implementation class for VTK writer that inherits from the VTKWriter class*/
#ifndef _STRUCTUREDVTKWRITER_H
#define _STRUCTUREDVTKWRITER_H

#include "VTKWriter.hpp"
#include <iostream>

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
        void writeVTK(){
         std::cout<<"Writing structured VTK files"<<std::endl;
        }
};
#endif