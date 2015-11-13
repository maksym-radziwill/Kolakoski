#define BLOCK 1024

/*
   1  -> 1
   2  -> 2
   11 -> 3
   22 -> 4
*/

inline int
height(char * restrict P){
  register int k = 0;
  for(k = 0; P[k] == 1 || P[k] == 2; k++);
  return k;
}

/* Still try to do a larger look-up table
   Maybe it will give a small performance boost */

inline void
assign(char * restrict P){

  const static char LOT[5][5] = {
    {0, 0, 0, 0, 0 },
    {0, 2, 1, 0, 0 },
    {0, 4, 3, 0, 0 },
    {0, 2, 1, 0, 0 },
    {0, 4, 3, 0, 0 }
  };

  P[-1] = *(LOT[(int) P[0]] + P[-1]);

}

inline void
trim(char * P){  
  P[0] = 2 - (P[0] % 2);
}

void
Loop(char * restrict P){
  
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

void
Count(const char * restrict P,
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


