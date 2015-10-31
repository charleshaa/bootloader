#ifndef _FONCTION_AFFICHAGE_H_
#define _FONCTION_AFFICHAGE_H_

void update_cursor(int row, int col);
uint16_t get_cursor();
void monitor_put(char c);
void monitor_write(char *c);
void monitor_clear();
void set_backColour(uint8_t color);
void set_foreColour(uint8_t color);
uint8_t get_backColour();
uint8_t get_foreColour();
static void scroll();

#endif