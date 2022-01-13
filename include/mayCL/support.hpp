#ifndef support_hpp
#define support_hpp

#include <OpenCL/opencl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

namespace mayCL
{
    cl_device_id chooseDeviceID();
    cl_device_id chooseDeviceID(unsigned int t_index);

    std::string getKernelSource(std::string filepath);
    std::vector<std::string> getKernelNames(std::string filepath);
}

#endif