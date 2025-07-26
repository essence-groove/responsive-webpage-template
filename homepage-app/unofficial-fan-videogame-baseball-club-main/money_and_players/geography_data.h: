/**
 * @file geography_data.h
 * @brief Defines data structures for geographical information (v3.7.4).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef GEOGRAPHY_DATA_H
#define GEOGRAPHY_DATA_H

#include <string>
#include <map>
#include <cmath> // For sqrt in distance calculation
#include <stdexcept> // For std::out_of_range

namespace LeagueSchedulerNS {

/**
 * @struct Coordinates
 * @brief Represents geographical coordinates for a city.
 */
struct Coordinates {
    double latitude;
    double longitude;
};

/**
 * @class GeographyData
 * @brief A utility class to manage geographical data and calculations.
 *
 * v3.7.4: This class now contains a static data layer with the coordinates
 * for all league cities to support location-aware environmental notes.
 */
class GeographyData {
public:
    /**
     * @brief Retrieves the coordinates for a given city.
     * @param city The name of the city.
     * @return The Coordinates struct for the city.
     * @throws std::out_of_range if the city is not found.
     */
    static const Coordinates& getCoordinates(const std::string& city) {
        return city_coordinates_.at(city);
    }

    /**
     * @brief Calculates the approximate distance between two cities.
     * @param city1 The name of the first city.
     * @param city2 The name of the second city.
     * @return The calculated distance.
     */
    static double calculateDistance(const std::string& city1, const std::string& city2) {
        const auto& coord1 = getCoordinates(city1);
        const auto& coord2 = getCoordinates(city2);
        
        double lat_diff = coord1.latitude - coord2.latitude;
        double lon_diff = coord1.longitude - coord2.longitude;
        return std::sqrt(lat_diff * lat_diff + lon_diff * lon_diff);
    }

private:
    // Static map containing the geographical coordinates of all league cities.
    static inline const std::map<std::string, Coordinates> city_coordinates_ = {
        // Atlantic Union
        {"Maine",       {43.67, -70.28}}, // Portland
        {"New York",    {40.71, -74.01}},
        {"Philadelphia",{39.95, -75.17}},
        {"Pittsburgh",  {40.44, -80.00}},
        {"Atlanta",     {33.75, -84.39}},
        {"Miami",       {25.76, -80.19}},
        {"Charlotte",   {35.22, -80.84}},
        {"Cleveland",   {41.50, -81.69}},
        {"Detroit",     {42.33, -83.04}},
        // Pacific Union
        {"Los Angeles", {34.05, -118.24}},
        {"San Diego",   {32.72, -117.16}},
        {"San Francisco",{37.77, -122.42}},
        {"Seattle",     {47.61, -122.33}},
        {"Austin",      {30.27, -97.74}},
        {"Dallas",      {32.78, -96.80}},
        {"Denver",      {39.74, -104.99}},
        {"St. Louis",   {38.63, -90.20}},
        {"Kansas City", {39.10, -94.58}}
    };
};

} // namespace LeagueSchedulerNS

#endif // GEOGRAPHY_DATA_H
