#include <mayCL/program.hpp>
#include <mayCL/logger.hpp>

namespace mayCL
{
    Program::Program(Context &t_context, std::string t_kernelFileName)
    {
        m_context = &t_context;
        m_kernelFilename = t_kernelFileName;

        std::string source = getKernelSource(m_kernelFilename);
        const char *sourcecstr = source.c_str();

        cl_int errorCode;
        m_program = clCreateProgramWithSource(t_context.getContext(), 1, &sourcecstr, NULL, &errorCode);

        if (errorCode != CL_SUCCESS)
        {
            CORE_CRITICAL("Could not create program");
            assert(m_program == NULL);
        }

        auto programBuildStatus = clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
        if (programBuildStatus != CL_SUCCESS)
        {
            CORE_CRITICAL("Could not build program. Error code: {}", (int)programBuildStatus);
            assert(programBuildStatus == CL_SUCCESS);
        }

        CORE_INFO("Program created");
    }
}