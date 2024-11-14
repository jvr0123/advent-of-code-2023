#include <format>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <numeric>

const std::unordered_map<std::string, int> kmax_cubes{{"blue", 14}, {"green", 13}, {"red", 12}};

// takes in a game, returns the game # if it was a valid game, otherwise returns 0
int part_one_parser(const std::string &game)
{
    std::istringstream iss(game);

    // parse the first section of the line, get the game number
    std::string game_header{}, game_information{};
    int game_number;
    char _;
    iss >> game_header >> game_number >> _;
    while (std::getline(iss, game_information, ';'))
    {
        // quick and dirty pesky punctuation removal from the string
        std::string color{};
        int num_cubes;

        std::transform(game_information.begin(), game_information.end(), game_information.begin(),
                       [](char &c)
                       {
                           if (std::ispunct(c))
                           {
                               return ' ';
                           }
                           return static_cast<char>(std::tolower(c));
                       });
        std::cout << game_information << std::endl;
        std::istringstream game_info_iss(game_information);
        while (game_info_iss >> num_cubes >> color)
        {
            auto it = kmax_cubes.find(color);
            if (it == kmax_cubes.end() || num_cubes > it->second)
            {
                return 0;
            }
        }
    }
    return game_number;
}

// figures out the minimum number of cubes to conceivably play a game, returns the product
int part_two_parser(const std::string &game)
{
    std::istringstream iss(game);

    // parse the first section of the line, get the game number
    std::string game_header{}, game_information{};
    int game_number;
    char _;
    iss >> game_header >> game_number >> _;
    std::unordered_map<std::string, int> min_cubes{{"blue", 0}, {"green", 0}, {"red", 0}};
    while (std::getline(iss, game_information, ';'))
    {
        // quick and dirty pesky punctuation removal from the string
        std::string color{};
        int num_cubes;

        std::transform(game_information.begin(), game_information.end(), game_information.begin(),
                       [](char &c)
                       {
                           if (std::ispunct(c))
                           {
                               return ' ';
                           }
                           return static_cast<char>(std::tolower(c));
                       });
        std::cout << game_information << std::endl;
        std::istringstream game_info_iss(game_information);
        while (game_info_iss >> num_cubes >> color)
        {
            min_cubes[color] = std::max(min_cubes[color], num_cubes);
        }
    }
    return std::accumulate(min_cubes.begin(), min_cubes.end(), 1, [](int acc, const auto &p)
                           { return acc * p.second; });
}

int main()
{
    std::fstream input("input");
    std::string line{};

    auto count1{0};
    auto count2{0};
    // get line from input file, remove all punctuation
    while (getline(input, line))
    {
        count1 += part_one_parser(line);
        count2 += part_two_parser(line);
    }

    input.close();

    std::cout << std::format("{} : {}", "Part 1:", count1) << std::endl;
    std::cout << std::format("{} : {}", "Part 2:", count2) << std::endl;
}