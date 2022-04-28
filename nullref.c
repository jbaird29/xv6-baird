#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  void *nullptr = ((void*) 0);  // create a NULL pointer
  int i = *(int *)nullptr;
  i++;
  // printf(1, "%d", *(int *)nullptr);  // dereference and see what prints
  exit();
}
