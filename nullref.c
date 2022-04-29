#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int *nullptr = 0;  // create a NULL pointer
  for(int i = 0; i < (0x1000 / sizeof(int)); i++) {
    printf(1, "%d, ", *nullptr);  // dereference and see what prints
    nullptr++;
  }
  exit();
}
