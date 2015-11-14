/* Much faster when using a fixed array */

/* Actually one way to speed this up is to
 create a more elaborate look-up table
 which precomputes two to three operations
 down -- notice that if we are high up 
 then two operations down are entirely
 predictable given suitable input... */

/* ISSUES: Count off by +/- 1 in some instances */
/* Speed has been improved by a factor of 2 thanks
   to the use of the init variable */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLOCK 1*1024

/*
   1  -> 1
   2  -> 2
   11 -> 3
   22 -> 4
*/

inline int
height(char * P){
  int k = 0;
  for(k = 0; P[k] == 1 || P[k] == 2; k++);
  return k;
}

/* Still try to do a larger look-up table
   Maybe it will give a small performance boost */

inline void
assign(char * P){

  const static char LOT[5][5] = {
    {0, 0, 0, 0, 0, },
    {0, 2, 1, 0, 0, },
    {0, 4, 3, 0, 0, },
    {0, 2, 1, 0, 0, },
    {0, 4, 3, 0, 0, }
  };

  P[-1] = *(LOT[(int) P[0]] + P[-1]);

}

inline void
trim(char * P){  
  P[0] = 2 - (P[0] % 2);
}

inline void
Loop(char * P){
  
  register int  k = 0;

  /* Go to the first node which is 11 or 22 or 0 */
  
  k = height(P);

  /* Trim the highest node to 1 or 2
     Exception if the highest node turns out to be 0 */
  
  if(k == 0){
    if(P[0] > 2){
      trim(P);
      k = height(P);
    }
  }

  trim(P+k);

  /* Descend down on the 1, 2 patterns */

  while(k >= 1){
    assign(P+k);
    k = k - 1;
  }
}

inline void
Count(const char * P,
      unsigned long long * count1,
      unsigned long long * count2){

  if(P[0] == 1){
    *count1 = *count1 + 1;
  }else if(P[0] == 2){
    *count2 = *count2 + 1;
  }else if(P[1] == 3){
    if(P[0] == 3)
      *count1 = *count1 + 1;
    else
      *count2 = *count2 + 1;
  }else{
    if(P[0] == 3)
      *count1 = *count1 + 2;
    else
      *count2 = *count2 + 2;
  }

  return;
}

void
Count_adjust(const char * P,
	     unsigned long long * count1,
	     unsigned long long * count2,
	     const unsigned long long len){  
  if(*count1 + *count2 > len){
    if(P[0] == 4){
      *count2 = *count2 - 1;
    }
    
    if(P[0] == 3){
      *count1 = *count1 - 1;
    }
  }
}

int main(int argc, char ** argv){

  char P[BLOCK] = {0}; 
  unsigned long long count1 = 1;
  unsigned long long count2 = 2;
  unsigned long long len = 0;
  
  if(argc < 2)
    return printf("Usage: %s num\n", argv[0]);
  else
    len = atoll(argv[1]);
  
  P[0] = 2;
  P[1] = 0;
  
  while(count1 + count2 < len){
    Loop(P);
    Count(P, &count1, &count2); 
  }

  Count_adjust(P, &count1, &count2, len); 

  printf("Number of 1's: %lld\n", count1);
  printf("Number of 2's: %lld\n", count2);
  printf("Discrepancy: %lld\n", count1 - count2);
  printf("Length of sequence: %lld\n", count1 + count2); 

  return 0;
}
