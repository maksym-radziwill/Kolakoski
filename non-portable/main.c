#include "small_libc.h"
#include "kolakoski.h"


inline void
Count_adjust(const char *   P,
	     unsigned long long *   count1,
	     unsigned long long *   count2,
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


void start(int argc, char * argv, char * num){
  
  if(argc < 2){
    print_str("Usage: ");
    print_str(argv); 
    print_str(" len\n"); 
    quit(0);
  }  
  
  char P[BLOCK] = {0}; 
  unsigned long long count1 = 1;
  unsigned long long count2 = 2;
  unsigned long long len = 2;

  len = Atoll(num); 
  
  P[0] = 2;
  P[1] = 0;

  while(count1 + count2 < len){
    Loop(P);
    Count(P, &count1, &count2); 
  }
  
  Count_adjust(P, &count1, &count2, len);

  print_str("Number of 1's: ");
  print_longlong(count1);
  print_str("Number of 2's: ");
  print_longlong(count2);


  print_str("Discrepancy: ");

  const long long diff = count1 - count2;

  if(diff < 0) print_longlong((unsigned long long) - diff);
  else print_longlong(diff); 

  print_str("Length of sequence: ");
  print_longlong(count1 + count2); 
  
  quit(0); 

}
