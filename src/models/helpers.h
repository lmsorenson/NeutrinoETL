#pragma once

bool is_upper_extreme(class NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, class NeutrinoPoint* axis_max_point);
bool is_lower_extreme(class NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, class NeutrinoPoint* axis_min_point);