#include <mayCL/device.hpp>

namespace mayCL
{
    Device::Device(cl_device_id t_id)
    {
        m_deviceId = t_id;
    }
}