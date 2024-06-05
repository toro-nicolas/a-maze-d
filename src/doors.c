/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The doors.c
*/
/**
 * @file doors.c
 * @brief The doors.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

int check_room_valid(maze_t *maze, char **content)
{
    int find = 0;

    for (room_t *tmp = maze->rooms_list; tmp && find != 2; tmp = tmp->next) {
        if (my_strcmp(tmp->room_name, content[0]) == 0 &&
        my_strcmp(tmp->room_name, content[1]) == 0)
            find++;
        if (my_strcmp(tmp->room_name, content[0]) == 0
        || my_strcmp(tmp->room_name, content[1]) == 0)
            find++;
    }
    if (find != 2)
        return 1;
    return 0;
}

int check_door_exist(room_t *first_room, room_t *second_room)
{
    door_t *tmp;

    for (tmp = first_room->doors_list; tmp; tmp = tmp->next_door)
        if (tmp->room == second_room)
            return 1;
    return 0;
}

void add_to_doors_list(door_t **begin, door_t *door)
{
    door_t *tmp;

    if (*begin == NULL) {
        *begin = door;
        return;
    }
    for (tmp = *begin; tmp->next_door != NULL; tmp = tmp->next_door);
    tmp->next_door = door;
}

void add_doors_to_rooms(maze_t *maze, char *left, char *right)
{
    room_t *room_left = NULL;
    room_t *room_right = NULL;
    door_t *new_door_left = my_malloc(sizeof(door_t), 1);
    door_t *new_door_right = my_malloc(sizeof(door_t), 1);

    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->room_name, left) == 0)
            room_left = tmp;
        if (my_strcmp(tmp->room_name, right) == 0)
            room_right = tmp;
    }
    new_door_left->room = room_right;
    new_door_right->next_door = NULL;
    new_door_right->room = room_left;
    new_door_left->next_door = NULL;
    my_printf("%s-%s\n", left, right);
    if (check_door_exist(room_left, room_right) || room_left == room_right)
        return;
    add_to_doors_list(&room_left->doors_list, new_door_left);
    add_to_doors_list(&room_right->doors_list, new_door_right);
}

int add_door(maze_t *maze, char *line)
{
    static int start = 1;
    char **content;

    remove_comment(line);
    content = STR2ARRAY_SEP(line, "-");
    if (my_array_len((void *)content) != 2 || my_count_letter(line, '-') != 1)
        return 1;
    if (check_room_valid(maze, content))
        return 1;
    if (start) {
        my_printf("#tunnels\n");
        start = 0;
    }
    add_doors_to_rooms(maze, content[0], content[1]);
    FREE_WORD_ARRAY(content);
    return 0;
}
