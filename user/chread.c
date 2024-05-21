// Simple grep.  Only supports ^ . * $ operators.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

char buf[1024];

void concat(char *str1, char *str2) {
    while (*str1) {
        str1++; // Move to the end of str1
    }
    
    while (*str2) {
        *str1 = *str2; // Copy character from str2 to str1
        str1++;
        str2++;
    }
    
    *str1 = '\0'; // Null-terminate the concatenated string
}

int
main(int argc, char *argv[])
{
  int fd;
  char *chid;
  char fname[50] = "channel_";
  char buf[50];

  if(argc != 2){
    fprintf(2, "usage: chread channel\n");
    exit(1);
  }

  chid = argv[1];
  concat(fname, chid);
  fd = open(fname, O_RDONLY);
  read(fd, buf, sizeof(buf));
  fprintf(2, "chread: %s\n", buf);
  close(fd);
  exit(0);
}

