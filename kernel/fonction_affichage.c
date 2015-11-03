#include "../common/types.h"
#include "x86.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"
#include "math.h"

//1ere adresse memoire video
static uint16_t *video_memory = (uint16_t *)0xB8000;

//Position du curseur
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//Couleur (caractere et fond)
static uint8_t backColor = COLOR_BLACK;
static uint8_t foreColor = COLOR_WHITE;


void monitor_init() {
   //Activation du curseur au niveau de l'affichage
   //Cursor Start Register
   outb(0x3D4, 0xA);                 
   outw(0x3D5, 0);
   //Cursor End Register
   outb(0x3D4, 0xB);                 
   outw(0x3D5, 31);

   //Place le curseur en haut a gauche
   set_cursor(0,0);  

   //Efface l'ecrant
   monitor_clear();    
}


void set_cursor(uint8_t row, uint8_t col)
{
   cursor_x = row;
   cursor_y = col;
   //Calcul de la position du curseur en 1D
   uint16_t pos_1D = col * 80 + row;
   //Position du curseur
   //MSB
   outb(0x3D4, 0xE);                 
   outw(0x3D5, pos_1D >> 8); 
   //LSB
   outb(0x3D4, 0xF);                 
   outw(0x3D5, pos_1D);      

}

uint16_t get_cursor() {
   uint8_t MSB;
   uint8_t LSB;
   uint16_t pos;

   //Recupere la position 1D du curseur
   //MSB
   outb(0x3D4, 14);
   MSB=inb(0x3D5);  
   //LSB    
   outb(0x3D4, 15);
   LSB=inb(0x3D5);

   pos = LSB + (MSB<<8);
   return pos;
}

void monitor_put(char c)
{
   uint8_t  attribut = (backColor << 4) | (foreColor & 0x0F);
   uint16_t char_attribut = attribut << 8;
   uint16_t *position;

   //si "c" est un backspace et que l'on est pas en debut de ligne
   if (c == 0x08 && cursor_x)
      //Decaler vers la gauche le curseur
      cursor_x--;

   //si "c" est une tabulation
   else if (c == '\t')
      //deplace le curseur vers la droite jusq'au prochain multiple de 8
      cursor_x = (cursor_x+8) & 0xF8;

   //si "c" est un carriage return
   else if (c == '\r')
      //replace le curseur en debut de ligne
      cursor_x = 0;


   //si "c" est un newline
   else if (c == '\n') {
      //place le curseur en debut de ligne suivante
      cursor_x = 0;
      cursor_y++;
   }
   //si "c" est un caractere imprimable
   else {
      //calcul de la position en 1D dans la memoire video
      position = video_memory + (cursor_y*80 + cursor_x);
      //Ecrire dans la memoire video
      *position = c | char_attribut;
      //Deplacer le curseur
      cursor_x++;
   }

   //si on arrive en fin de ligne
   if (cursor_x >= 80) {
      cursor_x = 0;
      cursor_y ++;
   }

   //Verifie si il faut faire un scroll
   scroll();
   
   //Place le curseur apres le caractere ecrit
 	set_cursor(cursor_x, cursor_y);
}

void monitor_write(char *c)
{
   int i = 0;
   //Tant que l'on est pas en fin de chaine ecrire un caractere
   while (c[i]) 
      monitor_put(c[i++]);
}

void monitor_clear()
{
   uint8_t attribut = (backColor << 4) | (foreColor & 0x0F);
   uint16_t espace = ' ' | (attribut << 8);

   int i;
   //Insert des espaces dans tous l'affichage
   for (i = 0; i < 80*25; i++)
      video_memory[i] = espace;
   
   //Place le curseur en haut a gauche
   set_cursor(0, 0);
}

static void scroll()
{
   uint8_t attribut = (backColor << 4) | (foreColor & 0x0F);
   uint16_t espace = ' ' | (attribut << 8);

   //Si le curseur est en bas de l'affichage
   if(cursor_y >= 25)
   {
      //Copier les ligne 1 a 24 sur les lignes 0 a 23
      int i;
      for (i = 0*80; i < 24*80; i++)
           video_memory[i] = video_memory[i+80];
       
      //Effacer la derniere ligne (mettre des espaces)
      for (i = 24*80; i < 25*80; i++)
         video_memory[i] = espace;
       
      //Placer le curseur en debut de derniere ligne
      set_cursor(cursor_x, 24);
   }
}

void set_backColor(uint8_t color) {
   backColor = color;
}

void set_foreColor(uint8_t color) {
   foreColor = color;
}

uint8_t get_backColor() {
   return backColor;
}

uint8_t get_foreColor() {
   return foreColor;
}

void printf(char *fmt, ...) {

	uint16_t i = 0;
	uint32_t *arg = &fmt;


	while(fmt[i]) {
		if(fmt[i]=='%') {
			i++;
			arg++;
			switch(fmt[i]) {
				case 'd':
					print_dec(*arg);
				break;
				case 's':;
					char* str = *arg;
					monitor_write(str);
				break;
				case 'c':
					monitor_put(*arg);
				break;
				case 'x':
					print_hex(*arg);
				break;
				default:
					arg--;
					monitor_put(fmt[i]);
				break;
			}
		} else {
			monitor_put(fmt[i]);
		}
		i++;
	}
}

void print_hex(uint32_t value) {

	uint32_t value_temp = 0;
	monitor_write("0x");
	bool flag0 = false;
	char char_hex[] = "0123456789ABCDEF";

	for (int8_t j = 7; j >= 0; j--) {
		value_temp = (value>>(j*4)) & 0xf;

		//pour ne pas afficher les 0 inutils
		if(value_temp > 0)
			flag0 =  true;

		if(j == 0 || flag0)
			monitor_put(char_hex[value_temp]);
	}
}

void print_dec(int32_t value) {
	bool flag0 = false;
	char c;
	if(value < 0) {
		monitor_put('-');
		value = ~value +1;
	}
	for (int16_t i = 9; i >= 0; i--) {

		c=(((value/pow(10,i))) %10)+'0';

		//pour ne pas afficher les 0 inutils
		if(c > '0')
			flag0 = true;

		if(i == 0 || flag0)
			monitor_put(c);
	}
}

void wait(uint32_t t) {
	for (uint32_t j = 0; j < t; ++j)	{
		for (uint32_t i = 0; i < 100000000; ++i) {
			i++;
			i--;
		}
	}
}