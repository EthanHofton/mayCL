#include <mayCL/context.hpp>

namespace mayCL
{
    Context::Context(Device *t_devices, unsigned int t_deviceCount)
    {
        m_devices = t_devices;
        m_deviceCount = t_deviceCount;

        m_deviceIds = new cl_device_id[t_deviceCount];
        for (int i = 0; i < m_deviceCount; i++)
        {
            m_deviceIds[i] = m_devices[i].getDeviceId();
        }

        m_context = clCreateContext(NULL, t_deviceCount, m_deviceIds, NULL, NULL, NULL);
    }

    Context::~Context()
    {
        delete[] m_deviceIds;
    }
}