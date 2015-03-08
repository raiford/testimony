#include <testimony.h>
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()
#include <stdlib.h>  // atoi()

int main(int argc, char** argv) {
  int r, i;
  struct tpacket_block_desc* block;
  int num;
  testimony t;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <socket> <num>\n", argv[0]);
  }
  num = atoi(argv[2]);

  printf("Init...\n");
  r = testimony_init(&t, argv[1], num);
  if (r < 0) {
    fprintf(stderr, "Error with init: %s\n", strerror(-r));
    return 1;
  }
  printf("Init complete\n");
  for (i = 0; i < 5; i++) {
    r = testimony_get_block(&t, &block);
    if (r < 0) {
      fprintf(stderr, "Error with get: %s\n", strerror(-r));
      return 1;
    }
    printf("%d\tgot block %p with %d packets\n", i, block,
           block->hdr.bh1.num_pkts);
    r = testimony_return_block(&t, block);
    if (r < 0) {
      fprintf(stderr, "Error with return: %s\n", strerror(-r));
      return 1;
    }
  }
  testimony_close(&t);
  return 0;
}