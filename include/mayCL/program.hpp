#ifndef program_hpp
#define program_hpp

#include "context.hpp"

namespace mayCL
{
    class Program
    {
    public:

        Program(Context &t_context, std::string t_kernelFileName);
        ~Program() = default;

        inline cl_program &getProgram() { return m_program; }

    private:

        cl_program m_program;
        std::string m_kernelFilename;
        Context *m_context;
    };
}

#endif