#include <math.h>
#include <seqGraph/debug.h>
#include <seqGraph/uniforms.h>

void makeProjectionMatrix(mat4 dest, f32 FOV, f32 FAR, f32 NEAR) {
  f32 S = 1 / tan((FOV / 2) * (3.141516 / 180));
  f32 a = (FAR / (FAR - NEAR));
  f32 b = -((FAR * NEAR) / (FAR - NEAR));

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
