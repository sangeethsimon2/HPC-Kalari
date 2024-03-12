#include "parameterObject.hpp"
// Definition of the static member
parameters* parameters::m_uniqueParameterInstance = nullptr;

//Implementation of the file reading method that is called from the CTOR
void parameters::readParameterFile(const std::string& fileName)
{
	std::ifstream dataFile (fileName);
	std::string data, comment, line;

	while (	std::getline(dataFile, line))
		{
			std::istringstream(line)>>comment>>data;
			if(comment=="dimensionality")
				m_dimensionality=std::stoi(data);
			else if(comment=="domainLengthX")
				m_domainX=std::stof(data);
            else if(comment=="domainLengthY")
				m_domainY=std::stof(data);
            else if(comment=="domainLengthZ")
				m_domainZ=std::stof(data);
			else if(comment=="Nx")
				m_Nx=std::stoi(data);
            else if(comment=="Ny")
				m_Ny=std::stoi(data);
            else if(comment=="Nz")
				m_Nz=std::stoi(data);
			else if(comment=="conductivityCoeff")
				m_conductivityCoeff=std::stof(data);
      else if(comment=="convergenceTol")
				m_convergenceTolerance=std::stof(data);
		}
	dataFile.close();


	//Output the parameters to user
//	std::cout<<"The parameters that were read in are:\n";
//	std::cout<<"Length="<<p._L<<", Num of cells="<<p._N<<", CFL="<<p._cfl<<", tmax="<<p._tmax<<", wavespeed="<<p._A<<", Max iterations="<<p._itmax<<"\n";
}

// Implementation of the getInstance method that calls the CTOR
parameters* parameters::getInstance(const std::string& fileName)
{
    if(parameters::m_uniqueParameterInstance==nullptr){
        parameters::m_uniqueParameterInstance = new parameters(fileName);
    }
    return parameters::m_uniqueParameterInstance;
}

//Implement the getter functions
int parameters::getDimensionality(){return(m_dimensionality);}
float parameters::getDomainLength(std::string direction){
    if(direction=="x")
      {return(m_domainX);}
    else if (direction=="y")
      {return(m_domainY);}
    else if (direction=="z")
      {return(m_domainZ);}
    else
      {std::cout<<" Direction not recognized"; abort();}
}
int parameters::getGridSize(std::string direction){
    if(direction=="x")
      {return(m_Nx);}
    else if (direction=="y")
      {return(m_Ny);}
    else if (direction=="z")
      {return(m_Nz);}
    else
      {std::cout<<" Direction not recognized"; abort();}
}

float parameters::getConductivityCoeff(){return(m_conductivityCoeff);}
float parameters::getConvergenceTolerance(){return(m_convergenceTolerance);}
int parameters::getTotalGridSize(){return(m_totalGridSize);}
float parameters::getGridSpacing(std::string direction){
    if(direction=="x")
      {return(m_dx);}
    else if (direction=="y")
      {return(m_dy);}
    else if (direction=="z")
      {return(m_dz);}
    else
      {std::cout<<" Direction not recognized"; abort();}
}
float parameters::getTimeStep(){return(m_dt);}

// Implementation of the method to check the correctness of the parameters
void parameters::checkParameters(){
    //Assert section for logic checking
    assert((getDimensionality()==2 || getDimensionality()==3) && "Dimensionality supported are only 2 or 3");
    assert((getConductivityCoeff()>0) && "Thermal conductivity cannot be negative" );
    assert((getDomainLength("x")>=0) && " X domain length cannot be negative");
    assert((getDomainLength("y")>=0) && " Y domain length cannot be negative");
    assert((getDomainLength("z")>=0) && " Z domain length cannot be negative");
    assert((getGridSize("x")>0) && " Number of grid points in X cannot be negative or 0");
    assert((getGridSize("y")>0) && " Number of grid points in Y cannot be negative or 0");
    assert((getGridSize("z")>0) && " Number of grid points in Z cannot be negative or 0");
    assert((getConvergenceTolerance()>0) && "Convergence tolerance must be >0");
    if(getDimensionality()==2)
      assert((getGridSize("z")==1) && "For 2D problems, number of Z directional cells must be 1");

 }

void parameters::printParameters(){
  std::cout<<"The parameters read from the file are:\n";
  std::cout<<" Dimensionality ="<<getDimensionality()<<std::endl;
  std::cout<<" Domain length in X ="<<getDomainLength("x")<<std::endl;
  std::cout<<" Domain length in Y ="<<getDomainLength("y")<<std::endl;
  std::cout<<" Domain length in Z ="<<getDomainLength("z")<<std::endl;
  std::cout<<" Number of grid points in X ="<<getGridSize("x")<<std::endl;
  std::cout<<" Number of grid points in Y ="<<getGridSize("y")<<std::endl;
  std::cout<<" Number of grid points in Z ="<<getGridSize("z")<<std::endl;
  std::cout<<" Thermal Conductivity coefficient ="<<getConductivityCoeff()<<std::endl;
  std::cout<<" The convergence tolerance ="<<getConvergenceTolerance()<<std::endl;
  }

void parameters::computeAdditionalParameters(){
  //Compute total grid size
  m_totalGridSize = m_Nx*m_Ny*m_Nz;
  assert((m_totalGridSize!=0) && "Total Grid Size cannot be 0");

  //Compute dx, dy and dz
  m_dx = (float)m_domainX/m_Nx;
  assert((m_dx>=0.) && " Grid spacing in X cannot be negative");

  m_dy = (float)m_domainY/m_Ny;
  assert((m_dy>=0.) && " Grid spacing in Y cannot be negative");

  m_dz = (float)m_domainZ/m_Nz;
  assert((m_dz>=0.) && " Grid spacing in Z cannot be negative");

  //Compute time step according to CFL stability criterion
  m_dt = (1.0/4.0 * getConductivityCoeff()) * (getDimensionality() == 2 ?
  std::min(m_dx * m_dx, m_dy * m_dy) : std::min(std::min(m_dx * m_dx, m_dy * m_dy), m_dz * m_dz));
  assert((m_dt>0.) && "Computed time step must be >0");
}
