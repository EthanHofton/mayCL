#include <mayCL/program.hpp>

namespace mayCL
{
    Program::Program(Context &t_context, std::string t_kernelFileName)
    {
        m_context = &t_context;
        m_kernelFilename = t_kernelFileName;

        std::string source = getKernelSource(t_kernelFileName);
        const char *sourcecstr = source.c_str();

        m_program = clCreateProgramWithSource(t_context.getContext(), 0, &sourcecstr, NULL, NULL);
        clBuildProgram(m_program, 0, NULL, NULL, NULL, NULL);
    }
}