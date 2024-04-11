/*Abstract class that will be inherited by the base writer classes (like vtk writer or csv writer)*/

#ifndef _WRITER_H
#define _WRITER_H

#include<memory>

#include<parameterObject.hpp>
#include<state.hpp>


class Writer{
    public:
          //Default CTOR
           Writer()=default;
           //Delete copy CTOR
           Writer(Writer& writer) = delete;
           //Delete assigment CTOR
           Writer& operator =(const Writer&) = delete;
           //Virtual destructor
           virtual ~Writer() = default;

           //Virtual method to write files(overrriden by specific writers)
           virtual void writeFile() = 0;

           //Setter method for the shared pointer to the parameter object
           void setParameter(const std::shared_ptr<parameters> _parameters){m_ptr2Parameters = _parameters;}
           //Setter method for the shared pointer to the state object
           void setState(const std::shared_ptr<State> _state){m_ptr2State = _state;}

           //Getter method for the shared pointer to the parameter object
           std::shared_ptr<parameters> getPtr2Parameters() const {return m_ptr2Parameters;}
           //Getter method for the shared pointer to the state object
           std::shared_ptr<State> getPtr2State() const {return m_ptr2State;}

     protected:
            std::shared_ptr<parameters> m_ptr2Parameters;
            std::shared_ptr<State>      m_ptr2State;
};

#endif