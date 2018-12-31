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

#include "bsuprivate.h"

static void print_bookmarks_helper(const struct bookmark_node *tree_to_print,
                                   int depth);

void print_bookmarks(const struct bookmark_node *tree_to_print)
{    
    print_bookmarks_helper(tree_to_print, 0);
}

static void print_bookmarks_helper(const struct bookmark_node *tree_to_print,
                                   int depth)
{
    int i;
    struct bookmark_node *travel;
    
    if (tree_to_print->type == bookmark_type_folder)
    {
        printf("%s:\n", tree_to_print->title);
        depth++;
        travel = tree_to_print->data.folder.children;
        while (travel != NULL)
            print_bookmarks_helper(travel++, depth);
    }
    else if (tree_to_print->type == bookmark_type_leaf)
    {
        /* Print tabs */
        for (i = 0; i < depth; i++)
            printf("\t");
        
        /* Print bookmark title */
        printf("%s: %s\n", tree_to_print->title, tree_to_print->data.leaf.url);
    }
    else
    {
        printf("Unknown bookmark type.\n");
    }
}