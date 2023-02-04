#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *gpu() {
  char buffer[1024];
  FILE *fp = popen("system_profiler SPDisplaysDataType | grep \"Chipset Model\"", "r");
  if (fp == NULL) {
    return "N/A";
  }

  fread(buffer, sizeof(char), sizeof(buffer), fp);
  pclose(fp);

  char *start = strstr(buffer, ": ") + 2;
  char *end = strchr(start, '\n');
  int length = end - start;
  char result[length + 1];
  memcpy(result, start, length);
  result[length] = '\0';

  return strdup(result);
}