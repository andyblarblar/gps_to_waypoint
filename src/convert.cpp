#include "../include/convert.hpp"
#include <vector>
#include <cmath>

void Convert::convert_gps_to_waypoint(std::vector<GPS_coordinates> gps_coordinates_list) {
    Waypoint temp_waypoint;

    if (!gps_coordinates_list.empty()) {
        for (auto temp_gps: gps_coordinates_list) {
            if (waypoints.empty()) {
                origin_x_ = temp_gps.latitude;
                origin_y_ = temp_gps.longitude;
                yaw_ = get_yaw(temp_gps.orientation);
                temp_waypoint = {0, 0, z_, roll_, pitch_, yaw_, tolerance_};
                waypoints.push_back(temp_waypoint);
            }
            else {
                x_ = get_x(temp_gps.latitude);
                y_ = get_y(temp_gps.longitude);
                yaw_ = get_yaw(temp_gps.orientation);

                temp_waypoint = {x_, y_, z_, roll_, pitch_, yaw_, tolerance_};
                waypoints.push_back(temp_waypoint);
            }
        }
    }

    /*
    CONVERT CARTESIAN TO SPHERICAL COORDINATE
    Cartesian (x, y, z)
    Spherical (r, theta, phi)

    r = sqrt((x * x) + (y * y) + (z * z))
    theta = arctan(y / x)
    phi = arctan(sqrt((x * x) + (y * y)) / z)
    */ 
}

std::vector<Waypoint> Convert::get_waypoints() {
    return waypoints;
}
double Convert::get_x(double gps_x) {
    return gps_x - origin_x_;
}

double Convert::get_y(double gps_y) {
    return gps_y - origin_y_;
}

double Convert::get_yaw(double angle) {
    return angle * M_PI / 180;
}