/*
** EPITECH PROJECT, 2023
** amazed
** File description:
** The main file of the project
*/
/**
 * @file main.c
 * @brief The main file of the project
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

int main(int argc, char **argv)
{
    int result = 0;
    maze_t *maze;

    if (argc != 1) {
        my_fprintf(2, "Usage: ./amazed < [map]\n");
        return 84;
    }
    maze = init_maze();
    if (check_valid_maze(maze)) {
        my_free();
        return 84;
    }
    maze->robots_list = create_robots_list(maze->start, maze->nb_robots);
    amazed(maze);
    my_free();
    return maze->return_value;
}
