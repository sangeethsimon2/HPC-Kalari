/*Class that creates an IOManager objects through a factory method*/

#ifndef _IOMANAGERFACTORY_H
#define _IOMANAGERFACTORY_H

#include<memory>
#include "IOManager.hpp"
#include "VTKWriter.hpp"
#include "structuredVTKWriter.hpp"

class IOManagerFactory {
public:
    static IOManager<VTKWriter>* createIOManager(const std::shared_ptr<parameters> param) {
        IOManager<VTKWriter>* ioManager = nullptr;
        if (param->getOutputType() == "vtk") {
            if (param->getVTKFormatType() == "structured") {
                ioManager = new IOManager<StructuredVTKWriter>();
            } else if (param->getVTKFormatType() == "unstructured") {
                throw std::runtime_error("Unstructured VTK files are not supported yet");
            }
        }
        // Add more output types here as needed
        return ioManager;
    }
};

#endif