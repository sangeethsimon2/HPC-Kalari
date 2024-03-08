/* A class & helper functions that handles the parameter related activities of this code*/
/* Implements the Singleton design pattern */
#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include<string>
#include<fstream>
#include<sstream>
#include<cassert>
#include<iostream>

class parameters{
public:
          //Delete copy CTOR
          parameters(parameters& param) = delete;

          //Delete assigment CTOR
          void operator =(const parameters&) = delete;

          //Interface function that calls the CTOR
          static parameters* getInstance(const std::string& fileName);

          //Static interface method to instantiate a static object of this class
          //static void loadParameters();

          //A file reader function
          void readParameterFile(const std::string& fileName);

          // Getter functions
          int getDimensionality();
          float getDomainLength(std::string direction);
          int getGridSize(std::string direction);
          int getTotalGridSize();
          float getConductivityCoeff();
          float getConvergenceTolerance();

          //A function to check for correctness of the provided parameters
          void checkParameters();
          // A function to print the parameters that have been read and filled
          void printParameters();
          // A method to compute additional parameters from the input data
          void computeAdditionalParameters();
protected:
          //Static instance filled by the CTOR
          static parameters* m_uniqueParameterInstance;

          //CTOR
          parameters(const std::string& fileName){
            //Call function to read the parameter file
            readParameterFile(fileName);
            //Call function to check for parameter correctness
            checkParameters();
            //Compute parameters (totalGridSize...)
            computeAdditionalParameters();
            // TODO:  Mask with a IFDEBUG flag
            printParameters();
          }

private:
        int m_dimensionality;
        float m_domainX, m_domainY, m_domainZ;
        int m_Nx, m_Ny, m_Nz, m_totalGridSize;
        float m_conductivityCoeff;
        float m_convergenceTolerance;
};


#endif