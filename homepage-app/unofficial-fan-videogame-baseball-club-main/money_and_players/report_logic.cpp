//omitted for brevity

    std::ofstream reportFile("schedule_report_v3.9.md");
    reportFile << "# APMW Season Schedule Report (v3.9)\n\n";

    std::cout << "\n--- Sample Season Schedule (v3.9.0) ---" << std::endl;
    for (const auto& block : season_schedule) {
        reportFile << "## Residency Block: " << block.host_team.city << " Host (" << block.start_date << " to " << block.end_date << ")" 
                   << (block.is_apex_residency ? " **(APEX RESIDENCY)**" : "") << "\n\n";
        int last_printed_day = date_converter.getDayNumber(block.start_date) - 1;


        for (const auto& game : block.games) {
            int current_game_day = date_converter.getDayNumber(game.date);
            if (current_game_day > last_printed_day + 1) {
                for (int day = last_printed_day + 1; day < current_game_day; ++day) {
                    std::string day_str = "Day " + std::to_string(day);
                    std::string note = "Travel / Rest Day. Environmental Adjustment: Reduces frequent travel and carbon emissions within the extended residency model.";
                    reportFile << "- **" << day_str << ":** TRAVEL / REST DAY. **Environmental Adjustment Note:** " << note << "\n";
                }
            }
            const Team& home_batting_team = game.designated_home_team_for_batting;
            const Team& away_batting_team = (game.team1 == home_batting_team) ? game.team2 : game.team1;
            std::string game_type_str = getGameTypeString(game.game_type);
            reportFile << "- **" << game.date << ":** " << away_batting_team.city << " (First Bat) vs. " << home_batting_team.city << " (Second Bat) at " << game.actual_host_stadium.city << " Stadium. **Type:** " << game_type_str << "\n";
            if (game.game_type == GameType::REGIONAL_GAME) {
                double distance = GeographyData::calculateDistance(away_batting_team.city, home_batting_team.city);
                std::string travel_note = (distance < 5.0) ? "This is a local derby, facilitating low-emission fan travel by train for a short-distance journey." : "This matchup allows for efficient regional fan travel by train, minimizing the carbon footprint compared to air travel.";
                reportFile << "  - *Note: This is a **Regional Game**. **Environmental Enhancement:** " << travel_note << "*\n";
            }
            last_printed_day = current_game_day;
        }
        int block_end_day = date_converter.getDayNumber(block.end_date);
        if (block_end_day > last_printed_day) {
             for (int day = last_printed_day + 1; day <= block_end_day; ++day) {
                std::string day_str = "Day " + std::to_string(day);
                std::string note = "Departure / Rest Day. Environmental Adjustment: Optimizes team travel logistics, reducing overall carbon footprint.";

                reportFile << "- **" << day_str << ":** TRAVEL / REST DAY. **Environmental Adjustment Note:** " << note << "\n";
            }
        }
        reportFile << "\n";
    }

    std::cout << "Schedule generation complete. Report written to schedule_report_v3.9.md" << std::endl;
    reportFile.close();
