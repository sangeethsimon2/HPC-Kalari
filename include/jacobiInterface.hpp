/* Virtual base class for all variants of jacobi solver  implementations*/
/*Part of the 'strategy design pattern' to runtime dispatch the correct
jacobi implementation based on user input*/
#ifndef _JACOBIINTERFACE_H
#define _JACOBIINTERFACE_H

class JacobiInterface{
    public:
           virtual void updateSolution()=0;
           virtual ~JacobiInterface() = default;
};

#endif