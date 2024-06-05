/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The parse_file.c
*/
/**
 * @file parse_file.c
 * @brief The parse_file.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

void remove_comment(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == '#') {
            line[i] = '\0';
            return;
        }
    }
}

int error_handling(maze_t *maze, char **line, int line_index)
{
    if (line == NULL || line[0] == NULL) {
        my_fprintf(2, "Error: Line is empty: %d\n", line_index);
        return 1;
    }
    if (my_strcmp(line[0], "##end") == 0 && maze->end_find == 1) {
        my_fprintf(2, "Error: Multiple end rooms\n");
        return 1;
    }
    if (my_strcmp(line[0], "##end") == 0 && maze->end_find == 1) {
        my_fprintf(2, "Error: Multiple end rooms\n");
        return 1;
    }
    return 0;
}

static void move_file_content(linked_list_t **file_content)
{
    linked_list_t *tmp;

    while (*file_content && ((char *)(*file_content)->data)[0] == '#') {
        tmp = *file_content;
        *file_content = (*file_content)->next;
        (*file_content)->prev = NULL;
        FREE(tmp);
    }
}

int get_robots_numbers(maze_t *maze, linked_list_t **file_content)
{
    char **content;

    move_file_content(file_content);
    content = STR2ARRAY_SEP((*file_content)->data, " \t\n");
    if (content == NULL || content[0] == NULL ||
    my_array_len((void *)content) != 1) {
        return_and_free(maze, file_content, content);
        my_fprintf(2, "Error: Robots number is invalid\n");
        return 1;
    }
    maze->nb_robots = my_super_number(content[0], (NB){0, 0, 0, 0});
    if (maze->nb_robots < 1 || my_errno == 1) {
        return_and_free(maze, file_content, content);
        my_fprintf(2, "Error: Robots number is invalid\n");
        return 1;
    }
    (*file_content)->type = UNKNOWN;
    FREE_WORD_ARRAY(content);
    my_printf("#number_of_robots\n%d\n", maze->nb_robots);
    return 0;
}

int next_line(maze_t *maze, char **line)
{
    if (my_strcmp(line[0], "##start") == 0) {
        maze->start_find = 1;
        FREE_WORD_ARRAY(line);
        return 1;
    }
    if (my_strcmp(line[0], "##end") == 0) {
        maze->end_find = 1;
        FREE_WORD_ARRAY(line);
        return 1;
    }
    if (line[0][0] == '#') {
        FREE_WORD_ARRAY(line);
        return 1;
    }
    return 0;
}
