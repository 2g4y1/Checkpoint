/*
*   This file is part of Checkpoint
*   Copyright (C) 2017-2018 Bernardo Giordano
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#ifndef TITLE_HPP
#define TITLE_HPP

#include <algorithm>
#include <stdlib.h>
#include <string>
#include <switch.h>
#include <utility>
#include <vector>
#include <unordered_map>
#include "filesystem.hpp"
#include "io.hpp"

extern "C" {
#include "nanojpeg.h"
}

class Title 
{
public:
    void init(u64 titleid, u128 userID, const std::string& name);
    
    u8*           smallIcon(void);
    u8*           icon(void);
    void          smallIcon(u8* data, size_t iconsize);
    void          icon(u8* data, size_t iconsize);
    u64           id(void);
    std::string   name(void);
    std::string   path(void);
    void          refreshDirectories(void);
    std::vector
    <std::string> saves(void);
    u128          userId(void);
    std::string   userName(void);

private:
    u64           mId;
    u128          mUserId;
    std::string   mUserName;
    std::string   mDisplayName;
    std::string   mSafeName;
    std::string   mPath;
    u8*           mIcon;
    u8*           mSmallIcon;
    std::vector
    <std::string> mSaves;
};

void   getTitle(Title &dst, u128 uid, size_t i);
size_t getTitleCount(u128 uid);
void   loadTitles(void);
void   refreshDirectories(u64 id);
u8*    smallIcon(u128 uid, size_t i);
void   reloadSmallIcon(u128 uid, size_t i);

#endif