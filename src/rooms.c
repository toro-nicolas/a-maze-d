/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The rooms.c
*/
/**
 * @file rooms.c
 * @brief The rooms.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

int check_end_start(maze_t *maze, room_t *room)
{
    if (maze->start_find) {
        if (maze->start != NULL)
            return 1;
        maze->start = room;
        my_printf("##start\n");
    }
    if (maze->end_find) {
        if (maze->end != NULL)
            return 1;
        maze->end = room;
        my_printf("##end\n");
    }
    my_printf("%s %d %d\n", room->room_name,
        room->position.x, room->position.y);
    return 0;
}

room_t *add_to_rooms_list(maze_t *maze, char *name, position_t position)
{
    room_t *new_room = my_malloc(sizeof(room_t), 1);
    room_t *tmp;

    new_room->room_name = my_malloc_strdup(name);
    new_room->position = position;
    new_room->robot = NULL;
    new_room->waiting = 0;
    new_room->visited = 0;
    new_room->doors_list = NULL;
    new_room->next = NULL;
    new_room->prev = NULL;
    if (maze->rooms_list == NULL) {
        maze->rooms_list = new_room;
        return new_room;
    }
    for (tmp = maze->rooms_list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_room;
    new_room->prev = tmp;
    return new_room;
}

int add_room(maze_t *maze, char **line)
{
    static int start = 1;
    position_t position;

    if (start)
        my_printf("#rooms\n");
    start = 0;
    position.x = my_super_number(line[1], (NB){0, 0, 0, 0});
    if (my_errno != 0 ||
    (my_strlen(line[1]) == 1 && my_str_contains(line[1], "-+") == 1))
        return 1;
    remove_comment(line[2]);
    position.y = my_super_number(line[2], (NB){0, 0, 0, 0});
    if (my_errno != 0 ||
    (my_strlen(line[2]) == 1 && my_str_contains(line[2], "-+") == 1))
        return 1;
    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next)
        if (my_strcmp(tmp->room_name, line[0]) == 0 ||
        (tmp->position.x == position.x && tmp->position.y == position.y))
            return 1;
    return check_end_start(maze, add_to_rooms_list(maze, line[0], position));
}

/**
 * @brief Reset the visited attribute of each rooms
 * @param rooms The list of rooms
 * @return <b>void</b>
 */
void reset_rooms(room_t *rooms)
{
    for (room_t *tmp = rooms; tmp; tmp = tmp->next)
        tmp->visited = 0;
}
