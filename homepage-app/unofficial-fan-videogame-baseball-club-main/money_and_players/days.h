#ifndef DAYS_H
#define DAYS_H

#include <vector> // Required for std::vector

// Forward-declarations of the types used in the class interface
struct YourDateType;
struct Game;

class DateConverter {
public:
    int getDayNumber(const YourDateType& date) const;

    // Declaration for the new custom sorting method
    void sortGames(std::vector<Game>& games) const;
};

#endif // DAYS_H
