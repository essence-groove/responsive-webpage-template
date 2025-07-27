#ifndef DAYS_H
#define DAYS_H

#include "game_data.h"
#include <string>  // <-- ADD THIS LINE
#include <vector> // Required for std::vector

// Forward-declarations of the types used in the class interface
struct YourDateType;
struct Game_4; // Changed from Game

namespace LeagueSchedulerNS {

    class DateConverter {
    public:
        // Overload 1: Handles a date object (as you already have)
        int getDayNumber(const YourDateType& date) const;
    
        // Overload 2: Handles a date string
        int getDayNumber(const std::string& date_str) const;
    
        void sortGames(std::vector<Game>& games) const;
    };

} // namespace LeagueSchedulerNS

#endif // DAYS_H
