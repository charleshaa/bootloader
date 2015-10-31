#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"

extern void outb(uint16_t port, uint8_t data);
extern void outw(uint16_t port, uint16_t data);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern void test();

// The VGA framebuffer starts at 0xB8000.
uint16_t *video_memory = (uint16_t *)0xB8000;
// Stores the cursor position.
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint8_t backColour = 0;
uint8_t foreColour = 15;

 void update_cursor(int row, int col)
 {
 	cursor_x = row;
 	cursor_y = col;
   // The screen is 80 characters wide...
   uint16_t cursorLocation = col * 80 + row;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outw(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outw(0x3D5, cursorLocation);      // Send the low cursor byte.

 }

uint16_t get_cursor() {
	uint8_t MSB;
	uint8_t LSB;
	uint16_t pos;

	outb(0x3D4, 14);
   MSB=inb(0x3D5);      
   outb(0x3D4, 15);     
   LSB=inb(0x3D5);      	

   pos = LSB + (MSB<<8);

	return pos;
}

void monitor_put(char c)
{
   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   uint16_t attribute = attributeByte << 8;
   uint16_t *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x) {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == '\t') {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r') {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n') {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ') {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80) {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.

   // Move the hardware cursor.
 	update_cursor(cursor_x, cursor_y);
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(char *c)
{
   int i = 0;
   while (c[i]) {
       monitor_put(c[i++]);
   }
}


// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
   // Make an attribute byte for the default colours
   uint8_t attributeByte = (backColour << 4) | (foreColour & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   update_cursor(cursor_x, cursor_y);
}

void set_backColour(uint8_t color) {
	backColour = color;
}
void set_foreColour(uint8_t color) {
	foreColour = color;
}
uint8_t get_backColour() {
	return backColour;
}
uint8_t get_foreColour() {
	return foreColour;
}


/* CE QU IL FAUT FAIRE
Fonction d'initialisation : initialise l'affichage en effaçant l'écran et en positionnant le curseur
en haut à gauche.
• Fonction d'effacement : efface l'écran.
• Fonction(s) permettant de changer la couleur du texte ainsi que la couleur du fond.
• Fonction(s) permettant de récupérer la couleur du texte ainsi que la couleur du fond.
• Fonction permettant d'afficher un caractère à la position du curseur.
• Fonction permettant d'afficher une chaîne de caractères à la position du curseur.
• Fonction d'affichage à arguments variable similaire à printf, implémentant au moins les
formats suivants :%c,%s,%d et %x
• Fonction permettant de définir la position du curseur.
• Fonction permettant d'obtenir la position du curseur
 *********DEJA FAIT*****


*/