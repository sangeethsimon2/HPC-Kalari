/*Class that manages Input-Output operations. The template type is the type of writer*/
#ifndef _IOManager_H
#define _IOManager_H

template<typename T>
class IOManager {
public:
    IOManager() : vtkWriter(new T()) {}

    ~IOManager() {
        delete vtkWriter;
    }

    void writeOutput() {
        vtkWriter->writeVTK();
    }

    void setParameter(const std::shared_ptr<parameters> _param) {
        vtkWriter->setParameter(_param);
    }

    void setState(const std::shared_ptr<State> _state) {
        vtkWriter->setState(_state);
    }

private:
    T* vtkWriter;

};

#endif