#include <stdio.h>
#include <string.h>

void print_binary(int *binary_buttons){
  for (int i=0; i < 16; i++) {
    printf("%i", binary_buttons[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]){
  struct button{
    char name[16];
    int binary[16];
  };

  struct button buttons[16] = {
    {"F1",     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F2",     {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F3",     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"F4",     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}},
    {"A1",     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
    {"A2",     {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}},
    {"A3",     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}},
    {"A4",     {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}},
    {"S1",     {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}},
    {"S2",     {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}},
    {"S3",     {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}},
    {"S4",     {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}},
    {"select", {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
    {"start",  {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}},
    {"C1",     {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}},
    {"C2",     {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}}
  };

  FILE *fp = fopen(argv[1], "r");
  char line[255];
  if (fp == NULL) {
    fprintf(stderr, "Can't open file\n");
    exit(1);
  }

  int l;
  for (int i=0; i<210; i++){
    l = fgets(line, 255, (FILE*)fp);
    if(l != NULL){
      if(strcmp(line, "\n") != 0){
        char delimiter[2] = ":";
        char *signifier = strtok(line, delimiter);
        char *signified = strtok(NULL, delimiter); // This feels wierd

        char keynames[16];
        char *key1 = strtok(signifier, "+");
        char *key2 = strtok(NULL, "+");
        char *key3 = strtok(NULL, "+");

        int merged[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        for(int i=0; i<16; i++){
          if(strcmp(key1, buttons[i].name) == 0){
            for(int j=0; j<16;j++){
              merged[j] = (merged[j] || buttons[i].binary[j]);
            }
          }
          if(key2 != NULL){
            if(strcmp(key2, buttons[i].name) == 0){
              for(int j=0; j<16;j++){
                merged[j] = (merged[j] || buttons[i].binary[j]);
              }
            }
          }
          if(key3 != NULL){
            if(strcmp(key3, buttons[i].name) == 0){
              for(int j=0; j<16;j++){
                merged[j] = (merged[j] || buttons[i].binary[j]);
              }
            }
          }
        }
        print_binary(merged);
      }
    }
  }

  return 0;
}
