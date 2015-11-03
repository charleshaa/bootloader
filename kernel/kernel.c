#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"


void kernel(){
	//initialisation de la GDT et de l'affichage
   gdt_init();
   monitor_init();

   #ifdef _DEBUG
   //Mode debug : effectue des testes sur toutes les fonction d'affichage

   //test couleur
   for (uint8_t i = 0; i < 16; ++i) {
   	set_backColor(i);
   	set_foreColor((i+1)%16);
   	monitor_clear();
   	monitor_write("\n\n\n\tTEST DES COULEURS");
   	wait(1);
	}
	set_backColor(COLOR_BLACK);
   set_foreColor(COLOR_WHITE);
   monitor_clear();

   //test curseur
   monitor_write("placer le curseur en position 6,4:");
   set_cursor(6,4);
   wait(2);
   uint16_t pos = get_cursor();
   monitor_write("\nlecture de la position du curseur en 6,4");
   printf("\npositon en X :%d\nposition en Y :%d", pos%80, pos/80);
   wait(2);
   monitor_clear();

   //test printf
   monitor_write("test de la fonction printf\n\n");
   printf("Afficher un X et un Y en debut et en fin de bonjour : %cbonjour%c\n",'X','Y');
   printf("Afficher la chaine bonjour entre X et Y : X%sY\n", "bonjour");
   printf("Afficher en hexa la valeur 48 : %x\n", 48);
   printf("Afficher en hexa la valeur 0x123ADF : %x\n", 0x123ADF);
   printf("Afficher en decimal 1, -1, 123456789 et -987654321 : %d %d %d %d", 1, -1, 123456789, -987654321);
   wait(3);
   monitor_clear();

   //test scroll
   monitor_write("Test de la fonction scroll\n");
   monitor_write("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n");
   wait(1);
   monitor_write("23\n");
   wait(1);
   monitor_write("24\n");
   wait(1);
   monitor_write("25\n");

   //fin des tests
   monitor_clear();
   monitor_write("FIN DES TESTS ");
   set_foreColor(COLOR_YELLOW);
   monitor_put(1);

	#else

	//affichage du message d'accueil
   set_backColor(COLOR_LIGHT_GREEN);
   set_foreColor(COLOR_BLUE);
   monitor_clear();
   printf("\n\tInitialisation de la console :\tOK\n");
   printf("\n\tInitialisation de la GDT :\tOK");
   printf("\n\t");
   #endif
   //fin du programme
   while(1);
}