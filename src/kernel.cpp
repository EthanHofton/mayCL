#include <mayCL/kernel.hpp>
#include <mayCL/logger.hpp>

namespace mayCL
{
    Kernel::Kernel(Program &t_program, std::string t_kernelName)
    {
        m_program = &t_program;
        cl_int errorCode;
        m_kernel = clCreateKernel(m_program->getProgram(), t_kernelName.c_str(), &errorCode);

        if (errorCode != CL_SUCCESS)
        {
            std::string errorMsg;
            switch (errorCode)
            {
            case CL_INVALID_PROGRAM:
                errorMsg = "program is not a valid program object";
                break;
            case CL_INVALID_PROGRAM_EXECUTABLE:
                errorMsg = "there is no successfully built executable for program";
                break;
            case CL_INVALID_KERNEL_NAME:
                errorMsg = "kernel_name is not found in program";
                break;
            case CL_INVALID_KERNEL_DEFINITION:
                errorMsg = "the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built";
                break;
            case CL_INVALID_VALUE:
                errorMsg = "kernel_name is NULL";
                break;
            case CL_OUT_OF_RESOURCES:
                errorMsg = "there is a failure to allocate resources required by the OpenCL implementation on the device";
                break;
            case CL_OUT_OF_HOST_MEMORY:
                errorMsg = "there is a failure to allocate resources required by the OpenCL implementation on the host";
                break;
            default:
                errorMsg = "could not create kernel";
                break;
            }

            CORE_CRITICAL("Could not create Kernel: {}", errorMsg);
            assert(errorCode == CL_SUCCESS);
        }
    }

    void Kernel::setArg(unsigned int t_argIndex, Buffer &t_argVal)
    {
        clSetKernelArg(m_kernel, t_argIndex, sizeof(t_argVal.getBuffer()), &(t_argVal.getBuffer()));
        CORE_INFO("Kenrel arguments set");
    }

    void Kernel::enqueue(CommandQueue &t_queue, unsigned int t_workDim, glm::vec3 t_globalDim, glm::vec3 t_localDim)
    {
        size_t globalWorkDim[] = {(size_t)t_globalDim.x, (size_t)t_globalDim.y, (size_t)t_globalDim.z};
        size_t localWorkDim[] = {(size_t)t_localDim.x, (size_t)t_localDim.y, (size_t)t_localDim.z};
        
        clEnqueueNDRangeKernel(t_queue.getQueue(), m_kernel, t_workDim, NULL, globalWorkDim, localWorkDim, 0, NULL, NULL);
        CORE_INFO("Kerenl added to command queue with global dimentions ({}, {}, {}) and local dimentions ({}, {}, {}) and {} work dimetions", t_globalDim.x, t_globalDim.y, t_globalDim.z, t_localDim.x, t_localDim.y, t_localDim.z, t_workDim);
    }
}