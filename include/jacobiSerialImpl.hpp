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
           void updateSolution(){
            std::cout<<" Called serial implementation\n";
           }

};


#endif