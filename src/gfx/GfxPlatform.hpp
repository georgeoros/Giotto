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

#ifndef GfxPlatform_hpp
#define GfxPlatform_hpp

#include <string>

#include "GfxRootClass.hpp"

namespace gfx
{

class GfxPlatform final : public GfxRootClass
{
public:
    static const char ClassName[];

    GfxPlatform();

    GfxPlatform(GfxPlatform const&) = delete;
    GfxPlatform(GfxPlatform&&) = delete;

    GfxPlatform& operator=(GfxPlatform const &) = delete;
    GfxPlatform& operator=(GfxPlatform&&) = delete;

    virtual explicit operator bool() const;

    void queryPlatform(void);

    std::string const& getPlatform(void) const;
private:
    std::string platform_;
};

}  // namespace gfx

#endif /* GfxPlatform_hpp */