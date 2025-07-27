#ifndef DAYS_H
#define DAYS_H

#include "game_data.h"
#include <string>  // <-- ADD THIS LINE
#include <vector> // Required for std::vector

namespace LeagueSchedulerNS {
    // Forward-declarations of the types used in the class interface
    struct YourDateType;

    class DateConverter {
    public:
        // Overload 1: Handles a date object (as you already have)
        int getDayNumber(const YourDateType& date) const;
    
        // Overload 2: Handles a date string
        int getDayNumber(const std::string& date_str) const;
    
        void sortGames(std::vector<Game>& games) const;
    };

} // namespace LeagueSchedulerNS

namespace LeagueScheduler_4_NS {
    // Forward-declarations of the types used in the class interface
    struct Game_4; // Changed from Game

    class DateConverter_4 {
    public:
        // New method designed for the future Game_4 struct
        void sortGames_4(std::vector<Game_4>& games) const;
    };
} // namespace LeagueScheduler_4_NS


#endif // DAYS_H
