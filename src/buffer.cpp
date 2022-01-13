#include <mayCL/buffer.hpp>

namespace mayCL
{
    Buffer::Buffer(Context &t_context, cl_mem_flags t_memMode, unsigned int t_dataSize)
    {
        m_context = &t_context;
        m_memMode = t_memMode;
        m_dataSize = t_dataSize;
        m_dataBuffer = (void *)(new char[m_dataSize]);

        m_buffer = clCreateBuffer(m_context->getContext(), m_memMode, m_dataSize, NULL, NULL);
    }

    Buffer::~Buffer() {}

    void Buffer::bufferWrite(CommandQueue t_queue, void *t_writeData)
    {
        clEnqueueWriteBuffer(t_queue.getQueue(), m_buffer, CL_FALSE, 0, m_dataSize, t_writeData, 0, NULL, NULL);
    }

    void Buffer::bufferRead(CommandQueue t_queue)
    {
        clEnqueueReadBuffer(t_queue.getQueue(), m_buffer, CL_FALSE, 0, m_dataSize, m_dataBuffer, 0, NULL, NULL);
    }
}