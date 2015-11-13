#include <stdint.h>

/* Internal functions --------------- */

inline int length(char * str){
  int i = 0;
  for(i = 0; str[i] != 0; i++);
  return i;
}

/* Revise this seems space wasteful */

void print_int(unsigned long n){
  unsigned long num = n;
  char str[128];
  char rev_str[128];
  int i = 0;

  if(num == 0){
    print_str("0");
    return;
  }


  while(num != 0){
    str[i] = (char) (num % 10) + '0';
    num = num - (num % 10);
    num = num / 10;
    i++ ;
  }

  int j = 0;
  i--;

  while(i >= 0){
    rev_str[j] = str[i];
    i--;
    j++;
  }

  rev_str[j] = 0;

  print_str(rev_str);

  return;
}

/* Main functions -------------------------- */

void print_longlong(unsigned long long n){

  struct bit_int {
    uint32_t low;
    uint32_t high;
  };

  union bit {
    unsigned long long int long_num;
    struct bit_int bit_num;
  } num;

  num.long_num = n;

  print_int(num.bit_num.low);
  print_str(" + 2^32*");
  print_int(num.bit_num.high);
  print_str("\n");

}

unsigned long long Atoll(char * str){
  int i = length(str)-1;
  unsigned long long num = 0;
  unsigned long long tens = 1;

  while(i >= 0){
    num = num + tens*(str[i] - '0');
    tens = 10*tens;
    i = i - 1;
  }

  return num;
}
