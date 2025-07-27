#include "days.h"
#include "game_data.h" // Use this instead of "game.h"
#include <algorithm> // Required for std::sort

// IMPORTANT: Include the header that provides the full definition of the 'Game' struct
// For example: #include "game.h"

// All implementations for DateConverter must be inside this namespace
namespace LeagueSchedulerNS {

// Implementation for the string overload (to fix the current error)
int DateConverter::getDayNumber(const std::string& date_str) const {
    size_t space_pos = date_str.find(' ');
    if (space_pos == std::string::npos) { return 0; }
    try {
        return std::stoi(date_str.substr(space_pos + 1));
    } catch (const std::exception& e) {
        return 0;
    }
}

// Implementation for the YourDateType overload
int DateConverter::getDayNumber(const YourDateType& date) const {
    // TODO: Implement the logic to get the day number from your actual date object.
    // For example:
    // return date.day_of_year;
    return 0; // Placeholder
}

// Implementation of the custom sorting method
void DateConverter::sortGames(std::vector<Game>& games) const {
    // The sorting logic is now encapsulated inside this method.
    // The lambda captures 'this' to call the getDayNumber member function.
    std::sort(games.begin(), games.end(), [this](const Game& a, const Game& b) {
        int day_a = getDayNumber(a.date);
        int day_b = getDayNumber(b.date);
        
        if (day_a != day_b) {
            return day_a < day_b;
        }
        return a.time < b.time;
    });
}
} // namespace LeagueSchedulerNS

// All implementations for DateConverter_4 must be inside this namespace
namespace LeagueScheduler_4_NS {

    void DateConverter_4::sortGames_4(std::vector<Game_4>& games) const {
        // TODO: Implement sorting logic for Game_4
    }

} // namespace LeagueScheduler_4_NS

