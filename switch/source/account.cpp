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

#include "account.hpp"

static std::unordered_map<u128, std::string> mUsernames;

Result Account::init(void)
{
    return accountInitialize();
}

void Account::exit(void)
{
    accountExit();
}

std::string Account::username(u128 id)
{
    std::unordered_map<u128, std::string>::const_iterator got = mUsernames.find(id);
    if (got == mUsernames.end())
    {
        // look for a user and add it to the map
        AccountProfile profile;
        AccountProfileBase profilebase;
        char username[0x21] = {0};
        memset(&profilebase, 0, sizeof(profilebase));

        Result res = accountGetProfile(&profile, id);
        if (R_FAILED(res))
        {
            return ""; 
        }

        res = accountProfileGet(&profile, NULL, &profilebase);
        if (R_FAILED(res))
        {
            return ""; 
        }

        strncpy(username, profilebase.username, sizeof(username) - 1);
        std::string user = std::string(username);
        mUsernames.insert({id, user});
        accountProfileClose(&profile);
        return user;
    }

    return got->second;
}