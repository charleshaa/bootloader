#ifndef _FONCTION_H_
#define _FONCTION_H_

/*memset
Copie "count" fois "value" dans "dst"
*/
void *memset (void * dst, int value, unsigned int count);

/*memcpy
Copie "count" element de "src" dans "dst"
*/
void *memcpy (void * dst, void *src, unsigned int count);

/*strncmp
compare les "n" premiers char de "q" et de "p"
retourne  0 => les chaine de caractere sont egal
retourne -1 => le 1er caractere different est < dans "p" que dans "q"
retourne +1 => le 1er caractere different est > dans "p" que dans "q"
*/
int strncmp (const char *p, const char *q, unsigned int n);

#endif