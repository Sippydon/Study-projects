#include "flags.h"

//#include "grep_func.h"
#include "regex.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Exeptions {
  int regcopm_exeptions;
  int file_not_found_exeptions;
};
int hasExeptions(struct Exeptions exeptions);
void printError(struct Exeptions exeptions, struct Flags flags,
                char *file_name);
int eHandler(regex_t *regex, char *buffer, size_t size, regmatch_t matches[],
             int *string_counter, int *match_string_counter,
             struct Flags flags);

void oHandler(regmatch_t matches[], char *buffer, regex_t regex, size_t size,
              struct Flags flags, int h, int string_counter, char *file_name);

void output(char *file_name, char *buffer, struct Flags flags,
            int string_counter, int match_string_counter, int h);

int flagHandler(int argc, char *argv[], struct Flags flags, int option_index) {
  struct Exeptions exeptions = {0, 0};
  char *buffer = NULL;
  int success = 0;
  int string_counter = 0;
  int match_string_counter = 0;
  size_t size = 1;
  size_t unused;
  regmatch_t matches[1];
  regex_t regex;
  int single = 1;

  FILE *file;
  if (flags.f == 0) {
    if (flags.i == 1) {
      success = regcomp(&regex, flags.pattern, REG_ICASE | REG_EXTENDED);
    } else {
      success = regcomp(&regex, flags.pattern, REG_EXTENDED);
    }
    if (success == 1) {
      exeptions.regcopm_exeptions = 1;
    }
  } else {
    FILE *regex_file;
    unsigned long tmp_len;
    int flag = 1;
    char *tmp_buffer = NULL;
    regex_file = fopen(flags.file_name, "r");

    if (regex_file != NULL) {
      fseek(regex_file, 0, SEEK_END);
      long file_size = ftell(regex_file);
      fseek(regex_file, 0, SEEK_SET);

      char *tmp_pattern = (char *)malloc(file_size + 1);

      while (getline(&tmp_buffer, &unused, regex_file) != -1) {
        tmp_len = strlen(tmp_buffer);

        if (tmp_buffer[tmp_len - 1] == '\n') {
          tmp_buffer[tmp_len - 1] = '\0';
        }

        if (flag == 1) {
          strcat(tmp_pattern, tmp_buffer);
          flag = 0;
        } else {
          strcat(tmp_pattern, "|");
          strcat(tmp_pattern, tmp_buffer);
        }
      }

      if (flags.i == 1) {
        success = regcomp(&regex, tmp_pattern, REG_ICASE | REG_EXTENDED);
      } else {
        success = regcomp(&regex, tmp_pattern, REG_EXTENDED);
      }
      if (success == 1) {
        exeptions.regcopm_exeptions = 1;
      }

      free(tmp_pattern);
      free(tmp_buffer);
      fclose(regex_file);

    } else {
      exeptions.file_not_found_exeptions = 1;
    }
  }
  if (hasExeptions(exeptions) == 0) {
    int h = argc - option_index;
    while (option_index != argc) {
      if (argv[option_index][0] == '-') {
        if (argv[option_index][1] == 'e' || argv[option_index][1] == 'f') {
          option_index += 2;
        } else {
          option_index++;
        }
      } else if (((file = fopen(argv[option_index], "r")) != NULL)) {
        while ((getline(&buffer, &unused, file)) != -1 && single) {
          if ((flags.o == 0 || (flags.v == 1 && flags.o == 1))) {
            success = eHandler(&regex, buffer, size, matches, &string_counter,
                               &match_string_counter, flags);
            if (success == 0 && flags.c == 0 && flags.l == 0) {
              output(argv[option_index], buffer, flags, string_counter,
                     match_string_counter, h);
            }
          } else if (flags.o == 1 && flags.c == 0) {
            oHandler(matches, buffer, regex, size, flags, h, string_counter,
                     argv[option_index]);
          }
          if (flags.l == 1) {
            if (success == 0 && flags.l == 1) {
              output(argv[option_index], buffer, flags, string_counter,
                     match_string_counter, h);
              single = 0;
            }
          }
        }

        if (flags.c == 1) {
          output(argv[option_index], buffer, flags, string_counter,
                 match_string_counter, h);
        }

        option_index += 1;
        string_counter = 0;
        match_string_counter = 0;

        fclose(file);

      } else {
        exeptions.file_not_found_exeptions = 1;
        printError(exeptions, flags, argv[option_index]);
        exeptions.file_not_found_exeptions = 0;
        option_index++;
      }
      single = 1;
    }
  }

  printError(exeptions, flags, argv[option_index]);
  regfree(&regex);
  free(buffer);

  return 0;
}

int eHandler(regex_t *regex, char *buffer, size_t size, regmatch_t matches[],
             int *string_counter, int *match_string_counter,
             struct Flags flags) {
  int match_result;

  match_result = regexec(regex, buffer, size, matches, 1);

  if (flags.v == 0) {
    if (match_result == 0) {
      *string_counter += 1;
      *match_string_counter += 1;
      match_result = 0;
    } else {
      *string_counter += 1;
      match_result = 1;
    }
  } else if (flags.v == 1) {
    if (match_result == REG_NOMATCH) {
      *string_counter += 1;
      *match_string_counter += 1;
      match_result = 0;
    } else {
      *string_counter += 1;
      match_result = 1;
    }
  }

  return match_result;
}

void oHandler(regmatch_t matches1[], char *buffer, regex_t regex, size_t size,
              struct Flags flags, int h, int string_counter, char *file_name) {
  int match = 0;
  regmatch_t matches[1];

  while (match == 0) {
    match = regexec(&regex, buffer, size, matches, 1);

    if (match == 0) {
      if (flags.l == 0) {
        if (flags.h == 0 && h > 1) {
          if (flags.n == 1) {
            printf("%d:", string_counter);
            printf("%s:", file_name);
            for (int i = matches->rm_so; i < matches->rm_eo; i++) {
              printf("%c", buffer[i]);
            }
            printf("\n");
            buffer += matches[0].rm_eo;
          } else {
            printf("%s:", file_name);
            for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
              printf("%c", buffer[i]);
            }
            buffer += matches[0].rm_eo;
            printf("\n");
          }
        } else if (h <= 1) {
          if (flags.n == 1) {
            printf("%d:", string_counter);
            for (int i = matches->rm_so; i < matches->rm_eo; i++) {
              printf("%c", buffer[i]);
            }
            //            printf("\n%s\n", buffer);
            printf("\n");
          } else {
            for (int i = matches->rm_so; i < matches->rm_eo; i++) {
              printf("%c", buffer[i]);
            }
            printf("\n");
          }
          buffer += matches[0].rm_eo;
        }
      }
    }
  }
}

void output(char *file_name, char *buffer, struct Flags flags,
            int string_counter, int match_string_counter, int h) {
  unsigned long len = strlen(buffer);

  if (buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
  }

  if (flags.h == 0 && h > 1) {
    if (flags.c == 1) {
      printf("%s:", file_name);
      printf("%d\n", match_string_counter);
    } else if (flags.n == 1 && flags.o == 0) {
      printf("%s:", file_name);
      printf("%d:", string_counter);
      printf("%s\n", buffer);
    } else if (flags.l == 0) {
      printf("%s:", file_name);
      printf("%s\n", buffer);
    }
    if (flags.l == 1 && flags.c == 0) {
      printf("%s\n", file_name);
    }
  } else if (flags.h == 1 || h <= 1) {
    if (flags.c == 1) {
      printf("%d\n", match_string_counter);
    } else if (flags.n == 1 && flags.o == 0) {
      printf("%d:", string_counter);
      printf("%s\n", buffer);
    } else if (flags.l == 0) {
      printf("%s\n", buffer);
    }
    if (flags.l == 1 && flags.c == 0) {
      printf("%s\n", file_name);
    }
  }
}

int hasExeptions(struct Exeptions exeptions) {
  int has_exeptions = 0;
  if (exeptions.regcopm_exeptions) {
    has_exeptions = 1;
  }
  if (exeptions.file_not_found_exeptions) {
    has_exeptions = 1;
  }

  return has_exeptions;
}

void printError(struct Exeptions exeptions, struct Flags flags,
                char *file_name) {
  if (exeptions.regcopm_exeptions) {
    fprintf(stderr, "Wrong regular expression\n");
  }
  if (exeptions.file_not_found_exeptions && flags.s == 0) {
    fprintf(stderr, "grep: %s: No such file\n", file_name);
  }
}