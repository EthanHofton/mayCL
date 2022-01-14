#include <mayCL/device.hpp>
#include <mayCL/logger.hpp>

namespace mayCL
{
    Device::Device(cl_device_id t_id)
    {
        m_deviceId = t_id;
        CORE_INFO("Device created");

    }
}