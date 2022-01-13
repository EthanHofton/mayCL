#include <mayCL/support.hpp>

namespace mayCL
{
    cl_device_id chooseDeviceID()
    {
        // get a list of devices
        cl_uint deviceCount;
        clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);

        cl_device_id *devices = new cl_device_id[deviceCount];
        clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // desplay device list
        char buff[128];
        for (int i = 0; i < deviceCount; i++)
        {
            clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 128, buff, NULL);
            std::cout << "(" << i << "): device " + std::string(buff) << " supports ";

            clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, 128, buff, NULL);
            std::cout << std::string(buff) << std::endl;
        }

        std::cout << "enter the number of the device you would like to use> ";
        std::string choice;
        while (true)
        {
            
            std::cin >> choice;

            if (std::stoi(choice) < deviceCount)
            {
                break;
            }
            std::cout << "invalid input. Please try again> ";
        }

        return devices[std::stoi(choice)];
    }

    cl_device_id chooseDeviceID(unsigned int t_index)
    {
        // get a list of devices
        cl_uint deviceCount;
        clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);

        cl_device_id *devices = new cl_device_id[deviceCount];
        clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        return devices[t_index];
    }

    std::string getKernelSource(std::string filepath)
    {
        std::ifstream source;
        source.open("kernels/" + filepath, std::ios::in);

        assert(source.is_open());

        std::string kernal = "";
        std::string line;
        while (getline(source, line))
        {
            kernal += line + "\n";
        }

        return kernal;
    }

    std::vector<std::string> getKernelNames(std::string filepath)
    {
        std::ifstream source;
        source.open("kernels/" + filepath, std::ios::in);

        assert(source.is_open());

        std::vector<std::string> kernalNames;
        std::string line;
        while (getline(source, line))
        {
            if (line.find("kernel void") != std::string::npos)
            {
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                std::size_t namePos = line.find("kernelvoid");
                line = line.substr(namePos + std::string("kernelvoid").size());
                std::size_t bracketPos = line.find("(");
                if (bracketPos != std::string::npos)
                {
                    std::string kernalName = line.substr(0, bracketPos);
                    kernalNames.push_back(kernalName);
                }
            }
        }

        return kernalNames;
    }
}