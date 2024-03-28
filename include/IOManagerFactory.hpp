/*Class that creates an IOManager objects through a factory method*/

#ifndef _IOMANAGERFACTORY_H
#define _IOMANAGERFACTORY_H

#include<memory>
#include "IOManager.hpp"
#include "writer.hpp"
#include "structuredVTKWriter.hpp"

class IOManagerFactory {
public:
    static std::shared_ptr<IOManager> createIOManager(const std::shared_ptr<parameters> param) {
        std::shared_ptr<IOManager> ioManager = nullptr;
        if (param->getOutputType() == "vtk") {
            if (param->getVTKFormatType() == "structured") {
                ioManager = std::make_shared<IOManager>(std::make_shared<StructuredVTKWriter>());
            } else if (param->getVTKFormatType() == "unstructured") {
                throw std::runtime_error("Unstructured VTK files are not supported yet");
            }
        }
        // Add more output types here as needed
        return ioManager;
    }
};

#endif