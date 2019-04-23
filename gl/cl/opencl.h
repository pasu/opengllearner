#include "CL/cl.h"
#include "CL/cl_gl_ext.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Buffer
{
public:
    enum
    {
        DEFAULT = 0,
        TEXTURE,
        TARGET
    };
    // constructor / destructor
    Buffer() : hostBuffer(0) {}
    Buffer(unsigned int N, unsigned int t = DEFAULT, void* ptr = 0);
    ~Buffer();
    cl_mem* GetDevicePtr() { return &deviceBuffer; }
    unsigned int* GetHostPtr() { return hostBuffer; }
    void CopyToDevice(bool blocking = true);
    void CopyFromDevice(bool blocking = true);
    void CopyTo(Buffer* buffer);
    void Clear();
    void Read(void* dst);
    void Write(void* dst);
    // data members
    cl_mem deviceBuffer, pinnedBuffer;
    unsigned int* hostBuffer;
    unsigned int type, size, textureID;
    bool ownData;
};

class Kernel
{
public:
    // constructor / destructor
    Kernel(const char* file, const char* entryPoint);
    ~Kernel();
    // get / set
    cl_kernel& GetKernel() { return kernel; }
    static cl_command_queue& GetQueue() { return queue; }
    static cl_context& GetContext() { return context; }
    static cl_device_id& GetDevice() { return device; }
    // methods
    void Run();
    void Run(cl_mem* buffers, int count = 1);
    void Run(Buffer* buffer);
    void Run(const size_t count);
    void SetArgument(int idx, cl_mem* buffer);
    void SetArgument(int idx, Buffer* buffer);
    void SetArgument(int idx, float);
    void SetArgument(int idx, int);
    void SetArgument(int idx, vec2);
    void SetArgument(int idx, vec3);
    void SetArgument(int idx, vec4);
    bool InitCL();
private:
    // data members
    cl_kernel kernel;
    cl_mem vbo_cl;
    cl_program program;
    static bool clinitialized;
    static cl_device_id device;
    static cl_context context; // simplifies some things, but limits us to one device
    static cl_command_queue queue;
    static char* log;
public:
    static bool candoInterop;
};