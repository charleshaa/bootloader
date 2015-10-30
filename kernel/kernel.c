#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"

extern void outb(uint16_t port, uint8_t data);
extern void outw(uint16_t port, uint16_t data);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern void test();

void kernel(){
	//??marche pas gdt_init();
	//TODO
	test();
	//update_cursor(1,1);
	//outb(0x3C0,0x02);//3C0 change couleur fond sur 1 byte 
	outb(0x3C0,0x2E);
	while(1);
}

 void update_cursor(int row, int col)
 {
    unsigned short position=(row*80) + col;
 
    // cursor LOW port to vga INDEX register
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
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
*/