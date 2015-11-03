#ifndef _FONCTION_AFFICHAGE_H_
#define _FONCTION_AFFICHAGE_H_

extern void outb(uint16_t port, uint8_t data);
extern void outw(uint16_t port, uint16_t data);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GRAY 7
#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

/*set_cursor
Place le curseur dans la fenetre a la position "row", "col"
row de 0 a 24
col de 0 a 79
*/
void set_cursor(uint8_t row, uint8_t col);

/*get_cursor
Obtenir la position du curseur
retourne une position en 1D (de 0 a 4000)
*/
uint16_t get_cursor();

/*monitor_put
Affiche le caractere "c" a la position courante du curseur
Deplace le curseur a la positon suivante
*/
void monitor_put(char c);

/*monitor_write
Affiche une chaine de caractere a la position du curseur
Deplace le curseur a la fin de la chaine
*/
void monitor_write(char *c);

/*monitor_clear
Efface l'ecrant
*/
void monitor_clear();

/*set_backColour
Reglage de la couleur du fond
"color" allant de 0 a 15
*/
void set_backColor(uint8_t color);

/*set_foreColour
Reglage de la couleur du caractere
"color" allant de 0 a 15
*/
void set_foreColor(uint8_t color);

/*get_backColour
Obtenir la couleur de fond
"color" allant de 0 a 15
*/
uint8_t get_backColor();

/*get_foreColour
Obtenir la couleur des caracteres
"color" allant de 0 a 15
*/
uint8_t get_foreColor();

/*scroll
Effectue un decalage d'une ligne vers le haut de l'affichage
Pour autant que l'on se trouve en bas de l'affichage
*/
static void scroll();

/*affichage_init
Initialisation de l'affichage (curseur)
*/
void monitor_init();

/*printf
Affiche une chaine de caractere formatee
%s = une string
%d = une valeur decimal
%c = un caractere
%x = une valuer hexa
*/
void printf(char *fmt, ...);

/*print_hex
afficher un valeux en hexa
0x123A donne "0x123A"
0x0023 donne "0x23"
*/
void print_hex(uint32_t value);

/*print_dec
	afficher une valeur en decimal
	0xA donne "10"
	0x80 donne "128"
	0xFFFFFFFF donne "-1"
*/
void print_dec(int32_t value);


/*
attendre
*/
void wait(uint32_t t);

#endif