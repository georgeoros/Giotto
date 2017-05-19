/*
 Giotto
 Copyright (C) 2017 George Oros
 
 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 
 See copyright notice at http://lidsdl.org/license.php
*/

#include <string>

#include "GfxGetVersion.hpp"

namespace gfx
{

const char GfxGetVersion::ClassName[] = "GfxGetVersion";

GfxGetVersion::GfxGetVersion() : GfxRootClass(ClassName)
{
    // Nothing to do
}

GfxGetVersion::operator bool() const
{
    return true;
}

void GfxGetVersion::getVersion(GfxVersion* ver) const
{
    GfxVersion::SdlType v;

    sdl2::SDL_GetVersion(&v);
    ver->set(v);
}

std::string GfxGetVersion::getRevision(void) const
{
    std::string str;

    str = sdl2::SDL_GetRevision();
    return str;
}

int32_t GfxGetVersion::getRevisionNumber(void) const
{
    return sdl2::SDL_GetRevisionNumber();
}

}  // namespace gfx

/* EOF */
