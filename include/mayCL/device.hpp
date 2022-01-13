#ifndef device_hpp
#define device_hpp

#include "support.hpp"

namespace mayCL
{
    class Device
    {
    public:

        Device(cl_device_id t_id);
        ~Device() = default;

        inline cl_device_id& getDeviceId() { return m_deviceId; }

    private:

        cl_device_id m_deviceId;
    };
}

#endif