/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The amazed.c
*/
/**
 * @file amazed.c
 * @brief The amazed.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

void amazed(maze_t *maze)
{
    my_printf("#moves\n");
    while (maze->robots_list != NULL) {
        move_robots(maze);
        remove_robots_at_end(maze->end, &maze->robots_list);
        my_putchar('\n');
    }
}
