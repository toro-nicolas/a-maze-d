/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The init_maze.c
*/
/**
 * @file init_maze.c
 * @brief The init_maze.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

int check_line(maze_t *maze, char **line, int line_index)
{
    int result = -1;

    if (maze->start_find == 1 && maze->end_find == 1) {
        my_fprintf(2, "Error: Start cannot be end:\n", line_index);
        return 1;
    }
    if (my_array_len((void *)line) == 1 || (my_array_len((void *)line) > 1 &&
    (my_str_contains(line[0], "#") || line[1][0] == '#')))
        result = add_door(maze, line[0]);
    if (my_array_len((void *)line) == 3 || (my_array_len((void *)line) > 3 &&
    (my_str_contains(line[2], "#") || line[3][0] == '#')))
        result = add_room(maze, line);
    if (result == 1 || result == -1) {
        my_fprintf(2, "Error: Line is invalid: %d\n", line_index);
        return 1;
    }
    maze->start_find = 0;
    maze->end_find = 0;
    return 0;
}

void *return_and_free(maze_t *maze, linked_list_t **file_content, char **line)
{
    for (linked_list_t *tmp = (*file_content); tmp; tmp = tmp->next)
        tmp->type = UNKNOWN;
    my_delete_list(file_content);
    maze->return_value = 84;
    FREE_WORD_ARRAY(line);
    return maze;
}

maze_t *parse_maze(maze_t *maze, linked_list_t *file_content)
{
    char **line;
    int line_index = 1;

    maze->return_value = 0;
    for (linked_list_t *tmp = file_content->next; tmp; tmp = tmp->next) {
        tmp->type = UNKNOWN;
        line_index++;
        line = STR2ARRAY_SEP(tmp->data, " \t\n");
        if (error_handling(maze, line, line_index))
            return return_and_free(maze, &file_content, line);
        if (next_line(maze, line))
            continue;
        if (check_line(maze, line, line_index))
            return return_and_free(maze, &file_content, line);
        FREE_WORD_ARRAY(line);
    }
    my_delete_list(&file_content);
    return maze;
}

static void display_file(linked_list_t *file_content)
{
    my_fprintf(2, "FILE CONTENT:\n");
    for (linked_list_t *tmp = file_content; tmp; tmp = tmp->next) {
        my_fprintf(2, "%s", (char *)tmp->data);
    }
    my_fprintf(2, "\nEND FILE CONTENT\n");
}

maze_t *init_maze(void)
{
    char *str = NULL;
    size_t size = 0;
    linked_list_t *file_content = NULL;
    maze_t *maze = my_malloc(sizeof(maze_t), 1);

    maze->start_find = 0;
    maze->end_find = 0;
    maze->rooms_list = NULL;
    maze->start = NULL;
    maze->end = NULL;
    while (getline(&str, &size, stdin) != EOF)
        my_push_back(&file_content, my_malloc_strdup(str), STRING);
    FREE(str);
    if (file_content == NULL)
        return NULL;
    if (get_robots_numbers(maze, &file_content))
        return maze;
    return parse_maze(maze, file_content);
}

int check_valid_maze(maze_t *maze)
{
    if (maze == NULL)
        return 1;
    if (maze->start == NULL || maze->end == NULL) {
        my_fprintf(2, "Error: No start or end found\n");
        return 1;
    }
    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next) {
        if (tmp->doors_list != NULL)
            break;
        if (tmp->next == NULL) {
            my_fprintf(2, "Error: No doors found\n");
            return 1;
        }
    }
    if (maze->start->doors_list == NULL || maze->end->doors_list == NULL ||
    get_best_path(maze->start, maze->end, FALSE) == NULL) {
        my_fprintf(2, "Error: Maze cannot be solved\n");
        return 1;
    }
    return 0;
}
