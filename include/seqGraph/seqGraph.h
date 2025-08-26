#ifndef __SG_H__
#define __SG_H__

#define W 600
#define H 600

#include <libosw/osw.h>

typedef u32 Color;

// Local variables 
u32 viewPort_x; 
u32 viewPort_y; 
u32 viewPort_w; 
u32 viewPort_h; 

/// Draws the framebuffer.
void sgDrawBuffer(void);

/// Set the framebuffer color.
void sgSetClearColor(Color c);

/// Clear the frambuffer color.
void sgClearColor(void);

/// Sets pixel at coordinate (x,y) to Color
void sgPokePixel(u32 x,u32 y, Color c);

/// Performs viewport transformation between clip space
/// and screen space. 
void sgViewport(u32 x_0, u32 y_0, u32 w, u32 h);

#endif // !__SG_H__
