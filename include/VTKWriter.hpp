/*An Abstract class that will be inherited by the children classes to write VTK files*/
#ifndef _VTKWRITER_H
#define _VTKWRITER_H

#include<memory>

#include<parameterObject.hpp>
#include<state.hpp>

class VTKWriter{
    public:
           //Default CTOR
           VTKWriter()=default;
           //Delete copy CTOR
           VTKWriter(VTKWriter& vtkwriter) = delete;
           //Delete assigment CTOR
           VTKWriter& operator =(const VTKWriter&) = delete;
           //Virtual destructor
           virtual ~VTKWriter() = default;

           //Virtual method to write VTK files(overrriden by specific Vtk format writers)
           virtual void writeVTK() = 0;

           //Setter method for the shared pointer to the parameter object
           void setParameter(const std::shared_ptr<parameters> _parameters){m_ptr2Parameters = _parameters;}
           //Setter method for the shared pointer to the state object
           void setState(const std::shared_ptr<State> _state){m_ptr2State = _state;}

    protected:
            std::shared_ptr<parameters> m_ptr2Parameters;
            std::shared_ptr<State>      m_ptr2State;

};
#endif