/*
 Bookmark Sync Utility: Syncronize bookmarks accross computers on a LAN.
 Copyright © 2018 Andrew Hyatt
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _BSU_COMMON_H_
#define _BSU_COMMON_H_

#include <CoreFoundation/CoreFoundation.h>

/* The title of the bookmark folder */
#define BSU_ROOT_TITLE "Root";

enum bookmark_type
{
    bookmark_type_folder,
    bookmark_type_leaf
};
typedef enum bookmark_type bookmark_type;

struct folder_data
{
    struct bookmark_node* children;
    int auto_open_in_tabs;
};

struct leaf_data
{
    char *url;
};
    
union bookmark_data
{
    struct folder_data folder;
    struct leaf_data leaf;
};

/* The main datastructure for bookmarks. Each one is a linked list of
 bookmark_nodes that are in the same place in the bookmark hierarchy.
 */
struct bookmark_node
{
    char *title;
    bookmark_type type;
    union bookmark_data data;
    struct bookmark_node *next;
};

/* Loads the bookmarks from the local user into the bookmark datastructure */
struct bookmark_node* load_bookmarks(void);

/* Writes a human-readable representation of the bookmark hierarchy to stdout */
void print_bookmarks(const struct bookmark_node *tree_to_print);

#endif