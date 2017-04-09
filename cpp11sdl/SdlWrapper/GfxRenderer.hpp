//
//  GfxRenderer.hpp
//  FirstProject
//
//  Created by George Oros on 3/29/17.
//  Copyright © 2017 George Oros. All rights reserved.
//

#ifndef GfxRenderer_hpp
#define GfxRenderer_hpp

#include "GfxSdlHeader.hpp"
#include "GfxRootClass.hpp"

#include "GfxWindow.hpp"
#include "GfxRect.hpp"
#include "GfxPoint.hpp"
#include "GfxFlip.hpp"
#include "GfxTexture.hpp"

class GfxRenderer final : public GfxRootClass
{
public:
    typedef SDL_Renderer SdlType;
    typedef SDL_Renderer* SdlTypePtr;
    
    GfxRenderer(const GfxWindow& win);
    
    GfxRenderer() = delete;

    GfxRenderer(const GfxRenderer&) = delete;
    GfxRenderer& operator=(const GfxRenderer&) = delete;
    
    GfxRenderer(GfxRenderer&& rend);
    GfxRenderer& operator=(GfxRenderer&& rend);
    
    ~GfxRenderer();
    
    void destroyRenderer(void);
    void renderClear(void);

    void renderCopy(const GfxTexture& tex,const GfxRect& src,const GfxRect& dest);
    void renderCopy(const GfxTexture& tex);
    
    void renderCopyEx(const GfxTexture& tex,const GfxRect& src,const GfxRect& dest,const double angle,const GfxPoint& pt,const GfxFlip& flip);
    void renderCopyEx(const GfxTexture& tex,const double angle,const GfxPoint& pt,const GfxFlip& flip);

    void renderPresent(void);

    SdlTypePtr getAsSdlTypePtr() const;
private:
    SDL_Renderer* renderer_;
    GfxWindow const* window_;
};

#endif /* GfxRenderer_hpp */