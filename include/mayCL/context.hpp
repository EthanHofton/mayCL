#ifndef context_hpp
#define context_hpp

#include "device.hpp"

namespace mayCL
{
    class Context
    {
    public:

        Context(Device **t_devices, unsigned int t_deviceCount);
        Context(Device &t_device);
        ~Context();

        inline cl_context &getContext() { return m_context; }

    private:

        cl_context m_context;
        unsigned int m_deviceCount;
        Device **m_devices;
        cl_device_id *m_deviceIds;
    };
}

#endif