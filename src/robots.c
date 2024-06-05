/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The robots.c
*/
/**
 * @file robots.c
 * @brief The robots.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

/**
 * @brief Create a list of robots
 * @param start The room where the robots start
 * @param nb_robots The number of robots
 * @return <b>robot_t *</b> The list of robots
 * @author Nicolas TORO
 */
robot_t *create_robots_list(room_t *start, int nb_robots)
{
    robot_t *robots = MALLOC(sizeof(robot_t));
    robot_t *tmp = robots;

    robots->id = 1;
    robots->room = start;
    robots->prev = NULL;
    robots->next = NULL;
    for (int i = 1; i < nb_robots; i++) {
        tmp->next = MALLOC(sizeof(robot_t));
        tmp->next->prev = tmp;
        tmp = tmp->next;
        tmp->id = i + 1;
        tmp->room = start;
        tmp->next = NULL;
    }
    return robots;
}

/**
 * @brief Remove the robots at the end of the maze
 * @param end The end room
 * @param robots The list of robots
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void remove_robots_at_end(room_t *end, robot_t **robots)
{
    for (robot_t *tmp = *robots; tmp; tmp = tmp->next) {
        if (tmp->room != end)
            continue;
        if (tmp->prev == NULL)
            *robots = tmp->next;
        if (tmp->prev == NULL && tmp->next != NULL)
            tmp->next->prev = NULL;
        if (tmp->prev != NULL)
            tmp->prev->next = tmp->next;
        if (tmp->prev != NULL && tmp->next)
            tmp->next->prev = tmp->prev;
    }
}

robot_path_t *create_robot_path(room_t *rooms_list,
    robot_t *robot, room_t *end)
{
    robot_path_t *robot_path = MALLOC(sizeof(robot_path_t));

    robot_path->path_wait_cost = 0;
    robot_path->path_cost = 0;
    robot_path->room = NULL;
    reset_rooms(rooms_list);
    robot_path->path_wait = get_best_path(robot->room, end, FALSE);
    reset_rooms(rooms_list);
    robot_path->path = get_best_path(robot->room, end, TRUE);
    return robot_path;
}

/**
 * @brief Get the next room of the robot
 * @note en gros, on a deux chemin possible. Soit on cherche le meilleure
 * chemin en esquivant les room pleine, soit on cherche le chemin le plus court
 * en passant par les room pleine et en comptant le nombre de tour qu'on va
 * attendre dans la dernière room
 * @param rooms_list The list of rooms
 * @param robot The robot
 * @param end The end room
 * @return <b>room_t *</b> The next room of the robot
 * @author Nicolas TORO
 */
room_t *get_next_robot_room(room_t *rooms_list, robot_t *robot, room_t *end)
{
    robot_path_t *robot_path = create_robot_path(rooms_list, robot, end);

    for (path_t *tmp = robot_path->path_wait; tmp; tmp = tmp->prev) {
        robot_path->path_wait_cost++;
        if (tmp->prev != NULL && tmp->prev->prev == NULL)
            robot_path->room = tmp->room;
    }
    if (robot_path->path_wait_cost <= 2 || robot_path->room == NULL)
        return end;
    for (path_t *tmp = robot_path->path; tmp; tmp = tmp->prev)
        robot_path->path_cost++;
    if (robot_path->path == NULL || robot_path->path_wait_cost + 1
    + robot_path->room->waiting < robot_path->path_cost)
        return robot_path->room;
    for (path_t *tmp = robot_path->path; tmp; tmp = tmp->prev) {
        if (tmp->prev != NULL && tmp->prev->prev == NULL)
            robot_path->room = tmp->room;
    }
    return robot_path->room;
}

/**
 * @brief Display the moves of the robot
 * @param maze The maze
 * @param room The new room of the robot
 * @param tmp The robot
 * @param start The start value to know if we need to display a space
 * @return <b>void</b>
 * @author Nicolas TORO
 */
static void display_moves(maze_t *maze, room_t *room, robot_t *tmp, int *start)
{
    if (room->robot != NULL && maze->end != room && tmp->room == maze->start)
        return;
    if (*start == 0)
        my_putchar(' ');
    *start = 0;
    my_printf("P%d-%s", tmp->id, ((room_t *)tmp->room)->room_name);
}

/**
 * @brief Move the robots
 * @param maze The maze
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void move_robots(maze_t *maze)
{
    int start = 1;
    room_t *room = NULL;

    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next) {
        tmp->robot = NULL;
        tmp->waiting = 0;
    }
    for (robot_t *tmp = maze->robots_list; tmp; tmp = tmp->next) {
        room = get_next_robot_room(maze->rooms_list, tmp, maze->end);
        if (room->robot != NULL && maze->end != room)
            room->waiting++;
        else
            tmp->room = room;
        ((room_t *)tmp->room)->robot = tmp;
        display_moves(maze, room, tmp, &start);
    }
}
