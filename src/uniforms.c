#include <math.h>
#include <seqGraph/debug.h>
#include <seqGraph/uniforms.h>

void makeProjectionMatrix(mat4 dest, f32 fov, f32 far, f32 near) {
  f32 S = 1 / tan((fov / 2) * (3.141516 / 180));
  f32 a = (far / (far - near));
  f32 b = -((far * near) / (far - near));

  dest[0][0] = S;
  dest[1][1] = S / (float)(W / H);
  dest[2][2] = a;
  dest[2][3] = b;
  dest[3][2] = 1;

  LOGV4("[0]", dest[0]);
  LOGV4("[1]", dest[1]);
  LOGV4("[2]", dest[2]);
  LOGV4("[3]", dest[3]);
}
