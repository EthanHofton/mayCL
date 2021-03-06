#include <mayCL/commandQueue.hpp>
#include <mayCL/logger.hpp>

namespace mayCL
{
    CommandQueue::CommandQueue(Context &t_context, Device &t_device)
    {
        m_context = &t_context;
        m_device = &t_device;
        m_queue = clCreateCommandQueue(m_context->getContext(), m_device->getDeviceId(), (cl_command_queue_properties)0, NULL);
        CORE_INFO("Command queue created");
    }

    void CommandQueue::wait()
    {
        CORE_INFO("waiting for command queue to finish...");
        clFinish(m_queue);
    }
}