/*
 * Audacity: A Digital Audio Editor
 */
#include "axisticks.h"

#include "numberscale.h"

#include <algorithm>
#include <cmath>

namespace au::shared {
namespace {
// Sorted by decreasing value.
std::vector<double> getTicksValues(double maxVal, double minVal, double step, AxisScale scale)
{
    std::vector<double> values;
    auto tick = std::floor(maxVal / step) * step;
    while (tick >= minVal) {
        if (scale == AxisScale::Logarithmic && tick <= 0) {
            break;
        }
        values.push_back(tick);
        tick -= step;
    }
    return values;
}

std::vector<AxisTick> toTicks(const std::vector<double>& values, const NumberScale& numberScale, double labelExtentFraction)
{
    std::vector<AxisTick> ticks;
    ticks.reserve(values.size());
    std::transform(values.begin(), values.end(), std::back_inserter(ticks), [&numberScale](double value) {
        return AxisTick { value, static_cast<double>(numberScale.valueToPosition(static_cast<float>(value))) };
    });

    // Sort ascending by position so the overlap-rejection loop is orientation-agnostic.
    std::sort(ticks.begin(), ticks.end(), [](const AxisTick& a, const AxisTick& b) {
        return a.position < b.position;
    });

    auto nextTop = -labelExtentFraction / 2;
    auto it = ticks.begin();
    while (it != ticks.end()) {
        const auto tickTop = it->position - labelExtentFraction / 2;
        const auto tickBottom = it->position + labelExtentFraction / 2;
        if (tickTop < nextTop || tickBottom > 1.0 + labelExtentFraction / 2) {
            it = ticks.erase(it);
        } else {
            nextTop = tickBottom;
            ++it;
        }
    }

    return ticks;
}

std::vector<AxisTick> getTicks(double min, double max, AxisScale scale, const NumberScale& numberScale,
                               double labelExtentFraction, double step)
{
    const std::vector<double> values = getTicksValues(max, min, step, scale);
    return toTicks(values, numberScale, labelExtentFraction);
}
}

AxisTicks axisTicks(double min, double max, AxisScale scale, double labelExtent, double axisLength)
{
    const auto range = max - min;
    if (range <= 0 || axisLength <= 0) {
        return {};
    }

    const auto safeMin = scale == AxisScale::Logarithmic ? std::max(min, 1.) : min;
    const auto numberScale = NumberScale{ scale, safeMin, max };

    const auto extentFraction = labelExtent / axisLength;
    const auto majorStep = std::pow(10., std::floor(std::log10(range)));
    const std::vector<AxisTick> majorTicks = getTicks(safeMin, max, scale, numberScale, extentFraction, majorStep);

    const auto minorStep = majorStep / 10;
    std::vector<AxisTick> minorTicks = getTicks(safeMin, max, scale, numberScale, extentFraction, minorStep);

    // Remove minor ticks that overlap with major ticks.
    minorTicks.erase(std::remove_if(minorTicks.begin(), minorTicks.end(),
                                    [&majorTicks, extentFraction](const AxisTick& minorTick) {
        return std::any_of(majorTicks.begin(), majorTicks.end(), [&minorTick, extentFraction](const AxisTick& majorTick) {
            return std::abs(majorTick.position - minorTick.position) < extentFraction;
        });
    }),
                     minorTicks.end());

    return { majorTicks, minorTicks };
}
}
