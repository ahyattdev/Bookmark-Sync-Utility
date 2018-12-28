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

#include <stdlib.h>
#include <CoreFoundation/CoreFoundation.h>
#include "bsuprivate.h"

struct bookmark_node* load_safari_bookmarks()
{
    CFStringRef errorString = NULL;
    CFURLRef bookmarksURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                                          CFSTR("~/Library/Safari/Bookmarks.plist"),
                                                          kCFURLPOSIXPathStyle,
                                                          FALSE);
    CFReadStreamRef bookmarksFile = CFReadStreamCreateWithFile(kCFAllocatorDefault, bookmarksURL);
    CFPropertyListFormat format;
    CFPropertyListRef plist = CFPropertyListCreateFromStream(kCFAllocatorDefault,
                                                             bookmarksFile,
                                                             0,
                                                             kCFPropertyListMutableContainersAndLeaves,
                                                             &format,
                                                             &errorString);
    CFDictionaryRef root;
    struct bookmark_node *root_node, *node;
    if (plist == NULL)
    {
        printf("Failed to load property list: %s", CFStringGetCStringPtr(errorString, kCFStringEncodingMacRoman));
    }
    
    /* Check root node type and cast property list */
    if (CFDictionaryGetTypeID() != CFGetTypeID(plist))
    {
        printf("Bookmarks property list root node is not a dictionary.\n");
    }
    
    root = (CFDictionaryRef) plist;
    
    /* Load the file version */
    /*if (!CFDictionaryGetValueIfPresent(root, BSUKeyFileVersion, &fileVersion))
    {
        printf("Failed to find file version.\n");
    }
    
    if (CFNumberGetTypeID() != CFGetTypeID((CFTypeRef)fileVersion))
    {
        printf("Failed to read file version key.\n");
    }*/
    
    /* Create root bookmark node */
    root_node = malloc(sizeof(*root_node));
    root_node->next = NULL;
    root_node->uuid = "Root";
    root_node->title = "";
    root_node->type = bookmark_type_root;
    root_node->data.root.children = NULL;
    
    CFRelease(plist);
    CFRelease(bookmarksFile);
    CFRelease(bookmarksURL);
    return root_node;
}