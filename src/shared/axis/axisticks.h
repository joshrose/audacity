/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "axisscale.h"
#include "axistypes.h"

namespace au::shared {
/**
 * @brief Picks "good" round-number major and minor ticks across [min, max]
 *        under the given scale, dropping any that would visually overlap.
 *
 * @param min         Lower end of the data range.
 * @param max         Upper end of the data range.
 * @param scale       Scale used to map values to positions (linear, log, ...).
 * @param labelExtent Size taken up by a label along the axis. Used together
 *                    with @p axisLength to prune overlapping ticks. Must share
 *                    the same unit as @p axisLength (e.g. pixels).
 * @param axisLength  Total length of the axis in the same unit as
 *                    @p labelExtent.
 *
 * @return Major and minor ticks, each carrying a fractional @c position in
 *         [0, 1] where 0 corresponds to @p min and 1 to @p max.
 */
AxisTicks axisTicks(double min, double max, AxisScale scale, double labelExtent, double axisLength);
}
