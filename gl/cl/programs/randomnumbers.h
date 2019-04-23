uint TauStep( int s1, int s2, int s3, uint M, uint* seed )
{
	uint b = (((*seed << s1) ^ *seed) >> s2);
	*seed = (((*seed & M) << s3) ^ b);
	return *seed;
}

uint HQIRand( uint* seed )
{
	uint z1 = TauStep( 13, 19, 12, 429496729, seed );
	uint z2 = TauStep( 2, 25, 4, 4294967288, seed );
	uint z3 = TauStep( 3, 11, 17, 429496280, seed );
	uint z4 = 1664525 * *seed + 1013904223;
	return z1 ^ z2 ^ z3 ^ z4;
}

uint SeedRandom( uint s )
{
	uint seed = s * 1099087573;
	seed = HQIRand( &seed );
	return seed;
}

uint RandomInt( uint* seed ) 
{
	// Marsaglia Xor32; see http://excamera.com/sphinx/article-xorshift.html
	// also see https://github.com/WebDrake/xorshift/blob/master/xorshift.c for higher quality variants
	*seed ^= *seed << 13;
	*seed ^= *seed >> 17;
	*seed ^= *seed << 5;
	return *seed;
}

float RandomFloat( uint* seed )
{
	return RandomInt( seed ) * 2.3283064365387e-10f;
}

float2 Hash2(float2 p)
{
    float r = 523.0*sin(dot(p, (float2)(53.3158, 43.6143)));
    float v1 = 15.32354 * r - floor(15.32354 * r);
    float v2 = 17.25865 * r - floor(17.25865 * r);
    return (float2)(v1, v2);
}

float Cells(float2 p, float numCells)
{
    p *= numCells;
    float d = 1.0e10;
    for (int xo = -1; xo <= 1; xo++)
    {
        for (int yo = -1; yo <= 1; yo++)
        {
            float2 tp = floor(p) + (float2)(xo, yo);
            float div = (float)(numCells / TILES);
            float v1 = fmod(tp.x, div);
            float v2 = fmod(tp.y, div);
            float2 v = (float2)(v1,v2);
            tp = p - tp - Hash2(v);
            d = min(d, dot(tp, tp));
        }
    }
    return sqrt(d);
}