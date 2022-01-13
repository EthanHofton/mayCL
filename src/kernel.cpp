#include <mayCL/kernel.hpp>

namespace mayCL
{
    Kernel::Kernel(Program &t_program, std::string kernelName)
    {
        m_program = &t_program;
        cl_int errorCode;
        m_kernel = clCreateKernel(m_program->getProgram(), kernelName.c_str(), &errorCode);

        if (errorCode != CL_SUCCESS)
        {
            std::cout << "kenel not made. Error" << std::endl;
            switch (errorCode)
            {
            case CL_INVALID_PROGRAM:
                std::cout << "program is not a valid program object." << std::endl;
                break;
            case CL_INVALID_PROGRAM_EXECUTABLE:
                std::cout << "there is no successfully built executable for program." << std::endl;
                break;
            case CL_INVALID_KERNEL_NAME:
                std::cout << "kernel_name is not found in program." << std::endl;
                break;
            case CL_INVALID_KERNEL_DEFINITION:
                std::cout << "the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built" << std::endl;
                break;
            case CL_INVALID_VALUE:
                std::cout << "kernel_name is NULL." << std::endl;
                break;
            case CL_OUT_OF_RESOURCES:
                std::cout << "there is a failure to allocate resources required by the OpenCL implementation on the device." << std::endl;
                break;
            case CL_OUT_OF_HOST_MEMORY:
                std::cout << "there is a failure to allocate resources required by the OpenCL implementation on the host." << std::endl;
                break;
            default:
                break;
            }

            assert(errorCode == CL_SUCCESS);
        }
    }

    void Kernel::setArg(unsigned int t_argIndex, Buffer &t_argVal)
    {
        clSetKernelArg(m_kernel, t_argIndex, sizeof(t_argVal.getBuffer()), &(t_argVal.getBuffer()));
    }

    void Kernel::enqueue(CommandQueue &t_queue, unsigned int t_workDim, glm::vec3 t_globalDim, glm::vec3 t_localDim)
    {
        size_t globalWorkDim[] = {(size_t)t_globalDim.x, (size_t)t_globalDim.y, (size_t)t_globalDim.z};
        size_t localWorkDim[] = {(size_t)t_localDim.x, (size_t)t_localDim.y, (size_t)t_localDim.z};
        
        clEnqueueNDRangeKernel(t_queue.getQueue(), m_kernel, t_workDim, NULL, globalWorkDim, localWorkDim, 0, NULL, NULL);
    }
}