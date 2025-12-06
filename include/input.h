// Include Guard, prevents compilation errors
#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"

/**
 * @brief Reads an entire file and converts it into a string.
 *
 * Opens the specified file in binary read mode and finds its size
 * so it can allocate the correct amount of memory.
 *
 * @param filename Name of the file that will be read.
 * @param file_size Pointer to an external variable to track size of the file.
 * @return Character array (string) if successful, NULL if it failed.
 */
char* read_input(const char* filename, long* file_size);

#endif // Closes INPUT_H include guard
