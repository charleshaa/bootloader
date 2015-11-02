#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"


void kernel(){
   //??marche pas gdt_init();
   monitor_init();
   set_cursor(0,0);
   monitor_clear();
   set_backColor(12);
   set_foreColor(1);
   monitor_put('a');
   monitor_write("salut toi");
   monitor_clear();
   monitor_write("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24");
   monitor_write("\ngisdzgfuzdlg");
   get_cursor();

   //fin du programme
   while(1);
}