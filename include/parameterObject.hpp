/* A class & helper functions that handles the parameter related activities of this code*/
/* Implements the Singleton design pattern */
#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include<string>
#include<fstream>
#include<sstream>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<memory>

class parameters{
public:
          //Delete copy CTOR
          parameters(parameters& param) = delete;

          //Delete assigment CTOR
          void operator =(const parameters&) = delete;

          //Interface function that calls the CTOR
          static std::shared_ptr<parameters> getInstance(const std::string& fileName);

          //Static interface method to instantiate a static object of this class
          //static void loadParameters();

          //A file reader function
          void readParameterFile(const std::string& fileName);

          // Getter functions
          int getDimensionality();
          double getDomainLength(std::string direction);
          int getGridSize(std::string direction);
          double getConductivityCoeff();
          double getConvergenceTolerance();
          int getMaxIterations();
          int getTotalGridSize();
          double getGridSpacing(std::string direction);
          double getTimeStep();
          std::string getOutputType();
          std::string getVTKFormatType();

          //A function to check for correctness of the provided parameters
          void checkParameters();
          // A function to print the parameters that have been read and filled
          void printParameters();
          // A method to compute additional parameters from the input data
          void computeAdditionalParameters();
protected:
          //Static instance filled by the CTOR
          static std::shared_ptr<parameters> m_uniqueParameterInstance;

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
        //User input parameters
        int m_dimensionality;
        double m_domainX, m_domainY, m_domainZ;
        int m_Nx, m_Ny, m_Nz;
        double m_conductivityCoeff;
        double m_convergenceTolerance;
        int m_maxIterations;
        std::string m_outputType="vtk";
        std::string m_VTKFormatType="structured";

        //Computed parameters
        double m_totalGridSize=0.;
        double m_dt=0;
        double m_dx=0.; double m_dy=0.; double m_dz=0.;
};


#endif