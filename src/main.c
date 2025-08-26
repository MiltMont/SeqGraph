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

  Color background = 0xfffffffff;

  OSWMouse mouse; 

  OSW_MouseSetPolling(OSW_TRUE);
  sgSetClearColor(background);
  sgClearColor();

  while (1) {
    OSW_Poll();
    OSW_MouseGetState(&mouse);

    if (OSW_MOUSE_BTN1) {
      sgPokePixel(mouse.x, mouse.y, 0);
    }

    sgDrawBuffer();
    OSW_VideoSwapBuffers();
  }
  return 0;
}
