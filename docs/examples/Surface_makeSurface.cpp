// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Surface_makeSurface, 256, 96, false, 0) {
void draw(SkCanvas* canvas) {
    sk_sp<SkSurface> big(SkSurfaces::Raster(SkImageInfo::MakeN32Premul(64, 64)));
    sk_sp<SkSurface> lil(big->makeSurface(SkImageInfo::MakeN32(32, 32, kPremul_SkAlphaType)));
    big->getCanvas()->clear(SK_ColorRED);
    lil->getCanvas()->clear(SK_ColorBLACK);
    SkPixmap pixmap;
    if (big->peekPixels(&pixmap)) {
        SkBitmap bigBits;
        bigBits.installPixels(pixmap);
        canvas->drawImage(bigBits.asImage(), 0, 0);
    }
    if (lil->peekPixels(&pixmap)) {
        SkBitmap lilBits;
        lilBits.installPixels(pixmap);
        canvas->drawImage(lilBits.asImage(), 64, 64);
    }
}
}  // END FIDDLE
