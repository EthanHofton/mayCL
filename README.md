# mayCL

OpenCL wrapper to abstract away the openCL functions

# installation

In order to install mayCL, use the following code

```bash
git clone https://github.com/EthanHofton/mayCL.git
cd mayCL
make
```

This will create a static libary, `libmayCL.a`, in `mayCL/lib/static/`. 
To use in your program, link to `mayCL/lib/static/libmayCL.a` and also add the include search path `mayCL/include` to your project

# Usage

Example Code:

```c++
#include <mayCL/mayCL.hpp>

#define DATA_LENGTH 5
#define DATA_SIZE (DATA_LENGTH*sizeof(float))

int main(int argc, char** argv)
{
    // initalize the data
    float data[DATA_LENGTH] = {0.00f, 0.25f, 0.50f, 0.75f, 1.00f};

    // display data before
    std::cout << "data before:" << std::endl;
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        std::cout << data[i] << std::endl;
    }

    // create device, context, queue and buffer
    mayCL::Device device(mayCL::chooseDeviceID());
    mayCL::Context context(device);
    mayCL::CommandQueue queue(context, device);
    mayCL::Buffer mem(context, CL_MEM_READ_WRITE, DATA_SIZE);

    // create kernel
    auto k = getKernelNames("main.clcpp");
    mayCL::Program program(context, "main.clcpp");
    mayCL::Kernel kernel(program, k[0]);

    // write data to buffer
    mem.bufferWrite(queue, (void*)data);

    // set kenerl arg
    kernel.setArg(0, mem);

    // add kernel to queue
    kernel.enqueue(queue, 1, {DATA_LENGTH, 0, 0}, {DATA_LENGTH, 0, 0});

    // read data from buffer
    mem.bufferRead(queue);

    // wait for tasks to finish before contuning with the program
    queue.wait();

    // read the return data as a list of floats from the buffer
    float *returnData = mem.getBufferDataAs<float>();

    // display returned data
    std::cout << "data after:" << std::endl;
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        std::cout << returnData[i] << std::endl;
    }

    return 0;
}
```

The example code above creates a list of float to be processed. Next it chooses a divice from a list of avalible devices and uses the chosen device
to create a context with. The program then creates a comman queue. This is a queue of OpenCL commands to be executed on. The program then creates a memory
buffer. This buffer contains the memory to be processes. We then create a a program and a kernel from that program. This kenrel is to be run for each element
in the data. We then queue a memroy write which writes the data from the origonal data list into the memory buffer, then queue the kenrel program to be run.
After this we queue a buffer read. this reads back the data from the buffer into a `void*`. we then get back the data from the memory buffer and display.

# Device

The device class stores a `cl_device_id`. The contructor takes in a `cl_device_id`. This can be provided using the native openCL functions or the device id can be found using the helper functions, `chooseDeviceID()` and `chooseDeviceID(unsigned int t_index)`.

`chooseDeviceID()` will display a list of devices in the console and wait for the user to input which device they would like to select. The function returns the seleted `cl_device_id`.

`chooseDeviceID(unsigned int t_index)` returns the `cl_device_id` at the index `t_index` from the list of devlices that would be displayed from `chooseDeviceID()`.

The Device class has memeber functions:

- `cl_device_id& getDeviceId()`. This returns the `cl_device_id`

# Context

The context class stores a `cl_context`. The constructor takes in either a `Device` or `Device **`. If the user provides just a single `Device`, the class will create a `cl_context` with a single device attached. if the user provided a `Device **`, the program will create a `cl_context` using the list of devices. Note the `Deivce **` is a list of `Device *`.

The context class has member functions:

- `cl_context &getContext()`. This reutnrs the `cl_context`

# Buffer

The buffer class stores a `cl_mem`. The contructor takes in a `Context`, `cl_mem_flags` and `unsigned int`. `cl_mem_flags` descbies if the memory is to be read, write or read/write. (See more here)[https://www.khronos.org/registry/OpenCL/sdk/2.2/docs/man/html/cl_mem_flags.html]. The `unsigned int` is the size of the memory buffer in bytes.

The buffer mas member functions:

- `void bufferWrite(CommandQueue t_queue, void *t_writeData)`. This queues a buffer write command on the command queue usning the given data `t_writeData`
- `void bufferRead(CommandQueue t_queue)`. This queues a buffer read command on the command queue. The data gets read into the Buffer class and can be retreved using one of the `getBufferData()` functions
- `template<typename T> T* getBufferDataAs()`. This returns the buffer data as a type `T*`
- `void* getBufferData()`. This returns the buffer data as `void*`
- `unsigned int getDataSize()`. This returns the size in bytes of the buffer
- `cl_mem& getBuffer()`. This returns the `cl_mem` instnace.

# CommandQueue

The command queue class stores the `cl_command_queue`. The constructor takes a `Context` and `Device`.

The CommandQueue memeber functions are:

- `void wait()`. This waits for the event queue to finish before continuing with the program
- `cl_command_queue &getQueue()`. This returns the `cl_command_queue`.

# Program

The program class stores the `cl_program`. The constructor takes in the `Context` and `std::string t_kernelFileName`. The kernel file should be located in a folder called kernels/ relative to the directorty where the final program will be run.

The Program member functions are:

- `cl_program &getProgram()`. This returns the `cl_program`

# Kenrel

The Kenrel program stores the `cl_kenrel`. The constructor takes in the `Program` and `std::string t_kernelName`. The `t_kenelName` should be the name of the kenel in the program source.

The kenrel memeber functions are:

- `void setArg(unsigned int t_argIndex, Buffer &t_argVal)`. This specifies an individual argument for the kernel function to run.
- `void enqueue(CommandQueue &t_queue, unsigned int t_workDim, glm::vec3 t_globalDim, glm::vec3 t_localDim)`. This function is what is used to add the kernel to the event queue. `t_queue` is the queue the kernel should be added too. `t_workDim` is the number of dimentions the work group has. `t_globalDim` and `t_localDim` describe how the parralisism will work. `t_globalDim` describe how many work items there will be and `t_localDim` is how many work items will be in the work groups.
- `cl_kernel& getKernel()`. This function returns the `cl_kenrel`.

# Support functions

The libary has a few support functions. They are as follows:

- `cl_device_id chooseDeviceID()`. Described above in `Device`
- `cl_device_id chooseDeviceID(unsigned int t_index)`. Described above in `Device`
- `std::string getKernelSource(std::string filepath)`. Returns the data in the file specified from the `kernels/` directory
- `std::vector<std::string> getKernelNames(std::string filepath)`. Returns all the kenrel names in the specified file (from the `kernels/` directory)
