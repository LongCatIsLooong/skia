// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Matrix_preservesAxisAlignment, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    SkMatrix matrix;
    for (SkScalar angle: { 0, 90, 180, 270 } ) {
        matrix.setRotate(angle);
        SkDebugf("preservesAxisAlignment: %s\n", matrix.preservesAxisAlignment() ? "true" : "false");
    }
}
}  // END FIDDLE
