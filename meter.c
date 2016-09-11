#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[]) {

  uint32_t window_size = 32;
  char *input_file = NULL;
  int c;

  if(argc <= 1){
    printf("Usage: meter [-w WINDOW_SIZE] INPUT_FILE\n");
    return -1;
  }
  opterr = 0;
  while ((c = getopt (argc, argv, "w:")) != -1){
    switch (c) {
      case 'w':
        if(sscanf(optarg, "%d", &window_size) <= 0){
          fprintf(stderr, "window_size must be a positive number.\n");
          return -1;
        }
        break;
      case '?':
        if (optopt == 'w')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
           "Unknown option character `\\x%x'.\n",
           optopt);
        return 1;
      default:
      abort ();
    }
  }

  input_file = argv[optind];

  if(input_file == NULL){
    printf("Input file requierd!\n");
    return -1;
  }


  FILE *fp;

  printf("input file: %s, window size: %i\n", input_file, window_size);

  fp = fopen(input_file, "r");

  fclose(fp);
}
