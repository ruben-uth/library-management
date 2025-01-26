/**
 * @file input.h
 * @author ESTG
 * @brief This header file provides really useful functions to check is some 
 * strings and integers are valid.
 */

#ifndef INPUT_H
#define INPUT_H

void cleanInputBuffer();
int getInt(int minValue, int maxValue, char *msg);
void readString(char *string, unsigned int size, char *msg);

#endif /* INPUT_H */
