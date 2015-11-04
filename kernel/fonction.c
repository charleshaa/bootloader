/**
 * @file fonction.c
 * @brief fonction de base pour un OS 
 * @author Pasquier Gerome,
 * @date Novembre 2015
 * @version 0.1
 */

#include "fonction.h"

void *memset (void * dst, int value, unsigned int count) {
   char *dp = dst;
   unsigned int i;
   for (i = 0; i < count; ++i)
      dp[i] = value;

   return dst;
}


void *memcpy (void * dst, void *src, unsigned int count) {
   unsigned int i;
   char * dp = dst;
   const char * sp = src;
   for (i = 0; i < count; ++i)
      dp[i] = sp[i];

   return dst;
}


int strncmp (const char *p, const char *q, unsigned int n) {
   unsigned int i;
   for (i = 0; i < n; ++i)
   {
      if(p[i] != q[i]) {
         if(p[i] < q[i])
            return -1; //p<q
         else
            return +1; //p>q
      }
   }
   return 0; //p=q
}