/**
 * @file math.c
 * @brief fonction mathematique
 * @author Pasquier Gerome
 * @date Novembre 2015
 * @version 0.1
 */

#include "../common/types.h"
#include "x86.h"
#include "math.h"


uint32_t pow(uint16_t n, uint16_t m) {
   uint32_t result = 1;
   uint16_t i;
   for (i = 0; i < m; ++i) {
      result = result * n;
   }
   return result;
}