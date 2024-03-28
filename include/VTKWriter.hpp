/*An Abstract class that will be inherited by the children classes to write VTK files*/
#ifndef _VTKWRITER_H
#define _VTKWRITER_H

#include "writer.hpp"

class VTKWriter : public Writer {
    public:
           //Default CTOR
           VTKWriter()=default;
           //Delete copy CTOR
           VTKWriter(VTKWriter& vtkwriter) = delete;
           //Delete assigment CTOR
           VTKWriter& operator =(const VTKWriter&) = delete;
           //Virtual destructor
           virtual ~VTKWriter() = default;

           //Override the Virtual method from the writer to write VTK files(final impl by specific Vtk format writers)
           void writeFile() override{};
};
#endif