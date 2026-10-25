#include "lib.h"
#include "parser.h"

// TODO: Use Makefile and remove binary from src
int main(int argc, char **argv)
{
    t_args *args = parser(&argc, argv);
    printf("%d", args->time_to_debug);
    return (0);
}