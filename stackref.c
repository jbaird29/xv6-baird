#include "types.h"
#include "user.h"
#include "memlayout.h"
#include "mmu.h"
#include "memlayout.h"

void printStackRecursively(int n) {
  if(n == 0)
    return;
  uint stacktop = 0;
  if(stackaddr(&stacktop) < 0)
    return printf(1, "Error getting stack addresss.");
  printf(1, "%x\n", stacktop);
  return printStackRecursively(n-1);
}

void invalidArgChecking() {
  uint *argToCheck;
  argToCheck = (uint *)(PGSIZE - 1);
  if(stackaddr(argToCheck) < 0)
    printf(1, "Ensured an addr <PGSIZE is invalid\n");
  argToCheck = (uint *)(PGSIZE * 20);
  if(stackaddr(argToCheck) < 0)
    printf(1, "Ensured an addr >sz and <stack is invalid\n");
  argToCheck = (uint *)(USERTOP + 1);
  if(stackaddr(argToCheck) < 0)
    printf(1, "Ensured an addr >USERTOP is invalid\n");
}

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf(1, "Enter 'stackref {n}' where {n} is # of recursive calls");
    exit();
  }
  int n = atoi(argv[1]);  // get the argument
  printStackRecursively(n);
  invalidArgChecking();
  exit();
}
