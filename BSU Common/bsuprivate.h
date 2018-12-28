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

#ifndef _BSU_PRIVATE_H_
#define _BSU_PRIVATE_H_

#include "bsucommon.h"

/* Property list keys */
extern CFStringRef const BSUKeyChildren;
extern CFStringRef const BSUKeyTitle;
extern CFStringRef const BSUKeyFileVersion;
extern CFStringRef const BSUKeyType;
extern CFStringRef const BSUKeyUUID;
extern CFStringRef const BSUKeyIdentifier;
extern CFStringRef const BSUKeyAutoTab;
extern CFStringRef const BSUKeyURIDictionary;
extern CFStringRef const BSUKeyURLString;
extern CFStringRef const BSUKeyURITitle;

extern CFStringRef const BSUBookmarkTypeList;
extern CFStringRef const BSUBookmarkTypeProxy;
extern CFStringRef const BSUBookmarkTypeLeaf;

struct bookmark_node* load_safari_bookmarks();

#endif