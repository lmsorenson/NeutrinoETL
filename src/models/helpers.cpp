#include "helpers.h"
#include <models/neutrinopoint.h>

bool is_upper_extreme(NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, NeutrinoPoint* axis_max_point)
{
    if (!point) return false;
    if (!axis_max_point) return true;

    double axis_value = (point->*get_axis_value)();
    double axis_max_value = (axis_max_point->*get_axis_value)();

    return (axis_value > axis_max_value);
}

bool is_lower_extreme(NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, NeutrinoPoint* axis_min_point)
{
    if (!point) return false;
    if (!axis_min_point) return true;

    double axis_value = (point->*get_axis_value)();
    double axis_min_value = (axis_min_point->*get_axis_value)();

    return (axis_value < axis_min_value);
}