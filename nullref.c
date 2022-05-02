#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf(1, "Enter 'nullref {d}' where {d} is the decimal address to print");
    exit();
  }
  int addr = atoi(argv[1]);  // get the argument
  printf(1, "%x\n", *(int *)addr);  // print value at that address
  exit();
}
