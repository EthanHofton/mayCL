#include <mayCL/context.hpp>
#include <mayCL/logger.hpp>

namespace mayCL
{
    Context::Context(Device **t_devices, unsigned int t_deviceCount)
    {
        m_devices = t_devices;
        m_deviceCount = t_deviceCount;

        m_deviceIds = new cl_device_id[m_deviceCount];
        for (int i = 0; i < m_deviceCount; i++)
        {
            m_deviceIds[i] = m_devices[i]->getDeviceId();
        }

        m_context = clCreateContext(NULL, m_deviceCount, m_deviceIds, NULL, NULL, NULL);

        CORE_INFO("Contexted created with {} device(s)", m_deviceCount);
    }

    Context::Context(Device &t_device)
    {
        m_deviceIds = nullptr;
        m_deviceCount = 1;
        m_context = clCreateContext(NULL, m_deviceCount, &t_device.getDeviceId(), NULL, NULL, NULL);

        CORE_INFO("Contexted created with 1 device");
    }

    Context::~Context()
    {
        if (m_deviceIds == nullptr)
        {
            delete[] m_deviceIds;
        }
    }
}