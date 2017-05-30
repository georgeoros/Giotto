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

#ifndef GfxTextureAccess_hpp
#define GfxTextureAccess_hpp

#include <cstdint>
#include <string>

#include "GfxRootClass.hpp"
#include "GfxSdlHeader.hpp"

namespace gfx
{

class GfxTextureAccess final : public GfxRootClass
{
public:
    typedef sdl2::SDL_TextureAccess SdlType;
    typedef sdl2::SDL_TextureAccess* SdlTypePtr;

    static const char ClassName[];

    enum class ValueType : uint32_t
    {
        accessStatic = sdl2::SDL_TEXTUREACCESS_STATIC,
        accessStreaming = sdl2::SDL_TEXTUREACCESS_STREAMING,
        accessTarget = sdl2::SDL_TEXTUREACCESS_TARGET
    };

    GfxTextureAccess();

    explicit GfxTextureAccess(const ValueType access);

    GfxTextureAccess(GfxTextureAccess const& other);
    GfxTextureAccess(GfxTextureAccess&& other);

    GfxTextureAccess& operator=(GfxTextureAccess const& other);
    GfxTextureAccess& operator=(GfxTextureAccess&& other);

    void clear(void);

    SdlType getAsSdlType(void) const;
    SdlTypePtr getAsSdlTypePtr(void) const;
private:
    SdlType access_;
};

}  // namespace gfx

#endif /* GfxTextureAccess_hpp */