#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "meter.h"


bool _verbose = false;

int main(int argc, char *argv[]) {

  uint32_t window_size = 32;
  char *input_file = NULL;

  if(argc <= 1){
    printf("Usage: meter [-w WINDOW_SIZE] [-v] INPUT_FILE\n");
    return -1;
  }
  opterr = 0;
  int c;
  while ((c = getopt (argc, argv, "w:")) != -1){
    switch (c) {
      case 'v':
        _verbose = true;
      break;
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

  return process_file(input_file, window_size);
}

int process_file(char *input_file, uint32_t window_size){
  
  FILE *fp;
  char *file_content;
  long length;

  if(_verbose){
    printf("Open file: %s\n", input_file);
  }
  fp = fopen(input_file, "r");
  if(fp){
    fseek (fp, 0, SEEK_END);
    length = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    file_content = malloc (length);
    if (file_content)
    {
      fread (file_content, 1, length, fp);
    }
    fclose(fp);
  }else{
    fprintf(stderr, "Could not open file '%s\'\n", input_file);
    return -2;
  }

  if(file_content == NULL){
    fprintf(stderr, "No data read from file '%s'\n", input_file);
    return -2;
  }

  remove_nonalpha(file_content);

  for(int i = 0; file_content[i]; i++){
    file_content[i] = tolower(file_content[i]);
  }
  
  printf("%s", file_content);

  return 0;
}


void remove_nonalpha(char *str)
{
    unsigned long i = 0;
    unsigned long j = 0;
    char c;

    while ((c = str[i++]) != '\0')
    {
        if (isalpha(c) || c == ' ')
        {
            str[j++] = c;
        }
    }
    str[j] = '\0';
}
