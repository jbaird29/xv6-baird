#include "types.h"
#include "user.h"
#include "pstat.h"
#include "param.h"


int main(int argc, char *argv[])
{
  int i;
  struct pstat stat;
  if(getpinfo(&stat) < 0) {
    printf(1, "Error");
    return -1;
  }
  
  for(i = 0; i < NPROC; i++) {
      if(stat.inuse[i])
        printf(1, "PID: %d | High Ticks: %d | Low Ticks: %d | Name: %s\n", stat.pid[i], stat.hticks[i], stat.lticks[i], stat.name[i]);
  }
    
  exit();
}
