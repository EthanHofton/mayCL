#include <mayCL/program.hpp>

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
            std::cout << "program not created. Error" << std::endl; 
            assert(m_program == NULL);
        }

        auto programBuildStatus = clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
        if (programBuildStatus != CL_SUCCESS)
        {
            std::cout << "program build failed. Error" << std::endl;
            assert(programBuildStatus == CL_SUCCESS);
        }

    }
}