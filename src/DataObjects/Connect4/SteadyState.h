#pragma once

class C4Board;

#include <unordered_set>
#include <list>
#include <array>
#include <algorithm>

const int C4_HEIGHT = 6;
const int C4_WIDTH = 7;

enum C4Result {
    TIE,
    RED,
    YELLOW,
    INCOMPLETE
};

vector<char> miai = {'@', '#'};
vector<char> priority_list = {'+', '=', '-'};
vector<char> claims = {' ', '|'};
vector<char> disks = {'1', '2'};

bool is_miai(char c){
    return c == '@' || c == '#';
}

class SteadyState {
public:
    SteadyState(const array<string, C4_HEIGHT>& chars);
    int query_steady_state(const C4Board& board) const;
    void mutate();
    void drop(const int x, const char c);
    C4Result play_one_game(const C4Board& board) const;
    void print() const;
    void clear();
    Bitboard bitboard_yellow = 0ul;
    Bitboard bitboard_red = 0ul;
    Bitboard bitboard_miai = 0ul;
    Bitboard bitboard_claimeven = 0ul;
    Bitboard bitboard_claimodd = 0ul;
    Bitboard bitboard_plus = 0ul;
    Bitboard bitboard_equal = 0ul;
    Bitboard bitboard_minus = 0ul;
    Bitboard bitboard_urgent = 0ul;
    Bitboard bitboard_then = 0ul;
    Bitboard bitboard_if = 0ul;
    void populate_char_array(const array<string, C4_HEIGHT>& source);
    bool validate(C4Board b);
    bool validate_recursive_call(C4Board b, unordered_set<double>& wins_cache);
    char get_char(const int x, const int y) const;
    void set_char(const int x, const int y, const char c);
    void set_char_bitboard(const Bitboard point, const char c);
    char get_char_from_char_array(const int x, const int y) const;
    char get_char_from_bitboards(const int x, const int y) const;
    bool check_ss_matches_board(C4Board b);

    string to_string() const {
        string s(C4_WIDTH*C4_HEIGHT, ' ');
        for (int y = 0; y < C4_HEIGHT; ++y)
            for (int x = 0; x < C4_WIDTH; ++x)
                s[x+y*C4_WIDTH] = get_char(x, y);
        return s;
    }
};

SteadyState read_from_file(const string& filename, bool read_reverse) {
    array<string, C4_HEIGHT> chars;

    ifstream file(filename);
    if (file.is_open()) {
        for (int y = 0; y < C4_HEIGHT; ++y) {
            string line;
            if (getline(file, line)) { // Read the entire line as a string
                // Check if the line length matches the expected width
                if (line.length() == static_cast<size_t>(C4_WIDTH)) {
                    if (read_reverse) reverse(line.begin(), line.end());
                    chars[y] = line;
                } else throw runtime_error("Invalid line length in the file " + filename);
            } else throw runtime_error("STEADYSTATE CACHE READ ERROR " + filename);
        }
    } else throw runtime_error("Failed to read SteadyState file " + filename);
    return SteadyState(chars);
}

SteadyState make_steady_state_from_string(const string& input) {
    // Check that the input length matches the expected size
    if (input.length() != static_cast<size_t>(C4_WIDTH * C4_HEIGHT)) {
        throw runtime_error("Invalid input length. Expected " + to_string(C4_WIDTH * C4_HEIGHT));
    }

    // Create an array to hold the rows
    array<string, C4_HEIGHT> chars;

    // Fill the array with chunks of C4_WIDTH length from the input string
    for (int y = 0; y < C4_HEIGHT; ++y) {
        chars[y] = input.substr(y * C4_WIDTH, C4_WIDTH);
    }

    return SteadyState(chars);
}

string reverse_ss(const std::string& input) {
    // Calculate the expected length of the input string
    int expectedLength = C4_WIDTH * C4_HEIGHT;

    // Validate the input string length
    if (input.length() != expectedLength) {
        throw invalid_argument("Input string length does not match C4_WIDTH * C4_HEIGHT");
    }

    // Output string to store the result
    string output = input;

    // Reverse each chunk of length C4_WIDTH
    for (int i = 0; i < C4_HEIGHT; ++i) {
        int startIdx = i * C4_WIDTH;
        reverse(output.begin() + startIdx, output.begin() + startIdx + C4_WIDTH);
    }

    return output;
}
