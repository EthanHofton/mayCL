#include <mayCL/buffer.hpp>

namespace mayCL
{
    Buffer::Buffer(cl_context t_context, cl_mem_flags t_memMode, void *t_data, unsigned int t_dataSize)
    {
        m_context = t_context;
        m_memMode = t_memMode;
        m_data = t_data;
        m_dataSize = t_dataSize;

        m_buffer = clCreateBuffer(m_context, m_memMode, m_dataSize, m_data, NULL);
    }

    Buffer::~Buffer()
    {
        
    }
}