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

typedef int bookmark_type_t;
enum bookmark_type
{
    bookmark_type_folder,
    bookmark_type_leaf,
    bookmark_type_root
};

struct folder_data
{
    struct bookmark_node* children;
    int auto_open_in_tabs;
};

struct leaf_data
{
    char *url;
};

/* Something like History, Bookmarks Bar, Address Book, etc */
struct proxy_data
{
    char *identifier;
};

struct root_data
{
    struct bookmark_node* children;
};
    
union bookmark_data
{
    struct folder_data folder;
    struct leaf_data leaf;
    struct root_data root;
};

/* The main datastructure for bookmarks. Each one is a linked list of
 bookmark_nodes that are in the same place in the bookmark hierarchy.
 */
struct bookmark_node
{
    char *uuid;
    char *title;
    bookmark_type_t type;
    union bookmark_data data;
    struct bookmark_node *next;
};

/* Loads the bookmarks from the local user into the bookmark datastructure */
struct bookmark_node* load_bookmarks(void);

#endif