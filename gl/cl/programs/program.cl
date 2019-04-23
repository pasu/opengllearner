#include "../shared.h"
#include "randomnumbers.h"
#include "program.h"

__kernel void TestFunction( write_only image2d_t outimg )
{
	uint x = get_global_id( 0 );
	uint y = get_global_id( 1 );
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;

    float2 uv = (float2)(((float)x / SCRWIDTH), ((float)y / SCRHEIGHT));
    float c = Cells(uv, NUM_CELLS);
    float4 col = (float4)(c*.83, c, min(c*1.3, 1.0),1);
	write_imagef( outimg, (int2)(x, y), col);
}

__kernel void Clear( write_only image2d_t outimg )
{
	uint x = get_global_id( 0 );
	uint y = get_global_id( 1 );
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;
	float r = (float)x / SCRWIDTH;
	float g = (float)y / SCRHEIGHT;
	write_imagef( outimg, (int2)(x, y), (float4)( 0, 0, 0, 1 ) );
}

__kernel void BoundsTest( __global uint* a )
{
	int id = get_global_id( 0 );
	if (id == 9999) a[9999] = 99999; else a[id] = id;
}