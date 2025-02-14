/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "SaveState.hpp"
#include "Error.hpp"

#include "m64p/Api.hpp"

//
// Exported Functions
//

bool CoreSetSaveStateSlot(int slot)
{
    std::string error;
    m64p_error ret;

    if (!m64p::Core.IsHooked())
    {
        return false;
    }

    ret = m64p::Core.DoCommand(M64CMD_CORE_STATE_SET, M64CORE_SAVESTATE_SLOT, &slot);
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreSetSaveStateSlot m64p::Core.DoCommand(M64CMD_CORE_STATE_SET, M64CORE_SAVESTATE_SLOT) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return ret == M64ERR_SUCCESS;
}

int CoreGetSaveStateSlot(void)
{
    std::string error;
    m64p_error ret;
    int slot = -1;

    if (!m64p::Core.IsHooked())
    {
        return -1;
    }

    ret = m64p::Core.DoCommand(M64CMD_CORE_STATE_QUERY, M64CORE_SAVESTATE_SLOT, &slot);
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreGetSaveStateSlot m64p::Core.DoCommand(M64CMD_CORE_STATE_QUERY, M64CORE_SAVESTATE_SLOT) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return slot;
}

bool CoreSaveState(void)
{
    std::string error;
    m64p_error ret;

    if (!m64p::Core.IsHooked())
    {
        return false;
    }

    ret = m64p::Core.DoCommand(M64CMD_STATE_SAVE, 0, nullptr);
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreSaveState: m64p::Core.DoCommand(M64CMD_STATE_SAVE) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return ret == M64ERR_SUCCESS;
}

bool CoreSaveState(std::filesystem::path file)
{
    std::string error;
    m64p_error ret;

    if (!m64p::Core.IsHooked())
    {
        return false;
    }

    ret = m64p::Core.DoCommand(M64CMD_STATE_SAVE, 1, (void*)file.string().c_str());
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreSaveState: m64p::Core.DoCommand(M64CMD_STATE_SAVE) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return ret == M64ERR_SUCCESS;
}

bool CoreLoadSaveState(void)
{
    std::string error;
    m64p_error ret;

    if (!m64p::Core.IsHooked())
    {
        return false;
    }

    ret = m64p::Core.DoCommand(M64CMD_STATE_LOAD, 0, nullptr);
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreLoadSaveState: m64p::Core.DoCommand(M64CMD_STATE_LOAD) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return ret == M64ERR_SUCCESS;
}

bool CoreLoadSaveState(std::filesystem::path file)
{
    std::string error;
    m64p_error ret;

    if (!m64p::Core.IsHooked())
    {
        return false;
    }

    ret = m64p::Core.DoCommand(M64CMD_STATE_LOAD, 0, (void*)file.string().c_str());
    if (ret != M64ERR_SUCCESS)
    {
        error = "CoreLoadSaveState: m64p::Core.DoCommand(M64CMD_STATE_LOAD) Failed: ";
        error += m64p::Core.ErrorMessage(ret);
        CoreSetError(error);
    }

    return ret == M64ERR_SUCCESS;
}
