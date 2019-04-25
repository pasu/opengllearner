#include "cuda_runtime.h"
#include <stdlib.h>
#include <stdio.h>

cudaError_t cuda();

__global__ void kernel(){
  
}

__device__
float2 Hash2(float2 p)
{
    float2 value;
    value.x = 53.3158f;
    value.y = 43.6143f;
    float r = 523.0f*sinf(p.x*value.x+ p.y*value.y);
    float v1 = 15.32354 * r - floor(15.32354 * r);
    float v2 = 17.25865 * r - floor(17.25865 * r);
    value.x = v1;
    value.y = v2;
    return value;
}
__device__ float Cells(float2 p, float numCells)
{
    p.x *= numCells;
    p.y *= numCells;
    float d = 1.0e10;
    for (int xo = -1; xo <= 1; xo++)
    {
        for (int yo = -1; yo <= 1; yo++)
        {
            float2 value; 
            value.x = (float)xo;
            value.y = (float)yo;
            float2 tp;
            tp.x = floorf(p.x) + value.x;
            tp.y = floorf(p.y) + value.y;
            float div = (float)(numCells / 2.0);
            float v1 = fmod(tp.x, div);
            float v2 = fmod(tp.y, div);
            float2 v;
            v.x = v1;
            v.y = v2;
            v = Hash2(v);
            tp.x = p.x - tp.x - v.x;
            tp.y = p.y - tp.y - v.y;
            d = min(d, tp.x*tp.x+tp.y*tp.y);
        }
    }
    return sqrt(d);
}

// clamp x to range [a, b]
__device__ float clamp(float x, float a, float b)
{
	return max(a, min(b, x));
}

__device__ int clamp(int x, int a, int b)
{
	return max(a, min(b, x));
}

// convert floating point rgb color to 8-bit integer
__device__ int rgbToInt(float r, float g, float b)
{
	r = clamp(r, 0.0f, 255.0f);
	g = clamp(g, 0.0f, 255.0f);
	b = clamp(b, 0.0f, 255.0f);
    return (int(r) << 16) | (int(g) << 8) | int(b);
}

__global__ void
cudaRender(unsigned int *g_odata, int imgw)
{
	extern __shared__ uchar4 sdata[];

	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int bw = blockDim.x;
	int bh = blockDim.y;
	int x = blockIdx.x*bw + tx;
	int y = blockIdx.y*bh + ty;

    float2 uv;
    uv.x = (float)x / 800.0;
    uv.y = (float)y / 800.0;

    float c = Cells(uv, 16.0);

	uchar4 c4 = make_uchar4(c*0.83*255.0, c*255.0, min(c*1.3, 1.0)*255.0, 0);
	g_odata[y*imgw + x] = rgbToInt(c4.z, c4.y, c4.x);
}

extern "C" void
launch_cudaRender(dim3 grid, dim3 block, int sbytes, unsigned int *g_odata, int imgw)
{
	cudaRender << < grid, block, sbytes >> >(g_odata, imgw);
}
