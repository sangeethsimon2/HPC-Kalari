/*Class that manages Input-Output operations. The template type is the type of writer*/
#ifndef _IOManager_H
#define _IOManager_H

#include "writer.hpp"
#include "structuredVTKWriter.hpp"

class IOManager {
public:
    IOManager() : m_Writer() {}

    IOManager(std::shared_ptr<Writer> _structuredvtkwriter) : m_Writer(_structuredvtkwriter) {}

    void writeOutput() {
        m_Writer->writeFile();
    }

    void setParameter(const std::shared_ptr<parameters> _param) {
        m_Writer->setParameter(_param);
    }

    void setState(const std::shared_ptr<State> _state) {
        m_Writer->setState(_state);
    }

private:
    std::shared_ptr<Writer> m_Writer = nullptr;

};

#endif