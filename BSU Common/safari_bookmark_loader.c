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

#define SAFARI_BOOKMARKS_PATH "/Library/Safari/Bookmarks.plist"

struct bookmark_node* load_safari_bookmarks()
{
    CFStringRef error_string = NULL, bookmarks_path;
    CFURLRef bookmarks_url;
    CFReadStreamRef bookmarks_read_stream;
    CFPropertyListFormat format;
    CFPropertyListRef plist;
    CFDictionaryRef root;
    struct bookmark_node *root_node, *node;
    CFErrorRef error = NULL;
    int status;
    char *home_folder, *full_path;
    
    home_folder = getenv("HOME");
    if (home_folder == NULL)
    {
        printf("Failed to get HOME environmental variable.\n");
        exit(EXIT_FAILURE);
    }
    full_path = malloc(strlen(SAFARI_BOOKMARKS_PATH)+strlen(home_folder)+1);
    strcpy(full_path, home_folder);
    strcpy(full_path+strlen(home_folder), SAFARI_BOOKMARKS_PATH);
    bookmarks_path = CFStringCreateWithCString(kCFAllocatorDefault,
                                              full_path,
                                              kCFStringEncodingMacRoman);
    
    bookmarks_url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                                  bookmarks_path,
                                                  kCFURLPOSIXPathStyle,
                                                  FALSE);
    bookmarks_read_stream = CFReadStreamCreateWithFile(kCFAllocatorDefault, bookmarks_url);
    CFReadStreamOpen(bookmarks_read_stream);
    /*CFRunLoopRun();*/
    
    while ((status = CFReadStreamGetStatus(bookmarks_read_stream)) != kCFStreamStatusOpen && status != kCFStreamStatusError);
    
    if (status == kCFStreamStatusError)
    {
        error = CFReadStreamCopyError(bookmarks_read_stream);
    }
    
    plist = CFPropertyListCreateFromStream(kCFAllocatorDefault,
                                   bookmarks_read_stream,
                                   0,
                                   kCFPropertyListImmutable,
                                   &format,
                                   &error_string);
    
    
    CFReadStreamClose(bookmarks_read_stream);
    
    if (plist == NULL)
    {
        printf("Failed to load property list: %s", CFStringGetCStringPtr(error_string, kCFStringEncodingMacRoman));
        exit(EXIT_FAILURE);
    }
    
    /* Check root node type and cast property list */
    if (CFDictionaryGetTypeID() != CFGetTypeID(plist))
    {
        printf("Bookmarks property list root node is not a dictionary.\n");
        exit(EXIT_FAILURE);
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
    root_node->title = BSU_ROOT_TITLE;
    root_node->type = bookmark_type_folder;
    root_node->data.folder.children = NULL;
    root_node->data.folder.auto_open_in_tabs = 0;
    
    CFRelease(plist);
    if (error != NULL)
        CFRelease(error);
    CFRelease(bookmarks_read_stream);
    CFRelease(bookmarks_url);
    CFRelease(bookmarks_path);
    free(full_path);
    return root_node;
}