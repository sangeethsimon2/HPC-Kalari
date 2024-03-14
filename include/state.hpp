/*A class that holds the state (Temperature) values*/
#ifndef _STATE_H
#define _STATE_H

#include<vector>
#include<memory>

class State{
    public:
          //Delete copy CTOR
          State(State& grid) = delete;

          //Delete assigment CTOR
          void operator =(const State&) = delete;

          //CTOR
          //totalSize = Nx*Ny(*Nz)
           State(int _totalSize){
            m_storage.resize(_totalSize);
            std::cout<<" Allocating memory. Flattened layout with i,j(,k) indexing\n";
          }
          //DTOR
          ~State(){
            m_storage.resize(0);
          }

          //Getter function
          float& getStateAtPoint(int index){
            return(m_storage[index]);
          }
          float* getState(){
            return(m_storage.data());
          }


    protected:
          //Underground storage array for the data (temperature)
          //Flattened array layout for multidimensional data
          //We envision that the array would be stored as a 3D array [k][j][i]
          //with i being the continuous x directional data
          //Access: For looping over elements use:
          //loop over (k):
          //  loop over (j):
          //    loop over (i):
          //       m_storage[i+j*Nx+k*Nx*Ny]
          std::vector<float> m_storage;
};

#endif