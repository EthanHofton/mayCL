#ifndef buffer_hpp
#define buffer_hpp

#include "context.hpp"

namespace mayCL
{
    class Buffer
    {
    public:

        Buffer(cl_context t_context, cl_mem_flags t_memMode, void *t_data, unsigned int t_dataSize);
        ~Buffer();

        void bufferWrite();
        void bufferRead();

        template<typename T>
        inline T* getBufferDataAs() { return (T*)m_data; }
        inline void* getBufferData() { return m_data; }

    private:

        cl_mem m_buffer;
        void *m_data;
        unsigned int m_dataSize;
        cl_mem_flags m_memMode;
        cl_context m_context;
    };
}

#endif