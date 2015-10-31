#include "../common/types.h"
#include "x86.h"
#include "kernel.h"
#include "fonction.h"
#include "gdt.h"
#include "fonction_affichage.h"


void kernel(){
	//??marche pas gdt_init();
	//TODO
	test();
	update_cursor(0,0);
	monitor_clear();
	//outb(0x3C0,0x02);//3C0 change couleur fond sur 1 byte 
	set_backColour(0x6);
	set_foreColour(0xe);
	monitor_put('a');
	monitor_write("salut toi");
	monitor_clear();
	monitor_write("oisahdfzgipurhgiausdhgisudhgisaudhiugfsdhgiusaiefuiafisduhgidfushgidufhgidusfhgidsfhugipdsuegdfiazwguifzwgeui\t");
	get_cursor();
	//monitor_write("salut\ttoi\ncoucou\nvous");
	while(1);
}