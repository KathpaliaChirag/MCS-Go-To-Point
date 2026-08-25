#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
  if(argc != 3) {
    printf(2, "Usage: chmod file mode\n");
    exit();
  }
  
  int mode = atoi(argv[2]);
  
  if(chmod(argv[1], mode) < 0) {
    printf(2, "chmod failed\n");
    exit();
  }
  
  exit();
}
