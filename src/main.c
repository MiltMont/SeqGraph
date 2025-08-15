#include <libosw/osw.h>
#include <math.h>
#include <seqGraph/seqGraph.h>

int main(int argc, char *argv[]) {
  // Create window and check for errors
  u32 err = OSW_Init("Game window", W * 2, H * 2, 0);

  // Initialize timer
  u32 timer = 0;

  if (err != OSW_OK) {
    return err;
  }

  Color background = 0;

  while (1) {
    timer += 5;
    background += 1 + sin(timer);

    OSW_Poll();
    sgSetClearColor(background);
    sgClearColor();
    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }
  return 0;
}
