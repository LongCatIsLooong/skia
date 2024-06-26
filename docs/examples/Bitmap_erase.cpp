// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Bitmap_erase, 256, 70, false, 0) {
void draw(SkCanvas* canvas) {
    SkBitmap bitmap;
    bitmap.allocPixels(SkImageInfo::MakeN32(2, 2, kPremul_SkAlphaType));
    bitmap.erase(0x7fff7f3f, SkIRect::MakeWH(1, 1));
    bitmap.erase(0x7f7f3fff, SkIRect::MakeXYWH(0, 1, 1, 1));
    bitmap.erase(0x7f3fff7f, SkIRect::MakeXYWH(1, 0, 1, 1));
    bitmap.erase(0x7f1fbf5f, SkIRect::MakeXYWH(1, 1, 1, 1));
    canvas->scale(25, 25);
    canvas->drawImage(bitmap.asImage(), 0, 0);
    canvas->drawImage(bitmap.asImage(), .5f, .5f);
}
}  // END FIDDLE
