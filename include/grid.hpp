/*An abstract class for Grid related activities. The methods will be overriden by its children for runtime binding*/
#ifndef _GRIDCLASS_H
#define _GRIDCLASS_H


class Grid{
    public:
           //Delete copy CTOR
           Grid(Grid& grid) = delete;

           //Delete assigment CTOR
           void operator =(const Grid&) = delete;

           //CTOR
           Grid(double _domainX=1, double _domainY=1, double _domainZ=0., int _Nx=1, int _Ny=1, int _Nz=1){
                m_domainX = _domainX;
                m_domainY = _domainY;
                m_domainZ = _domainZ;

                m_Nx = _Nx;
                m_Ny = _Ny;
                m_Nz = _Nz;
            }

           //Virtual DTOR to prevent memory leaks through dangling pointers
           virtual ~Grid()=default;

           //Interfaces to override by child classes
           //Create grid
           virtual void createGrid(){};

    protected:
            double m_domainX, m_domainY, m_domainZ;
            int m_Nx, m_Ny, m_Nz;
};

#endif