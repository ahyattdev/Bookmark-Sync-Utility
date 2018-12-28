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

CFStringRef const BSUKeyChildren = CFSTR("Children");
CFStringRef const BSUKeyTitle = CFSTR("Title");
CFStringRef const BSUKeyFileVersion = CFSTR("WebBookmarkFileVersion");
CFStringRef const BSUKeyType = CFSTR("WebBookmarkType");
CFStringRef const BSUKeyUUID = CFSTR("WebBookmarkUUID");
CFStringRef const BSUKeyIdentifier = CFSTR("WebBookmarkIdentifier");
CFStringRef const BSUKeyAutoTab = CFSTR("WebBookmarkAutoTab");
CFStringRef const BSUKeyURIDictionary = CFSTR("URIDictionary");
CFStringRef const BSUKeyURLString = CFSTR("URLString");
CFStringRef const BSUKeyURITitle = CFSTR("title");

CFStringRef const BSUBookmarkTypeList = CFSTR("WebBookmarkTypeList");
CFStringRef const BSUBookmarkTypeProxy = CFSTR("WebBookmarkTypeList");
CFStringRef const BSUBookmarkTypeLeaf = CFSTR("WebBookmarkTypeList");