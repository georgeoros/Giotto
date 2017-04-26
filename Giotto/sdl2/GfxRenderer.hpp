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

#ifndef GfxRenderer_hpp
#define GfxRenderer_hpp

#include "GfxSdlHeader.hpp"
#include "GfxRootClass.hpp"

#include "GfxWindow.hpp"
#include "GfxRect.hpp"
#include "GfxPoint.hpp"
#include "GfxRendererFlip.hpp"
#include "GfxTexture.hpp"

class GfxRenderer final : public GfxRootClass
{
public:
    typedef SDL_Renderer SdlType;
    typedef SDL_Renderer* SdlTypePtr;

    explicit GfxRenderer(const GfxWindow& win);

    GfxRenderer() = delete;

    GfxRenderer(const GfxRenderer&) = delete;
    GfxRenderer& operator=(const GfxRenderer&) = delete;

    GfxRenderer(GfxRenderer&& rend);
    GfxRenderer& operator=(GfxRenderer&& rend);

    ~GfxRenderer();

    void destroyRenderer(void);
    void renderClear(void);

    void renderCopy(const GfxTexture& tex, const GfxRect& src, const GfxRect& dest);
    void renderCopy(const GfxTexture& tex);

    void renderCopyEx(const GfxTexture& tex, const GfxRect& src, const GfxRect& dest,
                        const double angle, const GfxPoint& pt, const GfxRendererFlip& flip);
    void renderCopyEx(const GfxTexture& tex, const double angle, const GfxPoint& pt, const GfxRendererFlip& flip);

    void renderPresent(void);

    SdlTypePtr getAsSdlTypePtr() const;
private:
    SDL_Renderer* renderer_;
    GfxWindow const* window_;
};

#endif /* GfxRenderer_hpp */
