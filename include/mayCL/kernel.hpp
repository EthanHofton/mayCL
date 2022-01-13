#ifndef kernel_hpp
#define kernel_hpp

#include "program.hpp"
#include "buffer.hpp"
#include "commandQueue.hpp"

#include <glm/glm.hpp>

namespace mayCL
{
    class Kernel
    {
    public:
        
        Kernel(Program &t_program, std::string kernelName);
        ~Kernel() = default;

        void setArg(unsigned int t_argIndex, Buffer &t_argVal);

        void enqueue(CommandQueue &t_queue, unsigned int t_workDim, glm::vec3 t_globalDim, glm::vec3 t_localDim);

        inline cl_kernel& getKernel() { return m_kernel; }

    private:

        cl_kernel m_kernel;
        Program *m_program;
    };
}

#endif