/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The amazed.h
*/
/**
 * @file amazed.h
 * @brief The header of the amazed project
 * @author Nicolas TORO
 */

#include "mymemory.h"

#ifndef AMAZED_H_
    #define AMAZED_H_

/* Projects structures  */

typedef struct robot_s {
    void *room;
    int id;
    struct robot_s *prev;
    struct robot_s *next;
} robot_t;

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct door_s {
    void *room;
    struct door_s *next_door;
} door_t;

typedef struct room_s {
    char *room_name;
    position_t position;
    robot_t *robot;
    int waiting;
    int visited;
    struct door_s *doors_list;
    struct room_s *prev;
    struct room_s *next;
} room_t;

typedef struct path_s {
    room_t *room;
    int g_score; // Coût depuis le noeuds de départ jusqu'à ce node
    int f_score; // Coût total estimé depuis le départ
    // jusqu'à l'arrivée en passant par ce node
    struct path_s *prev; // Noeud précédent dans le chemin optimal
} path_t;

typedef struct path_info_s {
    room_t *start;
    room_t *end;
    my_bool_t only_free_room;
    int start_val;
    int nb_paths;
    linked_list_t *possible_paths;
    path_t *tmp;
} path_info_t;

typedef struct robot_path_s {
    path_t *path_wait;
    path_t *path;
    int path_wait_cost;
    int path_cost;
    room_t *room;
} robot_path_t;

typedef struct maze_s {
    int nb_robots;
    robot_t *robots_list;
    room_t *rooms_list;
    room_t *start;
    room_t *end;
    int start_find;
    int end_find;
    int return_value;
} maze_t;



/* Projects functions */

/* Parsing */
void remove_comment(char *line);
void *return_and_free(maze_t *maze, linked_list_t **file_content, char **line);
int add_door(maze_t *maze, char *line);
int add_room(maze_t *maze, char **line);
int check_line(maze_t *maze, char **line, int line_index);
int error_handling(maze_t *maze, char **line, int line_index);
int get_robots_numbers(maze_t *maze, linked_list_t **file_content);
int next_error_handling(maze_t *maze, char **line, int line_index);
int next_line(maze_t *maze, char **line);
int check_valid_maze(maze_t *maze);

/* Init maze */
maze_t *init_maze(void);
robot_t *create_robots_list(room_t *start, int nb_robots);

/* Path finding */
void display_path(path_t *path);
path_t *get_best_path(room_t *start, room_t *end, my_bool_t only_free_room);

/* Robots */
void remove_robots_at_end(room_t *end, robot_t **robots);
void reset_rooms(room_t *rooms);
void move_robots(maze_t *maze);

/* Exec amazed */
void amazed(maze_t *maze);

#endif /* AMAZED_H_ */
