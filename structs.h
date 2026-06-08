#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_options
{
    NONE = 0,
	LONG,
	RECURSIVE,
	ALL,
	REVERSE,
	TIME,
}	t_options;

typedef struct s_ls
{
    t_options options;
	// use a queue to store the sorted files and just print
	// all the files from the queue
}   t_ls;

#endif