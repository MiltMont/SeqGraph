#ifndef __SG_H__
#define __SG_H__

#define W 600
#define H 600

#include <libosw/osw.h>

typedef u32 Color;

/// Draws the framebuffer.
void sgDrawBuffer(void);

/// Set the framebuffer color.
void sgSetClearColor(Color c);

/// Clear the frambuffer color.
void sgClearColor(void);

#endif // !__SG_H__
