#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int max_size_row = 0;    // Max Number of Rows
int max_size_col = 0;    // Max Number of Columns

// Define ANSI escape codes for styling
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

#include "Structure.h"
#include "csv_io.h"
#include "graph_fn.h"
#include "Indexing.h"
#include "Insert.h"
#include "Delete_fn.h"
#include "SelectToChange.h"
#include "Search.h"
#include "PrintTable.h"