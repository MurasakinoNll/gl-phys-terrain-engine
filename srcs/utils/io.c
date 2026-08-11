#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
char *loadshader(const char *shadername){
  long len;
  FILE *fp = fopen(shadername, "r");
  if(fp == NULL){perror("failed to load shader path"); return NULL;} 
  fseek(fp, 0, SEEK_END); 
  if ((len = ftell(fp)) == -1){perror("ftell returned -1"); return NULL;}
  rewind(fp);
  char *buff = (char *)malloc(len + 1);
  if(buff == NULL){perror("bad malloc");fclose(fp); return NULL;}
  if ((fread(buff, 1, len, fp)) != (size_t)len){perror("failed fread"); return NULL;}
  buff[len]='\0';
  fclose(fp);
  return buff;
}
