#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int *nullptr = 0;  // create a NULL pointer
  printf(1, "%d", *nullptr);  // dereference and see what prints
  exit();
}
