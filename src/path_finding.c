/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** The path_finding.c
*/
/**
 * @file path_finding.c
 * @brief The path_finding.c
 * @author Nicolas TORO
 */

#include "../include/amazed.h"

/**
 * @brief Get the heuristic distance between two rooms
 * @note In our case, the heuristic distance is the number of iterations
 * to go from one room to the end room
 * @param start The starting room
 * @param end The ending room
 * @return <b>int</b> The heuristic distance (if the room is connected
 * to the end room, then the number of iterations, else -1)
 * @author Nicolas TORO
 */
int get_heuristic_distance(room_t *start, room_t *end)
{
    int distance = 1;

    if (start == end)
        return 0;
    for (door_t *door = start->doors_list; door; door = door->next_door) {
        if (door->room == end)
            return distance;
        distance++;
    }
    return -1;
}

/**
 * @brief Create a path node
 * @param start The starting room
 * @param end The ending room
 * @return <b>path_t *</b> The created node
 * @author Nicolas TORO
 */
static path_t *create_path(room_t *start, room_t *end)
{
    path_t *start_node = MALLOC(sizeof(path_t));

    start_node->room = start;
    start_node->g_score = 0;
    start_node->f_score = 0;
    start_node->prev = NULL;
    return start_node;
}

/**
 * @brief Get the node with the lowest score in the possible paths list
 * @param possible_paths The list of possible paths
 * @return <b>path_t *</b> The node with the lowest score
 * @author Nicolas TORO
 */
path_t *get_lowest_score_node(linked_list_t *possible_paths)
{
    path_t *lowest_node = NULL;

    for (linked_list_t *tmp = possible_paths; tmp; tmp = tmp->next) {
        if (lowest_node == NULL ||
            ((path_t *)tmp->data)->f_score < lowest_node->f_score)
            lowest_node = tmp->data;
    }
    return lowest_node;
}

/**
 * @brief Browse the neighbors of a room and create a path node for each
 * neighbor room and add them to possible paths
 * @param path_info The path information
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void browse_neighbors(path_info_t *path_info)
{
    path_t *new_path;
    int cost = 0;

    for (door_t *door = path_info->tmp->room->doors_list;
    door; door = door->next_door) {
        if (((room_t *)door->room)->visited || door->room == path_info->start
        || (path_info->only_free_room && path_info->tmp->prev == NULL &&
        door->room != path_info->end && ((room_t *)door->room)->robot != NULL))
            continue;
        new_path = create_path(door->room, path_info->end);
        new_path->prev = path_info->tmp;
        new_path->g_score = path_info->tmp->g_score + 1;
        cost = get_heuristic_distance(door->room, path_info->end);
        new_path->f_score = (cost == -1) ? new_path->g_score : MIN_INT + cost;
        if (my_find_node(path_info->possible_paths, new_path, NULL) == NULL) {
            path_info->nb_paths++;
            my_push_back(&path_info->possible_paths, new_path, UNKNOWN);
        }
    }
}

/**
 * @brief Get the best path between two rooms
 * @param start The starting room
 * @param end The ending room
 * @param only_free_room If we only want to browse free rooms
 * @return <b>path_t *</b> The best path found (NULL if no path found)
 * @author Nicolas TORO
 */
path_t *get_best_path(room_t *start, room_t *end, my_bool_t only_free_room)
{
    path_info_t path_info = {start, end, only_free_room, 1, 1, NULL, NULL};

    my_push_front(&path_info.possible_paths, create_path(start, end), UNKNOWN);
    while (path_info.nb_paths > 0) {
        path_info.tmp = get_lowest_score_node(path_info.possible_paths);
        if (path_info.start_val == 0 && path_info.tmp->room == start)
            return NULL;
        path_info.start_val = 0;
        if (path_info.tmp->room == end) {
            my_delete_list(&path_info.possible_paths);
            return path_info.tmp;
        }
        path_info.nb_paths--;
        my_delete_nodes(&path_info.possible_paths, path_info.tmp, NULL);
        path_info.tmp->room->visited = 1;
        browse_neighbors(&path_info);
    }
    my_delete_list(&path_info.possible_paths);
    return NULL;
}

/**
 * @brief Display the path found
 * @param path The path to display
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void display_path(path_t *path)
{
    if (path == NULL) {
        my_printf("No path found\n");
        return;
    }
    for (path_t *tmp = path; tmp; tmp = tmp->prev) {
        my_printf("%s", tmp->room->room_name);
        if (tmp->prev)
            my_printf(" <- ");
    }
    my_putchar('\n');
}
