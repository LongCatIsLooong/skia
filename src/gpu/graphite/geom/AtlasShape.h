/*
 * Copyright 2023 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef skgpu_graphite_geom_AtlasShape_DEFINED
#define skgpu_graphite_geom_AtlasShape_DEFINED

#include "src/base/SkVx.h"
#include "src/gpu/graphite/geom/Rect.h"
#include "src/gpu/graphite/geom/Shape.h"

namespace skgpu::graphite {

class PathAtlas;

/**
 * AtlasShape represents a shape for which per-pixel coverage data comes from a transient atlas
 * texture. This excludes font glyphs that are rendered to a persistent atlas, as those are
 * represented by the SubRunData geometry type.
 *
 * The bounds of an atlas shape are always specified in device space and the transform of the
 * DrawParams is expected to be identity. These bounds are restricted to the conservative bounds of
 * the draw's clip stack and may have the draw's clip stack fully applied to the mask shape.
 */
class AtlasShape {
    using float2 = skvx::float2;

public:
    AtlasShape() = default;
    AtlasShape(const Shape& shape,
               const PathAtlas* atlas,
               const SkM44& deviceToLocal,
               float2 deviceOrigin,
               float2 atlasOrigin,
               float2 maskSize)
            : fAtlas(atlas)
            , fDeviceToLocal(deviceToLocal)
            , fInverted(shape.inverted())
            , fDeviceOrigin(deviceOrigin)
            , fAtlasOrigin(atlasOrigin)
            , fMaskSize(maskSize) {}
    AtlasShape(const AtlasShape&) = default;

    ~AtlasShape() = default;

    // NOTE: None of the geometry types benefit from move semantics, so we don't bother
    // defining a move assignment operator for AtlasShape.
    AtlasShape& operator=(AtlasShape&&) = delete;
    AtlasShape& operator=(const AtlasShape&) = default;

    // Returns the device-space bounds of the clipped coverage mask shape. For inverse fills this
    // is different from the actual draw bounds stored in the Clip.
    const Rect bounds() const { return Rect(this->deviceOrigin(), this->maskSize()); }

    // The inverse local-to-device matrix.
    const SkM44& deviceToLocal() const { return fDeviceToLocal; }

    // The top-left device-space coordinates of the (clipped) atlas mask shape. For regular fills
    // this is equal to the device-space origin of the draw bounds. For inverse fills this point
    // is often within the draw bounds, however it is allowed to be smaller for a partially clipped
    // inverse fill that has its mask shape completely clipped out.
    const float2& deviceOrigin() const { return fDeviceOrigin; }

    // The altas-relative integer UV coordinates of the top-left corner of this shape's atlas
    // coverage mask bounds.
    const float2& atlasOrigin() const { return fAtlasOrigin; }

    // The width and height of the bounds of the coverage mask shape in device coordinates.
    const float2& maskSize() const { return fMaskSize; }

    // The atlas that the shape will be rendered to.
    const PathAtlas* atlas() const { return fAtlas; }

    // Whether or not the shape will be painted according to an inverse fill rule.
    bool inverted() const { return fInverted; }

private:
    const PathAtlas* fAtlas;
    SkM44 fDeviceToLocal;
    bool fInverted;

    float2 fDeviceOrigin;
    float2 fAtlasOrigin;
    float2 fMaskSize;
};

}  // namespace skgpu::graphite

#endif  // skgpu_graphite_geom_AtlasShape_DEFINED