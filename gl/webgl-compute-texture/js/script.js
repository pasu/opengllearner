const CANVAS_WIDTH = 800;
const CANVAS_HEIGHT = 800;

const script = async () => {
  // Canvas setup
  const canvas = document.getElementById('myCanvas');
  canvas.width = CANVAS_WIDTH;
  canvas.height = CANVAS_HEIGHT;

  // create WebGL2ComputeRenderingContext
  const context = canvas.getContext('webgl2-compute', {antialias: false});
  if (!context) {
    document.body.className = 'error';
    return;
  }

  // ComputeShader source
  // language=GLSL
  const computeShaderSource = `#version 310 es
  layout (local_size_x = 32, local_size_y = 4, local_size_z = 1) in;
  layout (rgba8, binding = 0) writeonly uniform highp image2D destTex;
  
  vec2 Hash2(vec2 p)
{
	float r = 523.0*sin(dot(p, vec2(53.3158, 43.6143)));
	float v1 = 15.32354 * r - floor(15.32354 * r);
	float v2 = 17.25865 * r - floor(17.25865 * r);
	return vec2(v1, v2);
}

float Cells(vec2 p, float numCells)
{
    p *= numCells;
    float d = 1.0e10;
    for (int xo = -1; xo <= 1; xo++)
    {
        for (int yo = -1; yo <= 1; yo++)
        {
            vec2 tp = floor(p) + vec2(xo, yo);
            float div = numCells / 2.0;
            float v1 = mod(tp.x, div);
            float v2 = mod(tp.y, div);
            vec2 v = vec2(v1, v2);
            tp = p - tp - Hash2(v);
            d = min(d, dot(tp, tp));
        }
    }
    return sqrt(d);
}

  void main() {
    ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);

    float ux = float(gl_GlobalInvocationID.x);
    float uy = float(gl_GlobalInvocationID.y);
    vec2 uv = vec2(ux / 800.0, uy / 600.0);
    float c = Cells(uv, 16.0);

    vec4 col = vec4(c*0.83, c, min(c*1.3, 1.0), 1);

	imageStore(destTex, storePos, col);
  }
  `;

  // create WebGLShader for ComputeShader
  const computeShader = context.createShader(context.COMPUTE_SHADER);
  context.shaderSource(computeShader, computeShaderSource);
  context.compileShader(computeShader);
  if (!context.getShaderParameter(computeShader, context.COMPILE_STATUS)) {
    console.log(context.getShaderInfoLog(computeShader));
    return;
  }

  // create WebGLProgram for ComputeShader
  const computeProgram = context.createProgram();
  context.attachShader(computeProgram, computeShader);
  context.linkProgram(computeProgram);
  if (!context.getProgramParameter(computeProgram, context.LINK_STATUS)) {
    console.log(context.getProgramInfoLog(computeProgram));
    return;
  }

  // create texture for ComputeShader write to
  const texture = context.createTexture();
  context.bindTexture(context.TEXTURE_2D, texture);
  context.texStorage2D(context.TEXTURE_2D, 1, context.RGBA8, CANVAS_WIDTH, CANVAS_HEIGHT);
  context.bindImageTexture(0, texture, 0, false, 0, context.WRITE_ONLY, context.RGBA8);

  // create frameBuffer to read from texture
  const frameBuffer = context.createFramebuffer();
  context.bindFramebuffer(context.READ_FRAMEBUFFER, frameBuffer);
  context.framebufferTexture2D(context.READ_FRAMEBUFFER, context.COLOR_ATTACHMENT0, context.TEXTURE_2D, texture, 0);

  // execute ComputeShader
  context.useProgram(computeProgram);
  context.dispatchCompute(CANVAS_WIDTH / 32, CANVAS_HEIGHT / 4, 1);
  context.memoryBarrier(context.SHADER_IMAGE_ACCESS_BARRIER_BIT);

  // show computed texture to Canvas
  context.blitFramebuffer(
    0, 0, CANVAS_WIDTH, CANVAS_HEIGHT,
    0, 0, CANVAS_WIDTH, CANVAS_HEIGHT,
    context.COLOR_BUFFER_BIT, context.NEAREST);
};

window.addEventListener('DOMContentLoaded', script);
