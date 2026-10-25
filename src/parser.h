#ifndef PARSER_H
#define PARSER_H

typedef struct args
{
    unsigned int nb_of_coders;
    unsigned int nb_dongles;
    unsigned int time_to_burnout;
    unsigned int time_to_compile;
    unsigned int time_to_debug;
    unsigned int time_to_refractor;
    unsigned int nb_of_compile_required;
    unsigned int dongle_cooldown;
    char *scheduler;
} t_args;

t_args *parser(int *argc, char **argv);

#endif