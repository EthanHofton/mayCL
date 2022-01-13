#ifndef buffer_hpp
#define buffer_hpp

#include "context.hpp"
#include "commandQueue.hpp"

namespace mayCL
{
    class Buffer
    {
    public:

        Buffer(Context &t_context, cl_mem_flags t_memMode, unsigned int t_dataSize);
        ~Buffer();

        void bufferWrite(CommandQueue t_queue, void *t_writeData);
        void bufferRead(CommandQueue t_queue);

        template<typename T>
        inline T* getBufferDataAs() { return (T*)m_dataBuffer; }
        inline void* getBufferData() { return m_dataBuffer; }

        inline unsigned int getDataSize() { return m_dataSize; }
        inline cl_mem& getBuffer() { return m_buffer; }

    private:

        cl_mem m_buffer;
        void *m_dataBuffer;
        unsigned int m_dataSize;
        cl_mem_flags m_memMode;
        Context *m_context;
    };
}

#endif