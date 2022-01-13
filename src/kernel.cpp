#include <mayCL/kernel.hpp>

namespace mayCL
{
    Kernel::Kernel(Program &t_program, std::string kernelName)
    {
        m_program = &t_program;
        clCreateKernel(m_program->getProgram(), kernelName.c_str(), NULL);
    }

    void Kernel::setArg(unsigned int t_argIndex, Buffer &t_argVal)
    {
        clSetKernelArg(m_kernel, t_argIndex, t_argVal.getDataSize(), &t_argVal.getBuffer());
    }
}