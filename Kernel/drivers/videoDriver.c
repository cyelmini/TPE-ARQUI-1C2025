#include "videoDriver.h"

struct vbe_mode_info_structure {
	uint16_t attributes;		
	uint8_t window_a;		
	uint8_t window_b;			
	uint16_t granularity;		
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		
	uint16_t pitch;			
	uint16_t width;			
	uint16_t height;			
	uint8_t w_char;			
	uint8_t y_char;			
	uint8_t planes;
	uint8_t bpp;			
	uint8_t banks;			
	uint8_t memory_model;
	uint8_t bank_size;		
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}
