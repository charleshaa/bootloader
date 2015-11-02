#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"

//1ere adresse memoire video
static uint16_t *video_memory = (uint16_t *)0xB8000;

//Position du curseur
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//Couleur (caractere et fond)
static uint8_t backColor = 0;
static uint8_t foreColor = 15;


void monitor_init() {
   //Activation du curseur au niveau de l'affichage
   //Cursor Start Register
   outb(0x3D4, 0xA);                 
   outw(0x3D5, 0);
   //Cursor End Register
   outb(0x3D4, 0xB);                 
   outw(0x3D5, 31);      
}


void set_cursor(int row, int col)
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
   else if(c >= ' ') {
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
   set_cursor(cursor_x, cursor_y);
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