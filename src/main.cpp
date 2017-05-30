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

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <memory>
#include <cstring>

#include "GfxInitQuit.hpp"
#include "GfxWindow.hpp"
#include "GfxRenderer.hpp"
#include "GfxSurface.hpp"
#include "GfxTexture.hpp"
#include "GfxBgiConstants.hpp"
#include "GfxCanvas.hpp"
#include "Linux.h"
#include "macOS.h"
#include "GfxMessageBox.hpp"
#include "GfxCpuInfo.hpp"
#include "GfxPlatform.hpp"
#include "GfxPowerInfo.hpp"
#include "GfxScreenSaver.hpp"
#include "GfxVideo.hpp"
#include "GfxWindowPosition.hpp"
#include "GfxWindowFlags.hpp"
#include "GfxVersion.hpp"
#include "GfxGetVersion.hpp"
#include "GfxFileSystem.hpp"
#include "GfxBits.hpp"
#include "GfxClipboard.hpp"
#include "GfxEndian.hpp"
#include "GfxLoadSo.hpp"
#include "GfxError.hpp"
#include "GfxRendererInfo.hpp"
#include "GfxGetRendererInfo.hpp"
#include "GfxRendererFlags.hpp"
#include "GfxPalette.hpp"
#include "GfxSurfaceFlags.hpp"
#include "GfxBgiFontConstants.hpp"
#include "GfxPixelFormatEnum.hpp"

void MsgBox(gfx::GfxWindow const& win)
{
    gfx::GfxPlatform plat;
    plat.queryPlatform();
    gfx::GfxPowerInfo pinfo;
    pinfo.queryPowerInfo();

    gfx::GfxMessageBoxFlags flags { gfx::GfxMessageBoxFlags::ValueType::flagInformation };
    std::string title = "Title";
    std::string message = pinfo.getAsString();
    int numbuttons = 4;
    std::string btn1 = "1 " + plat.getPlatform();
    gfx::GfxMessageBoxButtonData buttons[4] {
        gfx::GfxMessageBoxButtonData(gfx::GfxMessageBoxButtonFlags(
                    gfx::GfxMessageBoxButtonFlags::ValueType::noneDefault), 1, btn1),
        gfx::GfxMessageBoxButtonData(gfx::GfxMessageBoxButtonFlags(
                    gfx::GfxMessageBoxButtonFlags::ValueType::escKeyDefault), 2, "Button2"),
        gfx::GfxMessageBoxButtonData(gfx::GfxMessageBoxButtonFlags(
                    gfx::GfxMessageBoxButtonFlags::ValueType::returnKeyDefault), 3, "Button3"),
        gfx::GfxMessageBoxButtonData(gfx::GfxMessageBoxButtonFlags(
                    gfx::GfxMessageBoxButtonFlags::ValueType::noneDefault), 4, "4 Test")
    };
    gfx::GfxMessageBoxColor c[5] = {
        gfx::GfxMessageBoxColor(255, 0, 0),
        gfx::GfxMessageBoxColor(250, 220, 190),
        gfx::GfxMessageBoxColor(192, 92, 9),
        gfx::GfxMessageBoxColor(50, 100, 200),
        gfx::GfxMessageBoxColor(255, 255, 255)
    };
    gfx::GfxMessageBoxColorScheme colorScheme(c);
    colorScheme.setColor(gfx::GfxMessageBoxColorType(
                            gfx::GfxMessageBoxColorType::ValueType::colorBackground),
                         gfx::GfxMessageBoxColor(
                                            gfx::bgi::GfxBgiConstants::vgaDarkGray().getRed(),
                                            gfx::bgi::GfxBgiConstants::vgaDarkGray().getGreen(),
                                            gfx::bgi::GfxBgiConstants::vgaDarkGray().getBlue()));

    gfx::GfxMessageBoxData m(flags, const_cast<gfx::GfxWindow *>(&win), title, message, numbuttons, buttons,
                                colorScheme);
    // GfxMessageBoxData m(flags,win,title,message,numbuttons,buttons);

    gfx::GfxMessageBox g(m);
    int r = g.showModal();

    std::string rez;

    gfx::GfxBits b;
    rez = "R=" + std::to_string((b.mostSignificantBitIndex32(r) << 8) | (r & 0x00FF));

    /*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             rez.c_str(),
                             "File is missing. Please reinstall the program.",
                             NULL);*/
    gfx::GfxCpuInfo cinfo;
    cinfo.queryCpuInfo();
    gfx::GfxMessageBox k(gfx::GfxMessageBoxFlags(gfx::GfxMessageBoxFlags::ValueType::flagError),
                         rez, cinfo.getAsString(), win);
    k.showModal();

    gfx::GfxClipboard clipb;
    clipb.setClipboardText(cinfo.getAsString());
}

void BeforeInit(void)
{
    std::cout << "BeforeInit()" << std::endl;

    gfx::GfxVideo v;

    std::cout << "v.getNumVideoDrivers()=" << v.getNumVideoDrivers() << '\n';
    for (int i = 0; i < v.getNumVideoDrivers(); i++)
    {
        std::cout << "v.getVideoDriver(i)=" << v.getVideoDriver(i) << '\n';
    }
    gfx::GfxGetVersion gv;
    gfx::GfxVersion ver;

    gv.getVersion(&ver);
    std::cout << "ver.getAsString()=" << ver.getAsString() << '\n';
    std::cout << "gv.getRevision()=" << gv.getRevision() << '\n';
    std::cout << "gv.getRevisionNumber()=" << gv.getRevisionNumber() << '\n';

    gfx::GfxFileSystem fs;

    std::cout << "fs.getBasePath()=" << fs.getBasePath() << '\n';
    std::cout << std::endl;
}

void AfterInit(void)
{
    std::cout << "AfterInit()" << std::endl;

    gfx::GfxVideo v;

    std::cout << "v.getCurrentVideoDriver()=" << v.getCurrentVideoDriver() << '\n';
    std::cout << "v.getNumVideoDisplays()=" << v.getNumVideoDisplays() << '\n';
    for (int i = 0; i < v.getNumVideoDisplays(); i++)
    {
        std::cout << "v.getDisplayName(i)=" << v.getDisplayName(i) << '\n';
        float d, h, v1;
        v.getDisplayDPI(i, &d, &h, &v1);
        std::cout << "v.getDisplayDPI(i).ddpi=" << d << '\n';
        std::cout << "v.getNumDisplayModes(i)=" << v.getNumDisplayModes(i) << '\n';
        std::unique_ptr<gfx::GfxDisplayMode> dm = v.getCurrentDisplayMode(i);
        std::cout << "dm.get()->getFormat()=" << "0x" << std::uppercase << std::setfill('0') <<
                    std::setw(8) << std::hex << dm.get()->getFormat() << std::dec << '\n';
        std::cout << "dm.get()->getFormat()=" << dm.get()->getFormat() << '\n';
        std::cout << "dm.get()->getWidth()=" << dm.get()->getWidth() << '\n';
        std::cout << "dm.get()->getHeight()=" << dm.get()->getHeight() << '\n';
        std::cout << "dm.get()->getRefreshRate()=" << dm.get()->getRefreshRate() << "Hz" << '\n';

        gfx::GfxEndian e;

        std::cout << "e.swapFloatBE(d)=" << e.swapFloatBE(d) << '\n';
    }
    gfx::GfxGetRendererInfo gri;
    gfx::GfxRendererInfo ri;

    std::cout << "gri.getNumRenderDrivers()=" << gri.getNumRenderDrivers() << '\n';
    for (int i = 0; i < gri.getNumRenderDrivers(); i++)
    {
        gri.getRenderDriverInfo(i, &ri);
        std::cout << "ri.getName()=" << ri.getName() << '\n';
        std::cout << "ri.getFlags()=" << ri.getFlags() << '\n';
        std::cout << "ri.getMaxTextureWidth()=" << ri.getMaxTextureWidth() << '\n';
        std::cout << "ri.getMaxTextureHeight()=" << ri.getMaxTextureHeight() << '\n';
        std::cout << "ri.getNumTextureFormats()=" << ri.getNumTextureFormats() << '\n';
        for (uint32_t j = 0; j < ri.getNumTextureFormats(); j++)
        {
            std::cout << "ri.getTextureFormats()[j]=" << ri.getTextureFormats()[j] << '\n';
        }
        gfx::GfxRendererFlags rf(static_cast<gfx::GfxRendererFlags::SdlType>(ri.getFlags()));
        std::cout << "rf.isUnknown()=" << rf.isUnknown() << '\n';
        std::cout << "rf.isSoftware()=" << rf.isSoftware() << '\n';
        std::cout << "rf.isAccelerated()=" << rf.isAccelerated() << '\n';
        std::cout << "rf.getPresentVSync()=" << rf.getPresentVSync() << '\n';
        std::cout << "rf.getTargetTexture()=" << rf.getTargetTexture() << '\n';
    }
    std::cout << std::endl;
}

void AfterDeInit(void)
{
    std::cout << "AfterDeInit()" << std::endl;

    // We expect this to fail
    gfx::GfxLoadSo lso("whatever.so");
    void * f;

    f = lso.loadFunction("whatever_function");
    if (f == nullptr)
    {
        std::cout << "lso.loadFunction(\"whatever_function\")=" << "nullptr" << '\n';
        std::cout << "err.getError()=" << gfx::GfxError::getError() << '\n';
    }
    std::cout << std::endl;
}

void bmpSurfaceInfo(gfx::GfxSurface* bmps)
{
    gfx::pixels::GfxPixelFormat * fmt;
    gfx::pixels::GfxPalette::GfxColorVector vec;
    int32_t bpp;
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;

    fmt = bmps->getFormat();
    std::cout << "fmt->getFormat()=" << fmt->getFormat().getAsSdlType() << '\n';
    // palette goes here
    std::cout << "fmt->getBitsPerPixel()=" << static_cast<int>(fmt->bitsPerPixel()) << '\n';
    std::cout << "fmt->getBytesPerPixel()=" << static_cast<int>(fmt->bytesPerPixel()) << '\n';
    fmt->pixelFormatEnumToMasks(&bpp, &redMask, &greenMask, &blueMask, &alphaMask);
    std::cout << "fmt->getRmask()=" << redMask << '\n';
    std::cout << "fmt->getGmask()=" << greenMask << '\n';
    std::cout << "fmt->getBmask()=" << blueMask<< '\n';
    std::cout << "fmt->getAmask()=" << alphaMask << '\n';
}

void inc(int* a)
{
    if ((*a + 4) > 255)
    {
        *a = 255;
    }
    else
    {
        *a += 4;
    }
}

void dec(int* a)
{
    if ((*a - 4) < 0)
    {
        *a = 0;
    }
    else
    {
        *a -= 4;
    }
}

void _doStuff(void)
{
    BeforeInit();
    gfx::GfxInitFlags iflags;

    iflags.setVideo();
    iflags.setEvents();
    gfx::GfxInitQuit iq(iflags);
    AfterInit();
    std::cout << "_doStuff()" << std::endl;
    if (iq.getErrorCode() != 0)
    {
        std::cout << "Init failed\n";
        return;
    }
    gfx::GfxWindowFlags wf(gfx::GfxWindowFlags::ValueType::windowFlagResizable);
    gfx::GfxWindow win("Window title",
                        gfx::GfxWindowPosition(gfx::GfxWindowPosition::ValueType::positionCentered),
                        gfx::GfxWindowPosition(gfx::GfxWindowPosition::ValueType::positionCentered),
                        WIN_W,
                        WIN_H,
                        wf);
    MsgBox(win);
    gfx::GfxRenderer rend(win);

    gfx::GfxRendererInfo ri;
    rend.getRendererInfo(&ri);
    std::cout << "ri.getName()=" << ri.getName() << '\n';
    std::cout << "ri.getFlags()=" << ri.getFlags() << '\n';
    std::cout << "ri.getMaxTextureWidth()=" << ri.getMaxTextureWidth() << '\n';
    std::cout << "ri.getMaxTextureHeight()=" << ri.getMaxTextureHeight() << '\n';
    std::cout << "ri.getNumTextureFormats()=" << ri.getNumTextureFormats() << '\n';

    if (ri.getNumTextureFormats() > 0)
    {
        gfx::GfxRendererInfo::GfxTextureFormats gtf;

        gtf = ri.getTextureFormats();
        for (uint32_t i = 0; i < ri.getNumTextureFormats(); i++)
        {
            gfx::pixels::GfxPixelFormat gpf(gfx::pixels::GfxPixelFormatEnum(gtf[i]));
            std::cout << "gpf.getPixelFormatName()=" << gpf.getPixelFormatName() << '\n';
        }
    }
    gfx::GfxSurface sbitmap(std::string(__base_path) + std::string("/Image2.bmp"));
    bmpSurfaceInfo(&sbitmap);

    gfx::GfxSurface surfcanvas(gfx::GfxSurfaceFlags(), WIN_W, WIN_H);

    int c = 0;
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 480; j < WIN_H; j++)
        {
            surfcanvas.putPixel(i, j, gfx::bgi::GfxBgiConstants::vgaGetColorByIndex(
                        static_cast<gfx::bgi::GfxBgiConstants::GfxVga16ColorIndex>(c)));
        }
        if (((i + 1) % 60) == 0)
        {
            c += 1;
            if (c == gfx::bgi::GfxBgiConstants::kVgaNumColors) c = 0;
        }
    }

    gfx::bgi::GfxCanvas cv(surfcanvas);
    cv.Circle(gfx::GfxPoint(480, 240), gfx::bgi::GfxRadius(230), gfx::bgi::GfxBgiConstants::vgaGreen());
    auto color = gfx::bgi::GfxBgiConstants::vgaRed();
    cv.Arc(gfx::GfxPoint(480, 240), gfx::bgi::GfxAngle(60), gfx::bgi::GfxAngle(300), gfx::bgi::GfxRadius(239), color);
    cv.OutText(gfx::GfxPoint(360, 232), gfx::bgi::GfxString("SDL_bgi"), gfx::pixels::GfxColor(50, 100, 200));
    cv.Bar(gfx::GfxPoint(480, 0), gfx::GfxPoint(960, 240), gfx::bgi::GfxBgiConstants::vgaLightRed());
    cv.Bar(gfx::GfxRect(10, 10, 20, 20), gfx::bgi::GfxBgiConstants::vgaRed());
    cv.Rect(gfx::GfxPoint(20, 20), gfx::GfxPoint(30, 30), gfx::bgi::GfxBgiConstants::vgaGreen());
    cv.Rect(gfx::GfxRect(30, 30, 40, 40), gfx::pixels::GfxColor(128, 128, 128));
    cv.Line(gfx::GfxPoint(10, 10), gfx::GfxPoint(40, 40), gfx::bgi::GfxBgiConstants::vgaYellow());
    cv.OutText(gfx::GfxPoint(50, 50), gfx::bgi::GfxString("The quick brown fox jumped over the lazy dog 0123456789!"),
               gfx::pixels::GfxColor(150, 100, 200));

    std::string fontMsg = "The quick brown fox jumped over the laxy dog 0123456789!";
    for (int i = 0; i < gfx::bgi::fnt::GfxBgiFontConstants::fntNumFonts; i++)
    {
        int x = 30;
        int y = 60 + i * 16;
        int r = 210 - i * 10;
        int g = 200 + i * 5;
        int b = 20 + i * 10;
        cv.OutText(gfx::GfxPoint(x, y), gfx::bgi::GfxString(fontMsg),
                   gfx::pixels::GfxColor(r, g, b),
                   gfx::bgi::fnt::GfxBgiFontConstants::fntGetFontByIndex(
                        static_cast<gfx::bgi::fnt::GfxBgiFontConstants::GfxFontIndex>(i)));
    }


    cv.Bar(gfx::GfxPoint(600, 100), gfx::GfxPoint(800, 200), gfx::bgi::GfxBgiConstants::vgaLightGray());
    cv.OutText(gfx::GfxPoint(620, 120), gfx::bgi::GfxString("3D Text, custom font"),
               gfx::bgi::GfxBgiConstants::vgaWhite(), gfx::bgi::fnt::GfxBgiFontConstants::fntScript());
    cv.OutText(gfx::GfxPoint(621, 121), gfx::bgi::GfxString("3D Text, custom font"),
               gfx::bgi::GfxBgiConstants::vgaBlack(), gfx::bgi::fnt::GfxBgiFontConstants::fntScript());
    cv.OutText(gfx::GfxPoint(620, 140), gfx::bgi::GfxString("3D Text, SDL_bgi font"),
               gfx::bgi::GfxBgiConstants::vgaWhite());
    cv.OutText(gfx::GfxPoint(621, 141), gfx::bgi::GfxString("3D Text, SDL_bgi font"),
               gfx::bgi::GfxBgiConstants::vgaBlack());


    cv.OutText(gfx::GfxPoint(1010, 120), gfx::bgi::GfxString("WIN_W=" + std::to_string(WIN_W)),
               gfx::bgi::GfxBgiConstants::vgaGreen(), gfx::bgi::fnt::GfxBgiFontConstants::fntAntique());
    cv.OutText(gfx::GfxPoint(1010, 150), gfx::bgi::GfxString("WIN_H=" + std::to_string(WIN_H)),
               gfx::bgi::GfxBgiConstants::vgaLightGray(), gfx::bgi::fnt::GfxBgiFontConstants::fntWacky());
    c = 0;
    for (int i = 0; i < WIN_W; i++)
    {
        for (int j = 240; j < 480; j++)
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;

            r = gfx::bgi::GfxBgiConstants::vgaGetColorByIndex(
                    static_cast<gfx::bgi::GfxBgiConstants::GfxVga16ColorIndex>(c)).getRed();
            g = gfx::bgi::GfxBgiConstants::vgaGetColorByIndex(
                    static_cast<gfx::bgi::GfxBgiConstants::GfxVga16ColorIndex>(c)).getGreen();
            b = gfx::bgi::GfxBgiConstants::vgaGetColorByIndex(
                    static_cast<gfx::bgi::GfxBgiConstants::GfxVga16ColorIndex>(c)).getBlue();
            cv.PutPixel(gfx::GfxPoint(i, j), gfx::pixels::GfxColor(r, g, b, 224));
        }
        if (((i + 1) % 60) == 0)
        {
            c += 1;
            if (c == gfx::bgi::GfxBgiConstants::kVgaNumColors) c = 0;
        }
    }

    gfx::GfxSurface colors_surf(gfx::GfxSurfaceFlags(), WIN_W, WIN_H);
    gfx::GfxRect rt;

    gfx::sdl2::SDL_Event e;
    bool quit = false;
    int r1 = gfx::bgi::GfxBgiConstants::vgaDarkGray().getRed();
    int g1 = gfx::bgi::GfxBgiConstants::vgaDarkGray().getGreen();
    int b1 = gfx::bgi::GfxBgiConstants::vgaDarkGray().getBlue();
    int a1 = 0;

    gfx::GfxScreenSaver ss;
    if (ss.isScreenSaverEnabled() == false)
    {
        ss.enableScreenSaver();
    }
    std::srand(static_cast<unsigned int>(time(0)));
    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == gfx::sdl2::SDL_QUIT)
                quit = true;
            if (e.type == gfx::sdl2::SDL_KEYDOWN) {
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_Q)
                    inc(&r1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_A)
                    dec(&r1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_W)
                    inc(&g1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_S)
                    dec(&g1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_E)
                    inc(&b1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_D)
                    dec(&b1);
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_Z)
                { r1 = 0; g1 = 0; b1 = 0; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_X)
                { r1 = 128; g1 = 128; b1 = 128; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_C)
                { r1 = 255; g1 = 255; b1 = 255; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_K)
                { r1 = 137; g1 = 6; b1 = 71; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_U)
                { r1 = 113; g1 = 194; b1 = 4; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_O)
                { r1 = 237; g1 = 249; b1 = 75; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_M)
                { r1 = 128; g1 = 64; b1 = 128; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_N)
                {
                    r1 = std::rand() % 255;
                    g1 = std::rand() % 255;
                    b1 = std::rand() % 255;
                }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_H)
                { r1 = 128; g1 = 138; b1 = 43; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_I)
                { r1 = 42; g1 = 0; b1 = 46; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_T)
                { r1 = 125; g1 = 251; b1 = 1; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_J)
                { r1 = 42; g1 = 0; b1 = 46; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_Y)
                { r1 = 156; g1 = 54; b1 = 78; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_P)
                { r1 = 50; g1 = 100; b1 = 200; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_1)
                { inc(&a1); }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_2)
                { dec(&a1); }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_L)
                { r1 = 208; g1 = 8; b1 = 232; }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_8)
                { inc(&r1); inc(&g1); inc(&b1); }
                if (e.key.keysym.scancode == gfx::sdl2::SDL_SCANCODE_9)
                { dec(&r1); dec(&g1); dec(&b1); }
            }

            int rp = r1 * 100 / 255;
            int gp = g1 * 100 / 255;
            int bp = b1 * 100 / 255;
            std::string str_title;

            str_title = "[R(" + std::to_string(r1) + ")";
            for (int i = 0; i < rp / 10; i++)
            {
                str_title += "=";
            }
            for (int i = rp / 10; i < 10; i++)
            {
                str_title += ".";
            }
            str_title += "][G(" + std::to_string(g1) + ")";
            for (int i = 0; i < gp / 10; i++)
            {
                str_title += "=";
            }
            for (int i = gp / 10; i < 10; i++)
            {
                str_title += ".";
            }
            str_title += "][B(" + std::to_string(b1) + ")";
            for (int i = 0; i < bp / 10; i++)
            {
                str_title += "=";
            }
            for (int i = bp / 10; i < 10; i++)
            {
                str_title += ".";
            }
            str_title += "][A(" + std::to_string(a1) +")]";
            win.setTitle(str_title);
            surfcanvas.blitSurface(sbitmap, gfx::GfxRect(0, 0, sbitmap.getWidth(), sbitmap.getHeight()),
                                   gfx::GfxRect(160, 640, WIN_W, WIN_H));
            gfx::GfxTexture canvas_tex(&rend, surfcanvas);
            canvas_tex.setBlendMode(gfx::GfxBlendMode::ValueType::blendNone);

            rt.setX(0);
            rt.setY(0);
            rt.setWidth(WIN_W);
            rt.setHeight(480);
            colors_surf.fillRect(rt, gfx::pixels::GfxColor(r1, g1, b1, a1));
            rt.setX(WIN_W / 2);
            colors_surf.fillRect(rt, gfx::pixels::GfxColor(255-r1, 255-g1, 255-b1, a1));

            gfx::GfxTexture colors_tex(&rend, colors_surf);
            colors_tex.setBlendMode(gfx::GfxBlendMode::ValueType::blendBlend);

            rend.renderCopy(canvas_tex);
            rend.renderCopy(colors_tex);
            rend.renderPresent();
        }
        gfx::sdl2::SDL_Delay(25);
    }
    sbitmap.~GfxSurface();
    AfterDeInit();
}

void _doPlay(void)
{
    std::cout << "Moved to play!" << std::endl;
}

#include "GApplication.hpp"
#include "GDemoForm.hpp"

void _doGApp(void)
{
    gto::gobj::GApplication gApp(GVarName(gApp));
    GDemoForm * demoForm = new GDemoForm("GDemoForm");

    gApp.setMainForm(demoForm);
    gApp.loadAppConfiguration();
    gApp.run();

    delete demoForm;
}

#ifdef __windows_machine
int WinMain(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
    int action = __platform_default_action;

    if (argc == 2)
    {
        if (std::strcmp(argv[1], "play") == 0)
        {
            action = 0;
        }
        if (std::strcmp(argv[1], "sdl") == 0)
        {
            action = 1;
        }
        if (std::strcmp(argv[1], "giotto") == 0)
        {
            action = 2;
        }
    }

    switch (action)
    {
        case 0:
            _doPlay();
            break;
        case 1:
            _doStuff();
            break;
        case 2:
            _doGApp();
            break;
        default:
            break;
    }
    return 0;
}

/* EOF */
