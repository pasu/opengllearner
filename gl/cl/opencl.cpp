#include "pch.h"
#include "opencl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "shared.h"

using namespace std;

bool CheckCL(cl_int result, const char* file, int line)
{
    if (result == CL_SUCCESS) return true;
    if (result == CL_DEVICE_NOT_FOUND) FatalError(file, line, "Error: CL_DEVICE_NOT_FOUND", "OpenCL error");
    if (result == CL_DEVICE_NOT_AVAILABLE) FatalError(file, line, "Error: CL_DEVICE_NOT_AVAILABLE", "OpenCL error");
    if (result == CL_COMPILER_NOT_AVAILABLE) FatalError(file, line, "Error: CL_COMPILER_NOT_AVAILABLE", "OpenCL error");
    if (result == CL_MEM_OBJECT_ALLOCATION_FAILURE) FatalError(file, line, "Error: CL_MEM_OBJECT_ALLOCATION_FAILURE", "OpenCL error");
    if (result == CL_OUT_OF_RESOURCES) FatalError(file, line, "Error: CL_OUT_OF_RESOURCES", "OpenCL error");
    if (result == CL_OUT_OF_HOST_MEMORY) FatalError(file, line, "Error: CL_OUT_OF_HOST_MEMORY", "OpenCL error");
    if (result == CL_PROFILING_INFO_NOT_AVAILABLE) FatalError(file, line, "Error: CL_PROFILING_INFO_NOT_AVAILABLE", "OpenCL error");
    if (result == CL_MEM_COPY_OVERLAP) FatalError(file, line, "Error: CL_MEM_COPY_OVERLAP", "OpenCL error");
    if (result == CL_IMAGE_FORMAT_MISMATCH) FatalError(file, line, "Error: CL_IMAGE_FORMAT_MISMATCH", "OpenCL error");
    if (result == CL_IMAGE_FORMAT_NOT_SUPPORTED) FatalError(file, line, "Error: CL_IMAGE_FORMAT_NOT_SUPPORTED", "OpenCL error");
    if (result == CL_BUILD_PROGRAM_FAILURE) FatalError(file, line, "Error: CL_BUILD_PROGRAM_FAILURE", "OpenCL error");
    if (result == CL_MAP_FAILURE) FatalError(file, line, "Error: CL_MAP_FAILURE", "OpenCL error");
    if (result == CL_MISALIGNED_SUB_BUFFER_OFFSET) FatalError(file, line, "Error: CL_MISALIGNED_SUB_BUFFER_OFFSET", "OpenCL error");
    if (result == CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST) FatalError(file, line, "Error: CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST", "OpenCL error");
    if (result == CL_INVALID_VALUE) FatalError(file, line, "Error: CL_INVALID_VALUE", "OpenCL error");
    if (result == CL_INVALID_DEVICE_TYPE) FatalError(file, line, "Error: CL_INVALID_DEVICE_TYPE", "OpenCL error");
    if (result == CL_INVALID_PLATFORM) FatalError(file, line, "Error: CL_INVALID_PLATFORM", "OpenCL error");
    if (result == CL_INVALID_DEVICE) FatalError(file, line, "Error: CL_INVALID_DEVICE", "OpenCL error");
    if (result == CL_INVALID_CONTEXT) FatalError(file, line, "Error: CL_INVALID_CONTEXT", "OpenCL error");
    if (result == CL_INVALID_QUEUE_PROPERTIES) FatalError(file, line, "Error: CL_INVALID_QUEUE_PROPERTIES", "OpenCL error");
    if (result == CL_INVALID_COMMAND_QUEUE) FatalError(file, line, "Error: CL_INVALID_COMMAND_QUEUE", "OpenCL error");
    if (result == CL_INVALID_HOST_PTR) FatalError(file, line, "Error: CL_INVALID_HOST_PTR", "OpenCL error");
    if (result == CL_INVALID_MEM_OBJECT) FatalError(file, line, "Error: CL_INVALID_MEM_OBJECT", "OpenCL error");
    if (result == CL_INVALID_IMAGE_FORMAT_DESCRIPTOR) FatalError(file, line, "Error: CL_INVALID_IMAGE_FORMAT_DESCRIPTOR", "OpenCL error");
    if (result == CL_INVALID_IMAGE_SIZE) FatalError(file, line, "Error: CL_INVALID_IMAGE_SIZE", "OpenCL error");
    if (result == CL_INVALID_SAMPLER) FatalError(file, line, "Error: CL_INVALID_SAMPLER", "OpenCL error");
    if (result == CL_INVALID_BINARY) FatalError(file, line, "Error: CL_INVALID_BINARY", "OpenCL error");
    if (result == CL_INVALID_BUILD_OPTIONS) FatalError(file, line, "Error: CL_INVALID_BUILD_OPTIONS", "OpenCL error");
    if (result == CL_INVALID_PROGRAM) FatalError(file, line, "Error: CL_INVALID_PROGRAM", "OpenCL error");
    if (result == CL_INVALID_PROGRAM_EXECUTABLE) FatalError(file, line, "Error: CL_INVALID_PROGRAM_EXECUTABLE", "OpenCL error");
    if (result == CL_INVALID_KERNEL_NAME) FatalError(file, line, "Error: CL_INVALID_KERNEL_NAME", "OpenCL error");
    if (result == CL_INVALID_KERNEL_DEFINITION) FatalError(file, line, "Error: CL_INVALID_KERNEL_DEFINITION", "OpenCL error");
    if (result == CL_INVALID_KERNEL) FatalError(file, line, "Error: CL_INVALID_KERNEL", "OpenCL error");
    if (result == CL_INVALID_ARG_INDEX) FatalError(file, line, "Error: CL_INVALID_ARG_INDEX", "OpenCL error");
    if (result == CL_INVALID_ARG_VALUE) FatalError(file, line, "Error: CL_INVALID_ARG_VALUE", "OpenCL error");
    if (result == CL_INVALID_ARG_SIZE) FatalError(file, line, "Error: CL_INVALID_ARG_SIZE", "OpenCL error");
    if (result == CL_INVALID_KERNEL_ARGS) FatalError(file, line, "Error: CL_INVALID_KERNEL_ARGS", "OpenCL error");
    if (result == CL_INVALID_WORK_DIMENSION) FatalError(file, line, "Error: CL_INVALID_WORK_DIMENSION", "OpenCL error");
    if (result == CL_INVALID_WORK_GROUP_SIZE) FatalError(file, line, "Error: CL_INVALID_WORK_GROUP_SIZE", "OpenCL error");
    if (result == CL_INVALID_WORK_ITEM_SIZE) FatalError(file, line, "Error: CL_INVALID_WORK_ITEM_SIZE", "OpenCL error");
    if (result == CL_INVALID_GLOBAL_OFFSET) FatalError(file, line, "Error: CL_INVALID_GLOBAL_OFFSET", "OpenCL error");
    if (result == CL_INVALID_EVENT_WAIT_LIST) FatalError(file, line, "Error: CL_INVALID_EVENT_WAIT_LIST", "OpenCL error");
    if (result == CL_INVALID_EVENT) FatalError(file, line, "Error: CL_INVALID_EVENT", "OpenCL error");
    if (result == CL_INVALID_OPERATION) FatalError(file, line, "Error: CL_INVALID_OPERATION", "OpenCL error");
    if (result == CL_INVALID_GL_OBJECT) FatalError(file, line, "Error: CL_INVALID_GL_OBJECT", "OpenCL error");
    if (result == CL_INVALID_BUFFER_SIZE) FatalError(file, line, "Error: CL_INVALID_BUFFER_SIZE", "OpenCL error");
    if (result == CL_INVALID_MIP_LEVEL) FatalError(file, line, "Error: CL_INVALID_MIP_LEVEL", "OpenCL error");
    if (result == CL_INVALID_GLOBAL_WORK_SIZE) FatalError(file, line, "Error: CL_INVALID_GLOBAL_WORK_SIZE", "OpenCL error");
    return false;
}

bool Kernel::clinitialized = false, Kernel::candoInterop = true;
char* Kernel::log = 0;
cl_context Kernel::context;
cl_command_queue Kernel::queue;
cl_device_id Kernel::device;

static int sourceFiles = 0;
static char* sourceFile[64]; // yup, ugly constant

static size_t workSize[] = { SCRWIDTH, SCRHEIGHT};
static size_t localSize[] = { 32, 4 };


Buffer::Buffer(unsigned int N, unsigned int t /*= DEFAULT*/, void* ptr /*= 0*/)
{
    type = t;
    ownData = false;

    if (t == DEFAULT)
    {
        size = N;
        textureID = 0;
        deviceBuffer = clCreateBuffer(Kernel::GetContext(),CL_MEM_READ_WRITE,size*4,0,0);

        if (!ptr)
        {
            hostBuffer = new unsigned int[size];
            ownData = true;
        }
        else
        {
            hostBuffer = (unsigned int*)ptr;
        }
    }
    else
    {
        textureID = N;
        if (Kernel::candoInterop)
        {
            if (t == TARGET)
            {
                deviceBuffer = clCreateFromGLTexture(Kernel::GetContext(), CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, N, 0);
            }
            else
            {
                deviceBuffer = clCreateFromGLTexture(Kernel::GetContext(), CL_MEM_READ_ONLY, GL_TEXTURE_2D, 0, N, 0);
            }

            hostBuffer = 0;
        }
        else
        {
            size = SCRWIDTH * SCRHEIGHT;
            hostBuffer = new unsigned int[size];

            cl_image_format format;
            cl_image_desc desc;

            desc.image_type = CL_MEM_OBJECT_IMAGE2D;
            desc.image_width = SCRWIDTH;
            desc.image_height = SCRHEIGHT;
            desc.image_depth = 0;
            desc.image_array_size = 0;
            desc.image_row_pitch = 0;
            desc.image_slice_pitch = 0;
            desc.num_mip_levels = 0;
            desc.num_samples = 0;
            desc.buffer = 0;
            format.image_channel_order = CL_RGBA;
            format.image_channel_data_type = CL_FLOAT;
            if (t == TARGET)
            {
                deviceBuffer = clCreateImage(Kernel::GetContext(), CL_MEM_WRITE_ONLY, &format, &desc, hostBuffer, 0);
            }
            else
            {
                deviceBuffer = clCreateImage(Kernel::GetContext(), CL_MEM_READ_WRITE, &format, &desc, hostBuffer, 0);
            }
        }
    }
}

Buffer::~Buffer()
{
    if (ownData)
        delete hostBuffer;
}

void Buffer::CopyToDevice(bool blocking /*= true*/)
{
    cl_int error = clEnqueueWriteBuffer(Kernel::GetQueue(), deviceBuffer, blocking, 0, size * 4, hostBuffer, 0, 0, 0);
    CHECKCL(error);

}

void Buffer::CopyFromDevice(bool blocking /*= true*/)
{
    cl_int error = clEnqueueReadBuffer(Kernel::GetQueue(), deviceBuffer, blocking, 0, size * 4, hostBuffer, 0, 0, 0);
    CHECKCL(error);
}

void Buffer::CopyTo(Buffer* buffer)
{
    clEnqueueCopyBuffer(Kernel::GetQueue(), deviceBuffer, buffer->deviceBuffer, 0, 0, size * 4, 0, 0, 0);
}

void Buffer::Clear()
{
    uint value = 0;
    cl_int error = clEnqueueFillBuffer(Kernel::GetQueue(), deviceBuffer, &value, 4, 0, size * 4, 0, 0, 0);
    CHECKCL(error);
}

void Buffer::Read(void* dst)
{
    unsigned char* data = (unsigned char*)clEnqueueMapBuffer(Kernel::GetQueue(), pinnedBuffer, CL_TRUE, CL_MAP_READ, 0, 4 * size, 0, NULL, NULL, NULL);
    clEnqueueReadBuffer(Kernel::GetQueue(), deviceBuffer, CL_TRUE, 0, 4 * size, data, 0, NULL, NULL);
    memcpy(dst, data, size * 4);
}

void Buffer::Write(void* dst)
{
    unsigned char* data = (unsigned char*)clEnqueueMapBuffer(Kernel::GetQueue(), pinnedBuffer, CL_TRUE, CL_MAP_WRITE, 0, 4 * size, 0, NULL, NULL, NULL);
    memcpy(data, dst, size * 4);
    clEnqueueWriteBuffer(Kernel::GetQueue(), deviceBuffer, CL_FALSE, 0, 4 * size, data, 0, NULL, NULL);
}

static cl_device_id getFirstDevice(cl_context context)
{
    size_t dataSize;
    cl_device_id* devices;
    clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &dataSize);
    devices = (cl_device_id*)malloc(dataSize);
    clGetContextInfo(context, CL_CONTEXT_DEVICES, dataSize, devices, NULL);
    cl_device_id first = devices[0];
    free(devices);
    return first;
}

static cl_int getPlatformID(cl_platform_id* platform)
{
    char chBuffer[1024];
    cl_uint num_platforms, devCount;
    cl_platform_id* clPlatformIDs;
    cl_int error;
    *platform = NULL;

    CHECKCL(error = clGetPlatformIDs(0, NULL, &num_platforms));
    if (num_platforms == 0)
    {
        CHECKCL(-1);
    }

    clPlatformIDs = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id));
    error = clGetPlatformIDs(num_platforms, clPlatformIDs, NULL);

    cl_uint deviceType[2] = { CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_CPU };
    const char* deviceOrder[2][3] = { { "NVIDIA", "AMD", "" }, { "", "", "" } };

    cout << "available OpenCL platforms:\n" << endl;

    for (cl_uint i=0;i<num_platforms;i++)
    {
        CHECKCL(error = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_NAME, 1024, &chBuffer, NULL));
        cout << "#" << i << ":" << chBuffer << endl;
    }

    for (cl_uint j=0;j<2;j++)
    {
        for (int k = 0;k<3;k++)
        {
            for (cl_uint i = 0; i < num_platforms; i++)
            {
                error = clGetDeviceIDs(clPlatformIDs[i], deviceType[j], 0, NULL, &devCount);
                if ((error != CL_SUCCESS) || (devCount == 0)) continue;
                CHECKCL(error = clGetPlatformInfo(clPlatformIDs[i], CL_PLATFORM_NAME, 1024, &chBuffer, NULL));
                if (deviceOrder[j][k][0]) if (!strstr(chBuffer, deviceOrder[j][k])) continue;
                printf("OpenCL device: %s\n", chBuffer);
                *platform = clPlatformIDs[i];
                j = 2, k = 3;
                break;
            }
        }
    }

    free(clPlatformIDs);
    return CL_SUCCESS;
}

static char* loadSource(const char* file, size_t* size)
{
    string source;
    // extract path from source file name
    char path[2048];
    strcpy(path, file);
    char* marker = path, *fileName = (char*)file;
    while (strstr(marker + 1, "\\")) marker = strstr(marker + 1, "\\");
    while (strstr(marker + 1, "/")) marker = strstr(marker + 1, "/");
    while (strstr(fileName + 1, "\\")) fileName = strstr(fileName + 1, "\\");
    while (strstr(fileName + 1, "/")) fileName = strstr(fileName + 1, "/");
    if (fileName != file) fileName++;
    sourceFile[sourceFiles] = new char[strlen(fileName) + 1];
    strcpy(sourceFile[sourceFiles], fileName);
    *marker = 0;
    // load source file
    FILE* f = fopen(file, "r");
    if (!f) ERRORMESSAGE(file, "loadSource");
    char line[8192];
    int lineNr = 0, currentFile = sourceFiles++;
    while (!feof(f))
    {
        line[0] = 0;
        fgets(line, 8190, f);
        lineNr++;
        // clear source file line
        while (line[0])
        {
            if (line[strlen(line) - 1] > 32) break;
            line[strlen(line) - 1] = 0;
        }
        // expand error commands
        char* err = strstr(line, "Error(");
        if (err)
        {
            char rem[8192], cmd[128];
            strcpy(rem, err + 6);
            *err = 0;
            sprintf(cmd, "Error_( %i, %i,", currentFile, lineNr);
            strcat(line, cmd);
            strcat(line, rem);
        }
        // expand assets
        char* as = strstr(line, "Assert(");
        if (as)
        {
            char rem[8192], cmd[128];
            strcpy(rem, as + 7);
            *as = 0;
            sprintf(cmd, "Assert_( %i, %i,", currentFile, lineNr);
            strcat(line, cmd);
            strcat(line, rem);
        }
        // handle include files
        char* inc = strstr(line, "#include");
        if (inc)
        {
            char* start = strstr(inc, "\"");
            if (!start) ERRORMESSAGE("Preprocessor error in #include statement line", "loadSource");
            char* end = strstr(start + 1, "\"");
            if (!end) ERRORMESSAGE("Preprocessor error in #include statement line", "loadSource");
            char file[2048];
            *end = 0;
            strcpy(file, path);
            strcat(file, "/");
            strcat(file, start + 1);
            char* incText = loadSource(file, size);
            source.append(incText);
        }
        else
        {
            source.append(line);
            source.append("\n");
        }
    }
    *size = strlen(source.c_str());
    char* t = (char*)malloc(*size + 1);
    strcpy(t, source.c_str());
    return t;
}

Kernel::Kernel(const char* file, const char* entryPoint)
{
    if (!clinitialized)
    {
        if (!InitCL()) FATALERROR("Failed to initialize OpenCL");
        clinitialized = true;
    }
    size_t size;
    cl_int error;
    char* source = loadSource(file, &size);
    program = clCreateProgramWithSource(context, 1, (const char**)&source, &size, &error);
    CHECKCL(error);
    error = clBuildProgram(program, 0, NULL, "-cl-fast-relaxed-math -cl-mad-enable -cl-denorms-are-zero -cl-no-signed-zeros -cl-unsafe-math-optimizations -cl-finite-math-only", NULL, NULL);
    if (error != CL_SUCCESS)
    {
        if (!log) log = new char[100 * 1024]; // can be quite large
        log[0] = 0;
        clGetProgramBuildInfo(program, getFirstDevice(context), CL_PROGRAM_BUILD_LOG, 100 * 1024, log, NULL);
        log[2048] = 0; // truncate very long logs
        ERRORMESSAGE(log, "Build error");
    }
    kernel = clCreateKernel(program, entryPoint, &error);
    CHECKCL(error);
}

Kernel::~Kernel()
{
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
}

void Kernel::Run()
{
    glFinish();
    cl_int error = clEnqueueNDRangeKernel(queue, kernel, 2, 0, workSize, localSize, 0, 0, 0);
    CHECKCL(error);
    clFinish(queue);
}

void Kernel::Run(cl_mem* buffers, int count /*= 1*/)
{
    glFinish();
    cl_int error;
    if (Kernel::candoInterop)
    {
        CHECKCL(error = clEnqueueAcquireGLObjects(queue, count, buffers, 0, 0, 0));
        CHECKCL(error = clEnqueueNDRangeKernel(queue, kernel, 2, 0, workSize, localSize, 0, 0, 0));
        CHECKCL(error = clEnqueueReleaseGLObjects(queue, count, buffers, 0, 0, 0));
    }
    else
    {
        CHECKCL(error = clEnqueueNDRangeKernel(queue, kernel, 2, 0, workSize, localSize, 0, 0, 0));
    }
    clFinish(queue);
}

void Kernel::Run(Buffer* buffer)
{
    glFinish();
    cl_int error;
    if (Kernel::candoInterop)
    {
        CHECKCL(error = clEnqueueAcquireGLObjects(queue, 1, buffer->GetDevicePtr(), 0, 0, 0));
        CHECKCL(error = clEnqueueNDRangeKernel(queue, kernel, 2, 0, workSize, localSize, 0, 0, 0));
        CHECKCL(error = clEnqueueReleaseGLObjects(queue, 1, buffer->GetDevicePtr(), 0, 0, 0));
    }
    else
    {
        CHECKCL(error = clEnqueueNDRangeKernel(queue, kernel, 2, 0, workSize, localSize, 0, 0, 0));
    }
    clFinish(queue);
}

void Kernel::Run(const size_t count)
{
    cl_int error;
    CHECKCL(error = clEnqueueNDRangeKernel(queue, kernel, 1, 0, &count, 0, 0, 0, 0));
    clFinish(queue);
}

void Kernel::SetArgument(int idx, cl_mem* buffer)
{
    clSetKernelArg(kernel, idx, sizeof(cl_mem), buffer);
}

void Kernel::SetArgument(int idx, Buffer* buffer)
{
    clSetKernelArg(kernel, idx, sizeof(cl_mem), buffer->GetDevicePtr());
}

void Kernel::SetArgument(int idx, float value)
{
    clSetKernelArg(kernel, idx, sizeof(float), &value);
}

void Kernel::SetArgument(int idx, int value)
{
    clSetKernelArg(kernel, idx, sizeof(int), &value);
}

void Kernel::SetArgument(int idx, vec2 value)
{
    clSetKernelArg(kernel, idx, sizeof(vec2), &value);
}

void Kernel::SetArgument(int idx, vec3 value)
{
    clSetKernelArg(kernel, idx, sizeof(vec3), &value);
}

void Kernel::SetArgument(int idx, vec4 value)
{
    clSetKernelArg(kernel, idx, sizeof(vec4), &value);
}

bool Kernel::InitCL()
{
    cl_platform_id platform;
    cl_device_id* devices;
    cl_uint devCount;
    cl_int error;

    if (!CHECKCL(error = getPlatformID(&platform)))
    {
        return false;
    }

    if (!CHECKCL(error = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,NULL,&devCount)))
    {
        return false;
    }

    devices = new cl_device_id[devCount];

    if (!CHECKCL(error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, devCount, devices, NULL)))
    {
        return false;
    }

    unsigned int deviceUsed = 0;
    unsigned int endDev = devCount - 1;
    bool canShare = false;
    for (unsigned int i = deviceUsed; (!canShare && (i <= endDev)); ++i)
    {
        size_t extensionSize;
        CHECKCL(error = clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS, 0, NULL, &extensionSize));

        if (extensionSize > 0)
        {
            char* extensions = (char*)malloc(extensionSize);
            CHECKCL(error = clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS, extensionSize, extensions, &extensionSize));
            std::string devices(extensions);
            free(extensions);
            size_t oldPos = 0;
            size_t spacePos = devices.find(' ', oldPos); // extensions string is space delimited
            while (spacePos != devices.npos)
            {
                if (strcmp("cl_khr_gl_sharing", devices.substr(oldPos, spacePos - oldPos).c_str()) == 0)
                {
                    canShare = true; // device supports context sharing with OpenGL
                    deviceUsed = i;
                    break;
                }
                do
                {
                    oldPos = spacePos + 1;
                    spacePos = devices.find(' ', oldPos);
                } while (spacePos == oldPos);
            }
        }
    }

    if (canShare) printf("Using CL-GL Interop\n"); else
    {
        printf("No device found that supports CL/GL context sharing\n");
        return false;
    }
    cl_context_properties props[] =
    {
        CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
        CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
        CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0
    };

    candoInterop = true;
    context = clCreateContext(props, 1, &devices[deviceUsed], NULL, NULL, &error);
    if (error != 0)
    {
        cl_context_properties props[] = { 0 };
        context = clCreateContext(props, 1, &devices[deviceUsed], NULL, NULL, &error);
        candoInterop = false;
    }

    device = getFirstDevice(context);
    if (!CHECKCL(error)) return false;

    char device_string[1024];
    clGetDeviceInfo(devices[deviceUsed], CL_DEVICE_NAME, 1024, &device_string, NULL);
    printf("Device # %u, %s\n", deviceUsed, device_string);
    // create a command-queue
    queue = clCreateCommandQueue(context, devices[deviceUsed], 0, &error);
    if (!CHECKCL(error)) return false;
    return true;    
}
