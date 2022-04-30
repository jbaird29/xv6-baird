#include "types.h"
#include "user.h"
#include "memlayout.h"

int main(int argc, char *argv[])
{
  int *topptr = (int *)(USERTOP - 4);  // pointer to the top user-space address
  *topptr = 100;
  int childPID = fork();
  if(childPID == 0) {
      printf(1, "Child: %d\n", *topptr);
  } else {
      wait();
      printf(1, "Parent: %d\n", *topptr);
  }
  exit();
}
