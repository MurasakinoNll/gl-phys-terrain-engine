#include <stdio.h>
#include <stdlib.h>
char *loadshader(const char *shadername){
  FILE *fp = fopen(shadername, "r");
  if(fp == NULL){perror("failed to load shader path"); return NULL;} 
  fseek(fp, 0, SEEK_END); long len = ftell(fp);
  rewind(fp);
  char *buff = (char *)malloc(len + 1);
  if(buff == NULL){perror("bad malloc");fclose(fp); return NULL;}
  fread(buff, 1, len, fp);
  buff[len]='\0';
  fclose(fp);
  return buff;
}
