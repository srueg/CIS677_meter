
#include "meter.h"

/* enable verbose output */
bool verbose = false;

/* counts occurrences of distinct words over the whole text */
word_count_t *word_counters_total = NULL;
/* counts occurrences of distinct words within the sliding window */
word_count_t *word_counters_local = NULL;

int main(int argc, char *argv[]) {

  /* default size of sliding window = 32 words */
  uint32_t window_size = WINDOW_SIZE;
  char *input_file = NULL;

  /* START process input arguments */
  if(argc <= 1){
    printf("Usage: meter [-w WINDOW_SIZE=32words] [-v VERBOSE] INPUT_FILE\n");
    return -1;
  }
  opterr = 0;
  int c;
  while ((c = getopt (argc, argv, "w:v")) != -1){
    switch (c) {
      case 'v':
        verbose = true;
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
  /* END process input arguments */

  return process_file(input_file, window_size);
}

/*
 * Function: process_file
 * ----------------------------
 *   Processes a given text-file and calculates its local and global complexity.
 *
 *   input_file: the text-file to process
 *   window_size: the size for the sliding-window to calculate the local complexity
 *
 *   returns: statuscode, 0=successfull, <0=error
 */

int process_file(char *input_file, uint32_t window_size){
  
  FILE *fp;
  char *file_content;
  long length;

  if(verbose){
    printf("Open file: %s.\n", input_file);
  }
  fp = fopen(input_file, "r");
  if(fp){
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    file_content = malloc (length);
    if (file_content)
    {
      fread(file_content, 1, length, fp);
    }
    fclose(fp);
  }else{
    fprintf(stderr, "Could not open file '%s\'.\n", input_file);
    return -2;
  }

  if(file_content == NULL){
    fprintf(stderr, "No data read from file '%s'.\n", input_file);
    return -2;
  }

  /* remove non-alphabetic characters from text */
  remove_nonalpha(file_content);

  /* convert all text to lowercase */
  for(int i = 0; file_content[i]; i++){
    file_content[i] = tolower(file_content[i]);
  }
  if(verbose){
    printf("Cleaned file content.\n");
  }

  /* process text word by word */

  uint32_t total_word_count = 0;
  char *word = strtok(file_content," ");
   
  while(word != NULL){
    increase_word_count(&word_counters_local, word);
    increase_word_count(&word_counters_total, word);
    total_word_count++;
    if(total_word_count % window_size == 0){
      /* calculate local complexity for current window */
      double local_complexity = (double)get_word_count(&word_counters_local) / window_size;
      printf("Window %i: local complexity: %f\n", total_word_count/window_size, local_complexity);
      clear_word_counts(&word_counters_local);
    }
    word = strtok(NULL, " ");
  }

  uint32_t distinct_word_count = get_word_count(&word_counters_total);
  /* calculate total complexity */
  double total_complexity = (double)distinct_word_count / total_word_count;

  printf("Distinct words: %i, total words: %i, total complexity: %f\n", distinct_word_count, total_word_count, total_complexity);

  return 0;
}


