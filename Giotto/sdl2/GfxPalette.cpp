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

#include <memory>

#include "GfxPalette.hpp"

GfxPalette::GfxPalette() : GfxRootClass("GfxPalette")
{
    pal_ = SDL_AllocPalette(kDefaultPaletteSize);
    for (uint32_t i = 0; i < kDefaultPaletteSize; i++)
    {
        SDL_SetPaletteColors(pal_, GfxColor(kDefaultPaletteColorRed, kDefaultPaletteColorGreen,\
                                            kDefaultPaletteColorBlue).getAsSdlTypePtr(), i, 1);
    }
};

GfxPalette::GfxPalette(const GfxColorVector& colors) : GfxRootClass("GfxPalette")
{
    uint32_t colorIndex;
    uint16_t nColors;
    
    nColors = colors.size();
    pal_ = SDL_AllocPalette(nColors);
    colorIndex = 0;
    for (GfxColor clr : colors)
    {
        SDL_SetPaletteColors(pal_, clr.getAsSdlTypePtr(), colorIndex, 1);
        colorIndex += 1;
    }
}

GfxPalette::GfxPalette(const uint16_t nColors) : GfxRootClass("GfxPalette")
{
    pal_ = SDL_AllocPalette(nColors);
    for (uint32_t i = 0; i < nColors; i++)
    {
        SDL_SetPaletteColors(pal_, GfxColor(kDefaultPaletteColorRed, kDefaultPaletteColorGreen,\
                                            kDefaultPaletteColorBlue).getAsSdlTypePtr(), i, 1);
    }
}

GfxPalette::GfxPalette(const GfxPalette& other) : GfxRootClass("GfxPalette")
{
    pal_ = SDL_AllocPalette(other.pal_->ncolors);
    SDL_SetPaletteColors(pal_, other.pal_->colors, 0, other.pal_->ncolors);
}

GfxPalette::GfxPalette(GfxPalette&& other) : GfxRootClass("GfxPalette")
{
    pal_ = SDL_AllocPalette(other.pal_->ncolors);
    SDL_SetPaletteColors(pal_, other.pal_->colors, 0, other.pal_->ncolors);
    /* free other's resources */
    SDL_FreePalette(other.pal_);
    other.pal_ = nullptr;
}

GfxPalette::GfxPalette(SdlTypePtr pal)
{
    pal_ = SDL_AllocPalette(pal->ncolors);
    SDL_SetPaletteColors(pal_, pal->colors, 0 , pal->ncolors);
}

GfxPalette::~GfxPalette()
{
    if (pal_ != nullptr)
    {
        SDL_FreePalette(pal_);
    }
}

GfxPalette& GfxPalette::operator=(const GfxPalette& other)
{
    if (this != &other)
    {
        if (pal_ != nullptr)
        {
            SDL_FreePalette(pal_);
        }
        pal_ = SDL_AllocPalette(other.pal_->ncolors);
        SDL_SetPaletteColors(pal_, other.pal_->colors, 0, other.pal_->ncolors);
    }
    return *this;
}

GfxPalette& GfxPalette::operator=(GfxPalette&& other)
{
    if (this != &other)
    {
        if (pal_ != nullptr)
        {
            SDL_FreePalette(pal_);
        }
        pal_ = SDL_AllocPalette(other.pal_->ncolors);
        SDL_SetPaletteColors(pal_, other.pal_->colors, 0, other.pal_->ncolors);
        /* Free other's resources */
        SDL_FreePalette(other.pal_);
        other.pal_ = nullptr;
    }
    return *this;
}

void GfxPalette::setPaletteColors(const GfxColorVector& colors, const uint16_t firstColor)
{
    int errorCode = 0;
    int currentColorIndex = firstColor;

    for (GfxColor clr : colors)
    {
        errorCode = SDL_SetPaletteColors(pal_, clr.getAsSdlTypePtr(), currentColorIndex, 1);
        currentColorIndex += 1;
        if (errorCode != 0)
        {
            break;
        }
    }
}

GfxPalette::GfxColorVector GfxPalette::getPaletteColors(void) const
{
    GfxColorVector clrs(pal_->ncolors);

    for (uint32_t i = 0; i < pal_->ncolors; i++)
    {
        GfxColor c(pal_->colors[i]);
        clrs.push_back(c);
    }
    return clrs;
}

uint16_t GfxPalette::getNumColors(void) const
{
    return pal_->ncolors;
}

uint32_t GfxPalette::getVersion(void) const
{
    return pal_->version;
}

int GfxPalette::getRefCount(void) const
{
    return pal_->refcount;
}

GfxPalette::SdlType GfxPalette::getAsSdlType() const
{
    return *pal_;
}

GfxPalette::SdlTypePtr GfxPalette::getAsSdlTypePtr(void) const
{
    /* This is dangerous; we allow access to object private data */
    return (SdlTypePtr)pal_;
}

/* EOF */
