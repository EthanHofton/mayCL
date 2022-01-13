#ifndef commandQueue_hpp
#define commandQueue_hpp

#include "context.hpp"
#include "device.hpp"

namespace mayCL
{
    class CommandQueue
    {
    public:

        CommandQueue(Context &t_context, Device &t_device);
        ~CommandQueue() = default;

        void wait();

        inline cl_command_queue &getQueue() { return m_queue; }

    private:

        Context *m_context;
        Device *m_device;
        cl_command_queue m_queue;
    };
}

#endif