#include "types.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
  if(argc != 2) {
    printf(2, "Usage: block syscall_id\n");
    exit();
  }
  int id = atoi(argv[1]);
  if(block(id) == 0)
    printf(1, "Syscall %d is now blocked\n", id);
  else
    printf(2, "Failed to block syscall %d\n", id);
  exit();
}
