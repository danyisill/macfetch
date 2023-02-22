#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *gpu() {
  char buffer[4096]; // Increased buffer size to accommodate larger output
  FILE *fp = popen("system_profiler SPDisplaysDataType", "r"); // Removed grep filter
  if (fp == NULL) {
    return "N/A";
  }

  size_t bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp);
  pclose(fp);

  char *start = buffer;
  char *end;
  char *result = NULL;

  // Iterate through buffer and search for all instances of "Chipset Model"
  while ((start = strstr(start, "Chipset Model: ")) != NULL) {
    start += strlen("Chipset Model: ");
    end = strchr(start, '\n');
    int length = end - start;
    char *model = (char *) malloc(length + 1);
    memcpy(model, start, length);
    model[length] = '\0';

    if (result == NULL) {
      result = model;
    } else {
      char *temp = (char *) malloc(strlen(result) + length + 2);
      sprintf(temp, "%s, %s", result, model);
      free(result);
      free(model);
      result = temp;
    }

    start = end;
  }

  if (result == NULL) {
    return "N/A";
  } else {
    return result;
  }
}
//GPU detection rewrite
//author: Larry Bankovich/lennox <addaitech@gmail.com>
