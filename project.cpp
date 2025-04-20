#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <conio.h>

#define LTARROW 0x4B
#define RTARROW 0x4D
#define UPARROW 0x48
#define DNARROW 0x50
#define CR 0x0d
#define ESC 0x1b
#define F1_Key 0x3b00
#define F2_Key 0x3c00
#define F3_Key 0x3d00
#define F4_Key 0x3e00
#define F5_Key 0x3f00
#define F6_Key 0x4000
#define F7_Key 0x4100
#define F8_Key 0x4200
#define F9_Key 0x4300
#define F10_Key 0x4400

#define color_black 0
#define color_dark_blue 1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red 4
#define color_magenta 5
#define color_orange 6
#define color_light_gray 7
#define color_gray 8
#define color_blue 9
#define color_green 10
#define color_cyan 11
#define color_red 12
#define color_pink 13
#define color_yellow 14
#define color_white 15

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#endif

using namespace std;
namespace fs = filesystem;

string get_textcolor_code(const int textcolor)
{ // Linux only
    switch (textcolor)
    {
    case 0:
        return "30"; // color_black      0
    case 1:
        return "34"; // color_dark_blue  1
    case 2:
        return "32"; // color_dark_green 2
    case 3:
        return "36"; // color_light_blue 3
    case 4:
        return "31"; // color_dark_red   4
    case 5:
        return "35"; // color_magenta    5
    case 6:
        return "33"; // color_orange     6
    case 7:
        return "37"; // color_light_gray 7
    case 8:
        return "90"; // color_gray       8
    case 9:
        return "94"; // color_blue       9
    case 10:
        return "92"; // color_green     10
    case 11:
        return "96"; // color_cyan      11
    case 12:
        return "91"; // color_red       12
    case 13:
        return "95"; // color_pink      13
    case 14:
        return "93"; // color_yellow    14
    case 15:
        return "97"; // color_white     15
    default:
        return "37";
    }
}

string get_backgroundcolor_code(const int backgroundcolor)
{ // Linux only
    switch (backgroundcolor)
    {
    case 0:
        return "40"; // color_black      0
    case 1:
        return "44"; // color_dark_blue  1
    case 2:
        return "42"; // color_dark_green 2
    case 3:
        return "46"; // color_light_blue 3
    case 4:
        return "41"; // color_dark_red   4
    case 5:
        return "45"; // color_magenta    5
    case 6:
        return "43"; // color_orange     6
    case 7:
        return "47"; // color_light_gray 7
    case 8:
        return "100"; // color_gray       8
    case 9:
        return "104"; // color_blue       9
    case 10:
        return "102"; // color_green     10
    case 11:
        return "106"; // color_cyan      11
    case 12:
        return "101"; // color_red       12
    case 13:
        return "105"; // color_pink      13
    case 14:
        return "103"; // color_yellow    14
    case 15:
        return "107"; // color_white     15
    default:
        return "40";
    }
}

string get_print_color(const int textcolor)
{ // Linux only
    return "\033[" + get_textcolor_code(textcolor) + "m";
}

string get_print_color(const int textcolor, const int backgroundcolor)
{ // Linux only
    return "\033[" + get_textcolor_code(textcolor) + ";" + get_backgroundcolor_code(backgroundcolor) + "m";
}

void print_color(const int textcolor)
{
#if defined(_WIN32)
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, textcolor);
#elif defined(__linux__)
    cout << get_print_color(textcolor);
#endif // Windows/Linux
}

void print_color(const int textcolor, const int backgroundcolor)
{
#if defined(_WIN32)
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, backgroundcolor << 4 | textcolor);
#elif defined(__linux__)
    cout << get_print_color(textcolor, backgroundcolor);
#endif // Windows/Linux
}

void print_color_reset()
{
#if defined(_WIN32)
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 7); // reset color
#elif defined(__linux__)
    cout << "\033[0m"; // reset color
#endif // Windows/Linux
}

void println(const string &s = "")
{
    cout << s << endl;
}

void print(const string &s = "")
{
    cout << s;
}

void print(const string &s, const int textcolor)
{
    print_color(textcolor);
    cout << s;
    print_color_reset();
}

void print(const string &s, const int textcolor, const int backgroundcolor)
{
    print_color(textcolor, backgroundcolor);
    cout << s;
    print_color_reset();
}

void print_no_reset(const string &s, const int textcolor)
{ // print with color, but don't reset color afterwards (faster)
    print_color(textcolor);
    cout << s;
}

void print_no_reset(const string &s, const int textcolor, const int backgroundcolor)
{ // print with color, but don't reset color afterwards (faster)
    print_color(textcolor, backgroundcolor);
    cout << s;
}

#ifdef __MINGW32__
const int UP_KEY = 72;
const int DOWN_KEY = 80;
const int ENTER_KEY = 13;
const int RIGHT_KEY = 77;
const int LEFT_KEY = 75;
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <termios.h>
const int UP_KEY = 65;
const int DOWN_KEY = 66;
const int RIGHT_KEY = 67;
const int LEFT_KEY = 68;
const int ENTER_KEY = int('\n');
int getch(void);
#endif

#if defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

void clean();
int input_number(string s);
void output_menu_list(int n);
bool make_maze(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns, int **maze_map_numbers, int max_value, int min_value, int maxb, int minb);
void create_map(string level);
string map_save(int number_of_rows, int number_of_columns, int **maze_map_numbers, int current_row, int current_column, int **path, int length);
void playground(int **maze_map_numbers, int length, int number_of_rows, int number_of_columns, string file_name);
void map_output(int number_of_rows, int number_of_columns, int **maze_map_numbers, int current_row, int current_column, int **path, int length);
void save_data(string player_name, string time, string result, string file_name, string date);
bool find_answer(int **maze_map_numbers, int length, int number_of_rows, int number_of_columns, int current_row, int current_column, int i, int **path, int sum_of_numbers_on_path);
void output_maps_list(int i);
void select_map(string function);
string find_address();
void make_maze_from_file(string address, string function);
void history_menu();
void history_menu_out(int number_of_rows);
void users_list();
void users_list_output(int i);
void output_users_info(string address);
void output_last_ten_games_history();
void leaderboard();
bool is_this_path_blocked(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns);
bool is_on_the_path(int **path, int current_row, int current_column, int length);
bool is_path_unvalid(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns, int up_move_counter, int right_move_counter, int down_move_counter, int left_move_counter);

struct info
{
    string name;
    int win_rate;
    double total_time;
};

vector<pair<int, string>> users_name_winrate;
vector<pair<int, string>> maps_in_folder;
vector<pair<int, string>> users_list_in_folder;

int main()
{
    string ad;

    print("Welcome to Maze Maverick\n", color_pink, color_black);
    char q;
    int number_of_rows = 1;
    output_menu_list(1);
    while (true)
    {
        q = getch();
        clean();
        if ((int)q == 72 && number_of_rows - 1 > 0)
        {
            number_of_rows--;
        }
        else if ((int)q == 80 && (number_of_rows + 1) <= 9)
        {
            number_of_rows++;
        }
        else if ((int)q == 13)
        {
            if (number_of_rows == 1)
            {
                create_map("Easy");
            }
            if (number_of_rows == 2)
            {
                create_map("Hard");
            }
            if (number_of_rows == 3)
            {
                select_map("play");
            }
            if (number_of_rows == 4)
            {
                print("Please enter your file address : ", color_cyan, color_black);
                cin >> ad;
                make_maze_from_file(ad, "play");
            }
            if (number_of_rows == 5)
            {
                select_map("find");
            }
            if (number_of_rows == 6)
            {
                print("Please enter your file address : ", color_cyan, color_black);
                cin >> ad;
                make_maze_from_file(ad, "find");
            }
            if (number_of_rows == 7)
            {
                history_menu();
            }
            if (number_of_rows == 8)
            {
                leaderboard();
            }
            if (number_of_rows == 9)
            {
                print("Have a nice day :))", color_light_blue, color_black);
                exit(0);
            }
            number_of_rows = 1;
            clean();
        }
        else
        {
        }
        output_menu_list(number_of_rows);
    }

    return 0;
}

/// <summary>this function finds answer of maze if exists.</summary>
bool find_answer(int **maze_map_numbers, int length, int number_of_rows, int number_of_columns, int current_row, int current_column, int current_path_length, int **path, int sum_of_numbers_on_path)
{
    char q;
    if ((current_row == number_of_rows - 1 && current_column == number_of_columns - 1) || (current_path_length == length))
    {
        if ((float)sum_of_numbers_on_path / 2 == maze_map_numbers[number_of_rows - 1][number_of_columns - 1] && current_path_length == length && (current_row == number_of_rows - 1 && current_column == number_of_columns - 1))
        {
            clean();
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            print("\nPress any key to show other results if exist", color_cyan, color_black);
            print("\nPress (Backspace) to return", color_orange, color_black);
            q = getch();
            if (q == 8)
            {
                return 1;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    if ((is_on_the_path(path, current_row + 1, current_column, length) || current_row + 1 >= number_of_rows || (maze_map_numbers[current_row + 1][current_column] == 0 && current_row + 1 != number_of_rows - 1)) && (is_on_the_path(path, current_row - 1, current_column, length) || current_row - 1 < 0 || (maze_map_numbers[current_row - 1][current_column] == 0 && current_row - 1 == number_of_rows - 1)) && (is_on_the_path(path, current_row, current_column + 1, length) || current_column + 1 >= number_of_columns || (maze_map_numbers[current_row][current_column + 1] == 0 && current_column + 1 == number_of_columns - 1)) && (is_on_the_path(path, current_row, current_column - 1, length) || current_column - 1 < 0 || maze_map_numbers[current_row][current_column - 1] == 0))
    {
        return 0;
    }

    if (current_column + 1 < number_of_columns && !is_on_the_path(path, current_row, current_column + 1, length) && (maze_map_numbers[current_row][current_column + 1] != 0 || (current_row == number_of_rows - 1 && current_column + 1 == number_of_columns - 1)))
    {
        path[current_path_length][0] = current_row;
        path[current_path_length][1] = current_column;
        current_column = current_column + 1;

        sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
        current_path_length++;
        if (find_answer(maze_map_numbers, length, number_of_rows, number_of_columns, current_row, current_column, current_path_length, path, sum_of_numbers_on_path))
        {
            return 1;
        }

        current_path_length--;
        path[current_path_length][0] = number_of_rows;
        path[current_path_length][1] = number_of_columns;
        sum_of_numbers_on_path = sum_of_numbers_on_path - maze_map_numbers[current_row][current_column];
        current_column = current_column - 1;
    }
    if (current_row - 1 >= 0 && !is_on_the_path(path, current_row - 1, current_column, length) && (maze_map_numbers[current_row - 1][current_column] != 0 || (current_row - 1 == number_of_rows - 1 && current_column == number_of_columns - 1)))
    {
        path[current_path_length][0] = current_row;
        path[current_path_length][1] = current_column;
        current_row = current_row - 1;
        sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
        current_path_length++;
        if (find_answer(maze_map_numbers, length, number_of_rows, number_of_columns, current_row, current_column, current_path_length, path, sum_of_numbers_on_path))
        {
            return 1;
        }
        current_path_length--;
        path[current_path_length][0] = number_of_rows;
        path[current_path_length][1] = number_of_columns;
        sum_of_numbers_on_path = sum_of_numbers_on_path - maze_map_numbers[current_row][current_column];
        current_row = current_row + 1;
    }
    if ((current_row + 1) < number_of_rows && !is_on_the_path(path, current_row + 1, current_column, length) && (maze_map_numbers[current_row + 1][current_column] != 0 || (current_row + 1 == number_of_rows - 1 && current_column == number_of_columns - 1)))
    {
        path[current_path_length][0] = current_row;
        path[current_path_length][1] = current_column;
        current_row = current_row + 1;
        sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
        current_path_length++;
        if (find_answer(maze_map_numbers, length, number_of_rows, number_of_columns, current_row, current_column, current_path_length, path, sum_of_numbers_on_path))
        {
            return 1;
        }
        current_path_length--;
        path[current_path_length][0] = number_of_rows;
        path[current_path_length][1] = number_of_columns;
        sum_of_numbers_on_path = sum_of_numbers_on_path - maze_map_numbers[current_row][current_column];
        current_row = current_row - 1;
    }
    if (current_column - 1 >= 0 && !is_on_the_path(path, current_row, current_column - 1, length) && (maze_map_numbers[current_row][current_column - 1] != 0 || (current_row == number_of_rows - 1 && current_column - 1 == number_of_columns - 1)))
    {

        path[current_path_length][0] = current_row;
        path[current_path_length][1] = current_column;
        current_column = current_column - 1;

        sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
        current_path_length++;
        if (find_answer(maze_map_numbers, length, number_of_rows, number_of_columns, current_row, current_column, current_path_length, path, sum_of_numbers_on_path))
        {
            return 1;
        }
        current_path_length--;
        path[current_path_length][0] = number_of_rows;
        path[current_path_length][1] = number_of_columns;
        sum_of_numbers_on_path = sum_of_numbers_on_path - maze_map_numbers[current_row][current_column];
        current_column = current_column + 1;
    }
    return 0;
}
/// <summary>this function outputs history menu.</summary>
void history_menu_out(int number_of_rows)
{

    if (number_of_rows == 1)
    {
        print("Back to menu", color_green, color_black);
        cout << "\n";
    }
    else
    {
        cout << "Back to menu\n";
    }
    if (number_of_rows == 2)
    {
        print("History of players\n", color_green, color_black);
    }
    else
    {
        cout << "History of players\n";
    }
    if (number_of_rows == 3)
    {
        print("Last 10 games\n", color_green, color_black);
    }
    else
    {
        cout << "Last 10 games\n";
    }
}

/// <summary>player can run one of history menu.</summary>
void history_menu()
{
    clean();
    char q;
    int number_of_rows = 1;
    history_menu_out(number_of_rows);
    while (1)
    {

        q = getch();

        if ((int)q == 72 && number_of_rows - 1 > 0)
        {
            number_of_rows--;
        }
        else if ((int)q == 80 && (number_of_rows + 1) <= 3)
        {
            number_of_rows++;
        }
        if (q == 13)
        {
            if (number_of_rows == 1)
            {
                return;
            }
            else if (number_of_rows == 2)
            {
                users_list();
            }
            else if (number_of_rows == 3)
            {
                output_last_ten_games_history();
            }
        }
        clean();
        history_menu_out(number_of_rows);
    }
}
/// <summary>this function outputs last ten games history.</summary>
void output_last_ten_games_history()
{
    string s = find_address() + (char)92 + (char)92 + "Stats" + (char)92 + (char)92 + "history.txt";
    ifstream A(s);
    int i = 0;
    string p;
    clean();
    print("Last 10 games : \n\n", color_dark_green, color_black);
    while (i < 20)
    {
        getline(A, p);
        print(p, color_cyan, color_black);
        cout << "\n";

        i++;
    }
    A.close();

    print("\n\nPress any key to continue", color_orange, color_black);
    char q = getch();
}
/// <summary>this function saves users data in history file.</summary>
void save_data(string player_name, string time, string result, string file_name, string date)
{

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = std::chrono::system_clock::to_time_t(end);

    string gably, t;
    ifstream B("Stats\\history.txt");
    while (getline(B, t))
    {

        gably = gably + t + "\n";
    }
    B.close();
    ofstream A("Stats\\history.txt");

    A << player_name;
    int i = player_name.size();
    while (i < 15)
    {
        A << " ";
        i++;
    }

    A << "    " << file_name;
    i = file_name.size();
    while (i < 15)
    {
        A << " ";
        i++;
    }
    A << "    " << result;
    i = result.size();
    while (i < 6)
    {
        A << " ";
        i++;
    }
    time = time.substr(0, time.find('.') + 3);
    A << "    " << time << " s";
    i = time.size();
    while (i < 8)
    {
        A << " ";
        i++;
    }
    A << "    " << std::ctime(&end_time);
    A << "\n"
      << gably;
    A.close();
    string user_path = player_name;
    user_path = "Users\\" + user_path + ".txt";
    gably = "";
    ifstream D(user_path);
    while (getline(D, t))
    {

        gably = gably + t + "\n";
    }
    D.close();

    ofstream C(user_path);
    C << player_name;
    i = player_name.size();
    while (i < 15)
    {
        C << " ";
        i++;
    }

    C << "    " << file_name;
    i = file_name.size();
    while (i < 15)
    {
        C << " ";
        i++;
    }
    C << "    " << result;
    i = result.size();
    while (i < 6)
    {
        C << " ";
        i++;
    }
    time = time.substr(0, time.find('.') + 3);
    C << "    " << time << " s";
    i = time.size();
    while (i < 8)
    {
        C << " ";
        i++;
    }
    C << "    " << std::ctime(&end_time);
    C << "\n"
      << gably;
    C.close();
}

/// <summary>this function creates user list according to folder and opens one according to players choise.</summary>
void users_list()
{
    clean();
    int index;
    string s;
    string path = find_address() + (char)92 + (char)92 + "Users";
    int i = 0;
    while (i != users_list_in_folder.size())
    {
        users_list_in_folder.pop_back();
    }

    struct stat sb;
    users_list_in_folder.push_back(make_pair(0, "Back to menu"));
    int iii = 1;
    for (const auto &entry : fs::directory_iterator(path))
    {
        iii++;
        filesystem::path outfilename = entry.path();
        string outfilename_str = outfilename.string();
        const char *path = outfilename_str.c_str();
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            index = outfilename_str.find("Users", 5);
            s = outfilename_str.substr(index + 6);
            users_list_in_folder.push_back(make_pair(iii, s));
        }
    }
    i = 0;
    users_list_output(0);
    char q = 'm';
    while ((int)q != 13)
    {
        q = getch();
        if ((int)q == 72 && i - 1 >= 0)
        {
            i--;
        }
        else if ((int)q == 80 && (i + 1) < iii)
        {
            i++;
        }

        clean();

        users_list_output(i);
    }
    if (users_list_in_folder[i].second == "Back to menu")
    {
        return;
    }
    string f = "";
    f = "Users";
    f = f + (char)92;
    f = f + users_list_in_folder[i].second;
    output_users_info(f);
    clean();
}

/// <summary>this function outputs users list in the folder with different color.</summary>
void users_list_output(int i)
{
    int ii = 0;
    while (ii != users_list_in_folder.size())
    {

        if (i == ii)
        {
            print(users_list_in_folder[ii].second, color_green, color_black);
            cout << "\n";
        }
        else
        {
            cout << users_list_in_folder[ii].second << "\n";
        }
        ii++;
    }
}

/// <summary>this function outputs user info.</summary>
void output_users_info(string address)
{
    clean();
    ifstream A(address);
    string t;
    int i = 0, j = 0;
    while (getline(A, t))
    {
        i++;
    }
    A.close();
    ifstream B(address);
    double time, total_time = 0, times;
    int win_counter = 0;
    string date, name;
    bool flag = 1;
    while (j != i / 2)
    {
        B >> name >> t >> t;
        if (t == "WON")
        {
            win_counter++;
        }
        B >> time;

        total_time += time;
        B >> t;

        B >> t;
        if (flag)
        {
            date = date + " " + t;
        }
        B >> t;
        if (flag)
        {
            date = date + " " + t;
        }
        B >> t;
        if (flag)
        {
            date = date + " " + t;
        }
        B >> t;
        if (flag)
        {
            date = date + " " + t;
        }

        B >> t;
        if (flag)
        {
            date = date + " " + t;
            flag = 0;
        }
        j++;
    }
    B.close();

    print("Player`s name : " + name, color_cyan, color_black);
    print("\n\nTotal games : " + to_string(i / 2), color_cyan, color_black);
    print("\n\nGames won : " + to_string(win_counter), color_cyan, color_black);
    print("\n\nTotal time : " + to_string(total_time).substr(0, to_string(total_time).find('.') + 3), color_cyan, color_black);
    print("\n\nLast date : " + date, color_cyan, color_black);

    print("\n\nPress any key to continue", color_orange, color_black);
    char q = getch();
}

/// <summary>this function out puts 3 best players.</summary>
void leaderboard()
{
    clean();
    string s;
    string path = find_address() + (char)92 + (char)92 + "Users";
    int i = 0;
    while (i != users_name_winrate.size())
    {
        users_name_winrate.pop_back();
    }

    struct stat sb;
    int iii = 1;
    for (const auto &entry : fs::directory_iterator(path))
    {
        iii++;
        filesystem::path outfilename = entry.path();
        string outfilename_str = outfilename.string();
        const char *path = outfilename_str.c_str();
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            users_name_winrate.push_back(make_pair(iii, outfilename_str));
        }
    }
    int oo = 0;
    char q = 'm';
    info all[users_name_winrate.size()];
    while (oo != users_name_winrate.size())
    {

        ifstream A(users_name_winrate[oo].second);
        string t;
        int i = 0, j = 0;
        while (getline(A, t))
        {
            i++;
        }
        A.close();
        ifstream B(users_name_winrate[oo].second);
        double time, total_time = 0, times;
        int win_counter = 0;
        while (j != i / 2)
        {
            B >> t;
            all[oo].name = t;
            B >> t >> t;
            if (t == "WON")
            {
                win_counter++;
            }
            all[oo].win_rate = win_counter;
            B >> time;
            total_time += time;
            B >> t >> t >> t;
            B >> t >> t >> t;
            j++;
        }
        all[oo].total_time = total_time;
        B.close();
        oo++;
    }
    oo = 0;
    int fs = 0, ss = 0, ts = 0;

    oo = 0;
    while (oo != users_name_winrate.size())
    {
        if ((all[oo].win_rate > all[fs].win_rate || (all[oo].win_rate == all[fs].win_rate && all[oo].total_time < all[fs].total_time)) && oo != fs && oo != ss)
        {
            fs = oo;
        }
        oo++;
    }
    oo = 0;
    while (oo != users_name_winrate.size())
    {
        if ((all[oo].win_rate > all[ss].win_rate || (all[oo].win_rate == all[ss].win_rate && all[oo].total_time < all[ss].total_time)) && oo != fs && oo != ss)
        {
            ss = oo;
        }
        oo++;
    }
    oo = 0;
    while (oo != users_name_winrate.size())
    {
        if ((all[oo].win_rate > all[ts].win_rate || (all[oo].win_rate == all[ts].win_rate && all[oo].total_time < all[ts].total_time)) && oo != fs && oo != ss)
        {
            ts = oo;
        }
        oo++;
    }
    int number_of_space = all[fs].name.size();
    if (number_of_space < all[ss].name.size())
    {
        number_of_space = all[ss].name.size();
    }
    if (number_of_space < all[ts].name.size())
    {
        number_of_space = all[ts].name.size();
    }

    print(all[fs].name, color_dark_green, color_black);
    i = all[fs].name.size();
    while (i < number_of_space)
    {
        cout << " ";
        i++;
    }
    print("     Win rate : " + to_string(all[fs].win_rate) + "     Total time : " + to_string(all[fs].total_time).substr(0, to_string(all[fs].total_time).find('.') + 3) + "\n\n", color_dark_green, color_black);
    string ty = to_string(all[fs].total_time);

    if (users_name_winrate.size() > 1)
    {

        print(all[ss].name, color_cyan, color_black);
        i = all[ss].name.size();
        while (i < number_of_space)
        {
            cout << " ";
            i++;
        }

        print("     Win rate : " + to_string(all[ss].win_rate) + "     Total time : " + to_string(all[ss].total_time).substr(0, to_string(all[ss].total_time).find('.') + 3) + "\n\n", color_cyan, color_black);
    }
    if (users_name_winrate.size() > 2)
    {

        print(all[ts].name, color_pink, color_black);
        i = all[ts].name.size();
        while (i < number_of_space)
        {
            cout << " ";
            i++;
        }
        print("     Win rate : " + to_string(all[ts].win_rate) + "     Total time : " + to_string(all[ts].total_time).substr(0, to_string(all[ts].total_time).find('.') + 3) + "\n\n", color_pink, color_black);
    }
    print("Press any key to continue", color_orange, color_black);
    q = getch();

    clean();
}

/// <summary>this function changes string to int if it is possible.</summary>
int input_number(string s)
{
    int i = s.size() - 1, n = 1, num = 0;
    while (i != -1)
    {
        if (isdigit(s[i]) || (i == 0 && s[i] == '-'))
        {
            num = num + (s[i] - '0') * n;
            n = n * 10;
        }
        else
        {
            return -1;
        }

        i--;
    }
    return num;
}
/// <summary>this function returns 1 if the path was blocked.</summary>
bool is_this_path_blocked(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns)
{
    if ((is_on_the_path(path, current_row + 1, current_column, length) || current_row + 1 >= number_of_rows) && (is_on_the_path(path, current_row - 1, current_column, length) || current_row - 1 < 0) && (is_on_the_path(path, current_row, current_column + 1, length) || current_column + 1 >= number_of_columns) && (is_on_the_path(path, current_row, current_column - 1, length) || current_column - 1 < 0))
    {
        return 1;
    }
    return 0;
}

/// <summary>this function finds address of file as path.</summary>
string find_address()
{
    char tmp[256];
    getcwd(tmp, 256);
    string s = tmp, q;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == (char)92)
        {
            q += s[i];
        }
        q += s[i];
    }
    return q;
}

/// <summary>this function outputs map with diffrent colors.</summary>
void map_output(int number_of_rows, int number_of_columns, int **maze_map_numbers, int current_row, int current_column, int **path, int length)
{
    int max_l = to_string(maze_map_numbers[0][0]).size();
    for (int i = 0; i < number_of_rows; i++)
    {
        for (int j = 0; j < number_of_columns; j++)
        {
            if (to_string(maze_map_numbers[i][j]).size() > max_l)
            {
                max_l = to_string(maze_map_numbers[i][j]).size();
            }
        }
    }

    for (int i = 0; i < number_of_rows * 2 + 1; i++)
    {
        cout << endl;

        if (i % 2 != 0)
        {

            for (int j = 0; j < number_of_columns * 2 + 1; j++)
            {
                if (j % 2 == 0)
                {
                    if (j == 0)
                    {

                        cout << char(186) << "  ";
                    }
                    else
                    {
                        cout << "  " << char(186) << "  ";
                    }
                }
                else
                {
                    bool flag2 = 1;
                    string out = to_string(maze_map_numbers[(i - 1) / 2][(j - 1) / 2]);
                    while (out.size() < max_l)
                    {
                        if (flag2)
                        {
                            out = out + ' ';
                            flag2 = 0;
                        }
                        else
                        {
                            out = ' ' + out;
                            flag2 = 1;
                        }
                    }

                    bool flag = 1;
                    for (size_t current_path_length = 0; current_path_length < length; current_path_length++)
                    {
                        if (path[current_path_length][0] == (i - 1) / 2 && path[current_path_length][1] == (j - 1) / 2)
                        {
                            flag = 0;
                            print(out, color_green, color_black);
                        }
                    }
                    if ((i - 1) / 2 == current_row && (j - 1) / 2 == current_column)
                    {
                        print(out, color_pink, color_black);
                    }
                    else if (maze_map_numbers[(i - 1) / 2][(j - 1) / 2] == 0 && ((i - 1) / 2 != number_of_rows - 1 || (j - 1) / 2 != number_of_columns - 1))
                    {
                        print(out, color_red, color_black);
                    }
                    else if (flag == 1)
                    {
                        print(out, color_white, color_black);
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < number_of_columns * (5 + max_l) + 1; j++)
            {

                if (j % (5 + max_l) == 0)
                {
                    if (i == 0)
                    {

                        if (j == 0)
                        {
                            cout << char(201);
                        }
                        else if (j == number_of_columns * (5 + max_l))
                        {
                            cout << char(187);
                        }
                        else
                        {
                            cout << char(203);
                        }
                    }
                    else if (i == 2 * number_of_rows)
                    {
                        if (j == 0)
                        {
                            cout << char(200);
                        }
                        else if (j == number_of_columns * (5 + max_l))
                        {
                            cout << char(188);
                        }
                        else
                        {
                            cout << char(202);
                        }
                    }
                    else
                    {
                        if (j == 0)
                        {
                            cout << char(204);
                        }
                        else if (j == number_of_columns * (5 + max_l))
                        {
                            cout << char(185);
                        }
                        else
                        {
                            cout << char(206);
                        }
                    }
                }
                else
                {
                    cout << char(205);
                }
            }
        }
    }
}

/// <summary>this function saves map in folder.</summary>
string map_save(int number_of_rows, int number_of_columns, int **maze_map_numbers, int current_row, int current_column, int **path, int length)
{
    string s;

    int max_l = to_string(maze_map_numbers[0][0]).size();
    for (int i = 0; i < number_of_rows; i++)
    {
        for (int j = 0; j < number_of_columns; j++)
        {
            if (to_string(maze_map_numbers[i][j]).size() > max_l)
            {
                max_l = to_string(maze_map_numbers[i][j]).size();
            }
        }
    }

    for (int i = 0; i < number_of_rows * 2 + 1; i++)
    {
        s += "\n";

        if (i % 2 != 0)
        {

            for (int j = 0; j < number_of_columns * 2 + 1; j++)
            {
                if (j % 2 == 0)
                {
                    if (j == 0)
                    {
                        s += "|  ";
                    }
                    else
                    {
                        s += "  |  ";
                    }
                }
                else
                {
                    bool flag2 = 1;
                    string out = to_string(maze_map_numbers[(i - 1) / 2][(j - 1) / 2]);
                    while (out.size() < max_l)
                    {
                        if (flag2)
                        {
                            out = out + ' ';
                            flag2 = 0;
                        }
                        else
                        {
                            out = ' ' + out;
                            flag2 = 1;
                        }
                    }

                    bool flag = 1;
                    for (size_t current_path_length = 0; current_path_length < length; current_path_length++)
                    {
                        if (path[current_path_length][0] == (i - 1) / 2 && path[current_path_length][1] == (j - 1) / 2)
                        {
                            flag = 0;
                            s += out;
                        }
                    }

                    if ((i - 1) / 2 == current_row && (j - 1) / 2 == current_column)
                    {
                        s += out;
                    }
                    else if (maze_map_numbers[(i - 1) / 2][(j - 1) / 2] == 0 && ((i - 1) / 2 != number_of_rows - 1 || (j - 1) / 2 != number_of_columns - 1))
                    {
                        s += out;
                    }
                    else if (flag == 1)
                    {
                        s += out;
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < number_of_columns * (5 + max_l) + 1; j++)
            {
                s += "-";
            }
        }
    }
    return s;
}

/// <summary>this function creates map with giving its level.</summary>
void create_map(string level)
{
    char q;
    int number_of_rows = -1, number_of_columns = -1, length = -1;
    int current_row = 0, current_column = 0;
    int max_value = -1, min_value = -1, max_block = -1, min_block = -1;
    string map, input;

    if (level == "Easy")
    {
        print("\nPress any key to create a " + level + " map", color_cyan, color_black);
    }
    if (level == "Hard")
    {
        print("\nPress any key to create a " + level + " map", color_cyan, color_black);
    }
    print("\nPress (Backspace) to return to output_menu_list", color_orange, color_black);
    q = getch();
    if (q == 8)
    {
        return;
    }
    clean();
    print("\nEnter number of lines : ", color_cyan, color_black);

    bool f = 0;
    while (number_of_rows == -1)
    {
        cin >> input;
        number_of_rows = input_number(input);
        if (number_of_rows == -1)
        {
            f = 1;
        }
        else
        {
            break;
        }
        if (f)
        {
            print("\nIncorrect format!! please try again.", color_red, color_black);
        }
        f = 1;
    }

    print("\nEnter number of columns : ", color_cyan, color_black);
    f = 0;
    while (number_of_columns == -1)
    {
        cin >> input;
        number_of_columns = input_number(input);
        if (number_of_columns == -1)
        {
            f = 1;
        }
        else
        {
            break;
        }
        if (f)
        {
            print("\nIncorrect format!! please try again.", color_red, color_black);
        }
        f = 1;
    }
    if (level != "Easy")
    {
        print("\nEnter length of the path : ", color_cyan, color_black);

        f = 0;
        while (length == -1)
        {
            cin >> input;
            length = input_number(input);
            if (length == -1)
            {
                f = 1;
            }
            else
            {
                break;
            }
            if (f)
            {
                print("\nIncorrect format!! please try again.", color_red, color_black);
            }
            f = 1;
        }
        print("\nEnter minimum value of numbers : ", color_cyan, color_black);

        f = 0;
        while (min_value == -1)
        {
            cin >> input;
            min_value = input_number(input);
            if (min_value == -1)
            {
                f = 1;
            }
            else
            {
                break;
            }
            if (f)
            {
                print("\nIncorrect format!! please try again.", color_red, color_black);
            }
            f = 1;
        }
        print("\nEnter maximum value of numbers : ", color_cyan, color_black);
        f = 0;
        while (max_value == -1)
        {
            cin >> input;
            max_value = input_number(input);
            if (max_value == -1)
            {
                f = 1;
            }
            else
            {
                break;
            }
            if (f)
            {
                print("\nIncorrect format!! please try again.", color_red, color_black);
            }
            f = 1;
        }
        print("\nEnter minimum number of blocks : ", color_cyan, color_black);

        f = 0;
        while (min_block == -1)
        {
            cin >> input;
            min_block = input_number(input);
            if (min_block == -1)
            {
                f = 1;
            }
            else
            {
                break;
            }
            if (f)
            {
                print("\nIncorrect format!! please try again.", color_red, color_black);
            }
            f = 1;
        }
        print("\nEnter maximum number of blocks : ", color_cyan, color_black);

        f = 0;
        while (max_block == -1)
        {
            cin >> input;
            max_block = input_number(input);
            if (max_block == -1)
            {
                f = 1;
            }
            else
            {
                break;
            }
            if (f)
            {
                print("\nIncorrect format!! please try again.", color_red, color_black);
            }
            f = 1;
        }
    }
    else
    {
        length = number_of_rows + number_of_columns - 2;
        min_value = -3;
        max_value = 3;
        min_block = 2;
        max_block = 5;
    }
    if ((number_of_rows + number_of_columns) % 2 != length % 2)
    {
        print("\nInvalid path length!!", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (length > number_of_rows * number_of_columns - 1)
    {
        print("\nInvalid path length!!", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (length < number_of_rows + number_of_columns - 2)
    {
        print("\nInvalid path length!!", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (length + min_block + 1 > number_of_rows * number_of_columns)
    {
        print("\nInvalid number of blocks!!", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (min_block > max_block)
    {

        print("\nInvalid minimum and maximum blocks!!", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (min_block < 0)
    {
        cerr << "\nInvalid minimum blocks!!";
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    if (min_value > max_value)
    {
        cerr << "\nInvalid minimum and maximum values!!";
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }

    int **path = new int *[length];
    for (int i = 0; i < length; i++)
    {
        *(path + i) = new int[2];
        for (int j = 0; j < 2; j++)
        {
            path[i][j] = number_of_rows;
        }
    }

    int **maze_map_numbers = new int *[number_of_rows];
    for (int i = 0; i < number_of_rows; i++)
    {
        *(maze_map_numbers + i) = new int[number_of_columns];
        for (int j = 0; j < number_of_columns; j++)
        {
            maze_map_numbers[i][j] = 0;
        }
    }

    make_maze(path, current_row, current_column, length, number_of_rows, number_of_columns, maze_map_numbers, max_value, min_value, max_block, min_block);
    map = map_save(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
    string name, addres;
    print("\nMap creation was successful", color_green, color_black);
    while (1)
    {
        print("\n\nPlease enter a name for your map : ", color_cyan, color_black);
        cin >> name;
        addres = (char)92 + level + '_' + name + '.' + "txt";
        addres = "Maps" + addres;
        ifstream P(addres);
        if (P.fail())
        {
            break;
        }
        P.close();
        addres = "";
        print("\nThere is a map with this name.", color_red, color_black);
    }
    print("\nYour map has been saved as \"" + level + '_' + name + ".txt" + '"', color_dark_green, color_black);
    ofstream A(addres);
    A << map;
    A << "\nMap name : " << name;
    A << "\nMap level : " << level;
    A << "\nPath length : " << length;

    A.close();

    print("\n\nPress any key to continue", color_orange, color_black);
    q = getch();
}

/// <summary>this function cleans terminal.</summary>
void clean()
{
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

/// <summary>this function makes maze from file.</summary>
void make_maze_from_file(string address, string function)
{

    bool flag = 1;
    char q;
    string t;
    int number_of_rows = 0, number_of_columns = -1, length;
    ifstream A(address);
    if (A.fail() == 1)
    {
        print("\nInvalid address", color_red, color_black);
        print("\n\nPress any key to continue", color_orange, color_black);
        q = getch();
        return;
    }
    while (1)
    {
        getline(A, t);

        if (t[0] == '|')
        {
            number_of_rows++;
            if (flag == 1)
            {
                for (int i = 0; i < t.size(); i++)
                {
                    if (t[i] == '|')
                    {
                        number_of_columns++;
                    }
                }
                flag = 0;
            }
        }
        if (t[0] == 'M')
        {
            getline(A, t);
            A >> t >> t >> t >> length;

            break;
        }
    }

    A.close();
    ifstream B(address);
    int **maze_map_numbers = new int *[number_of_rows];
    for (int i = 0; i < number_of_rows; i++)
    {
        *(maze_map_numbers + i) = new int[number_of_columns];
        for (int j = 0; j < number_of_columns; j++)
        {
            maze_map_numbers[i][j] = 0;
        }
    }
    int i = 0, j = 0, ii = 0, jj = 0;
    string temp;
    while (ii != number_of_rows)
    {
        getline(B, t);

        if (t[0] == '|')
        {
            while (j != t.size())
            {
                if (t[j] == '|')
                {
                }
                else if (t[j] == ' ')
                {
                    if (isdigit(t[j - 1]) == 1)
                    {
                        maze_map_numbers[ii][jj] = stoi(temp);
                        temp = "";
                        jj++;
                    }
                }
                else
                {
                    temp += t[j];
                }
                j++;
            }

            ii++;
        }
        jj = 0;
        j = 0;
        i += 2;
    }

    B.close();
    if (function == "find")
    {
        int **path = new int *[length];
        for (int i = 0; i < length; i++)
        {
            *(path + i) = new int[2];
            for (int j = 0; j < 2; j++)
            {
                path[i][j] = number_of_rows;
            }
        }
        if (!find_answer(maze_map_numbers, length, number_of_rows, number_of_columns, 0, 0, 0, path, maze_map_numbers[0][0]))
        {
            print("\nThere is no other result", color_red, color_black);
            print("\n\nPress any key to continue", color_orange, color_black);
            q = getch();
        }
    }
    if (function == "play")
    {
        string name;
        int i = address.size();
        while (i != 0)
        {
            if (address[i] == (char)92)
            {
                break;
            }
            name = address[i] + name;
            i--;
        }
        playground(maze_map_numbers, length, number_of_rows, number_of_columns, name);
    }
}

/// <summary>this function for player to solve maze.</summary>
void playground(int **maze_map_numbers, int length, int number_of_rows, int number_of_columns, string file_name)
{
    char q;
    int current_row = 0, current_column = 0;
    int **path = new int *[length];
    for (int i = 0; i < length; i++)
    {
        *(path + i) = new int[2];
        for (int j = 0; j < 2; j++)
        {
            path[i][j] = number_of_rows;
        }
    }
    string player_name;
    print("Enter your name : ", color_cyan, color_black);
    cin >> player_name;

    string result, time, date;

    auto start = chrono::steady_clock::now();
    map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);

    int sum_of_numbers_on_path = maze_map_numbers[0][0];
    for (size_t i = 0; i < length;)
    {

        print("\nYour sum : " + to_string(sum_of_numbers_on_path), color_cyan, color_black);
        print("\nYour path length : " + to_string(i), color_cyan, color_black);
        print("\nTarget path length : " + to_string(length), color_cyan, color_black);
        if ((is_on_the_path(path, current_row + 1, current_column, length) || current_row + 1 >= number_of_rows || (maze_map_numbers[current_row + 1][current_column] == 0 && !(current_row == number_of_rows - 1 && current_column == number_of_columns - 1))) && (is_on_the_path(path, current_row - 1, current_column, length) || current_row - 1 < 0 || (maze_map_numbers[current_row - 1][current_column] == 0 && !(current_row == number_of_rows - 1 && current_column == number_of_columns - 1))) && (is_on_the_path(path, current_row, current_column + 1, length) || current_column + 1 >= number_of_columns || (maze_map_numbers[current_row][current_column + 1] == 0 && !(current_row == number_of_rows - 1 && current_column == number_of_columns - 1))) && (is_on_the_path(path, current_row, current_column - 1, length) || current_column - 1 < 0 || (maze_map_numbers[current_row][current_column - 1] == 0 && !(current_row == number_of_rows - 1 && current_column == number_of_columns - 1))))
        {
            clean();
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            print("\nYOU LOST!!", color_red, color_black);
            print("\nYour sum : " + to_string(sum_of_numbers_on_path), color_cyan, color_black);
            print("\nYour path length : " + to_string(i), color_cyan, color_black);
            print("\nTarget path length : " + to_string(length), color_cyan, color_black);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            time = to_string(chrono::duration<double>(diff).count());
            int index_of_dot = time.find('.');
            time = time.substr(0, index_of_dot + 3);
            print("\nTime spending: " + time + " s", color_cyan, color_black);
            result = "LOST";
            save_data(player_name, time, result, file_name, date);
            break;
        }
        q = getch();
        clean();
        if ((int)q == 72 && current_row - 1 >= 0 && !is_on_the_path(path, current_row - 1, current_column, length) && (maze_map_numbers[current_row - 1][current_column] != 0 || (current_row - 1 == number_of_rows - 1 && current_column == number_of_columns - 1)))
        {
            path[i][0] = current_row;
            path[i][1] = current_column;
            current_row = current_row - 1;
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
            i++;
        }
        else if ((int)q == 80 && (current_row + 1) < number_of_rows && !is_on_the_path(path, current_row + 1, current_column, length) && (maze_map_numbers[current_row + 1][current_column] != 0 || (current_row + 1 == number_of_rows - 1 && current_column == number_of_columns - 1)))
        {
            path[i][0] = current_row;
            path[i][1] = current_column;
            current_row = current_row + 1;
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
            i++;
        }
        else if ((int)q == 77 && current_column + 1 < number_of_columns && !is_on_the_path(path, current_row, current_column + 1, length) && (maze_map_numbers[current_row][current_column + 1] != 0 || (current_row == number_of_rows - 1 && current_column + 1 == number_of_columns - 1)))
        {
            path[i][0] = current_row;
            path[i][1] = current_column;
            current_column = current_column + 1;
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
            i++;
        }
        else if ((int)q == 75 && current_column - 1 >= 0 && !is_on_the_path(path, current_row, current_column - 1, length) && (maze_map_numbers[current_row][current_column - 1] != 0 || (current_row == number_of_rows - 1 && current_column - 1 == number_of_columns - 1)))
        {
            path[i][0] = current_row;
            path[i][1] = current_column;
            current_column = current_column - 1;
            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            sum_of_numbers_on_path += maze_map_numbers[current_row][current_column];
            i++;
        }
        else
        {

            map_output(number_of_rows, number_of_columns, maze_map_numbers, current_row, current_column, path, length);
            print("\nInvalid move!!\nPlease try again", color_red, color_black);
        }
        if ((current_row == number_of_rows - 1 && current_column == number_of_columns - 1) || (i == length))
        {
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            if (i == length && (float)sum_of_numbers_on_path / 2.0 == maze_map_numbers[number_of_rows - 1][number_of_columns - 1])
            {
                cout << "\n";
                print("YOU WON!!", color_green, color_black);
                print("\nYour sum : " + to_string(sum_of_numbers_on_path - maze_map_numbers[number_of_rows - 1][number_of_columns - 1]), color_cyan, color_black);
                print("\nYour path length : " + to_string(i), color_cyan, color_black);
                print("\nTarget path length : " + to_string(length), color_cyan, color_black);
                result = "WON";
            }
            else
            {
                print("\nYOU LOST!!", color_red, color_black);
                print("\nYour sum : " + to_string(sum_of_numbers_on_path - maze_map_numbers[number_of_rows - 1][number_of_columns - 1]), color_cyan, color_black);
                print("\nYour path length : " + to_string(i), color_cyan, color_black);
                print("\nTarget path length : " + to_string(length), color_cyan, color_black);
                result = "LOST";
            }

            time = to_string(chrono::duration<double>(diff).count());
            int index_of_dot = time.find('.');
            time = time.substr(0, index_of_dot + 3);
            print("\nTime spending: " + time + " s", color_cyan, color_black);

            save_data(player_name, time, result, file_name, date);
            break;
        }
    }
    print("\n\nPress any key to continue", color_orange, color_black);

    q = getch();
}

/// <summary>this function returns 1 if that position is on the path.</summary>
bool is_on_the_path(int **path, int current_row, int current_column, int length)
{

    for (size_t current_path_length = 0; current_path_length < length; current_path_length++)
    {
        if (path[current_path_length][0] == current_row && path[current_path_length][1] == current_column)
        {
            return 1;
        }
    }
    return 0;
}

/// <summary>this function creates array with contains values.</summary>
bool make_maze(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns, int **maze_map_numbers, int max_value, int min_value, int maxb, int minb)
{
    srand(time(0));
    int random_number = 0;
    int sum_of_numbers_on_path = 0;
    while (random_number == 0)
    {
        if (min_value != max_value)
        {
            random_number = rand() % (max_value - min_value + 1) + min_value;
        }
        else
        {
            random_number = min_value;
        }
    }
    maze_map_numbers[0][0] = random_number;
    sum_of_numbers_on_path += random_number;

    for (size_t i = 0; i < length; i++)
    {
        path[i][0] = number_of_rows;
        path[i][1] = number_of_columns;
    }
inja:
    current_row = 0;
    current_column = 0;
    int left_move_counter = 0, right_move_counter = number_of_columns - 1, up_move_counter = 0, down_move_counter = number_of_rows - 1;
    int ezafe = (length - (number_of_rows + number_of_columns - 2)) / 2;
    for (int i = 0; i < ezafe; i++)
    {
        int najafi = rand() % 2;
        if (najafi % 2 == 0)
        {
            down_move_counter++;
            up_move_counter++;
        }
        if (najafi % 2 == 1)
        {
            left_move_counter++;
            right_move_counter++;
        }
    }

    for (size_t i = 0; i < length; i++)
    {
        path[i][0] = 0;
        path[i][1] = 0;
    }
    int current_path_length = 0;

    while (true)
    {
        int najafi = rand() % 4;
        random_number = 0;
        if (najafi == 0 && up_move_counter > 0 && current_row - 1 >= 0 && !is_on_the_path(path, current_row - 1, current_column, length))
        {
            current_row = current_row - 1;
            path[current_path_length][0] = current_row;
            path[current_path_length][1] = current_column;

            up_move_counter--;
            current_path_length++;
        }
        else if (najafi == 1 && right_move_counter > 0 && current_column + 1 < number_of_columns && !is_on_the_path(path, current_row, current_column + 1, length))
        {

            current_column = current_column + 1;
            path[current_path_length][0] = current_row;
            path[current_path_length][1] = current_column;

            right_move_counter--;
            current_path_length++;
        }
        else if (najafi == 2 && down_move_counter > 0 && current_row + 1 < number_of_rows && !is_on_the_path(path, current_row + 1, current_column, length))
        {
            current_row = current_row + 1;
            path[current_path_length][0] = current_row;
            path[current_path_length][1] = current_column;

            down_move_counter--;
            current_path_length++;
        }
        else if (najafi == 3 && left_move_counter > 0 && current_column - 1 >= 0 && !is_on_the_path(path, current_row, current_column - 1, length))
        {
            current_column = current_column - 1;
            path[current_path_length][0] = current_row;
            path[current_path_length][1] = current_column;
            left_move_counter--;
            current_path_length++;
        }
        if (current_path_length == length)
        {
            break;
        }
        if (is_path_unvalid(path, current_row, current_column, length, number_of_rows, number_of_columns, up_move_counter, right_move_counter, down_move_counter, left_move_counter))
        {
            goto inja;
        }
    }
    for (size_t i = 0; i < length - 1; i++)
    {
        random_number = 0;
        while (random_number == 0)
        {
            if (min_value != max_value)
            {
                random_number = rand() % (max_value - min_value + 1) + min_value;
            }
            else
            {
                random_number = min_value;
            }
        }

        maze_map_numbers[path[i][0]][path[i][1]] = random_number;
        sum_of_numbers_on_path += random_number;
    }
    maze_map_numbers[number_of_rows - 1][number_of_columns - 1] = sum_of_numbers_on_path;
    for (size_t i = 0; i < number_of_rows; i++)
    {
        for (size_t j = 0; j < number_of_columns; j++)
        {
            if (!is_on_the_path(path, i, j, length) && (i != 0 || j != 0))
            {
                random_number = 0;
                while (random_number == 0)
                {
                    if (min_value != max_value)
                    {
                        random_number = rand() % (max_value - min_value + 1) + min_value;
                    }
                    else
                    {
                        random_number = min_value;
                    }
                }

                maze_map_numbers[i][j] = random_number;
            }
        }
    }

    random_number = -1;
    while (random_number == -1)
    {
        if (minb != maxb)
        {
            random_number = rand() % (maxb - minb + 1) + minb;
        }
        else
        {
            random_number = minb;
        }

        if (random_number + length + 1 > number_of_rows * number_of_columns)
        {
            random_number = -1;
        }
    }
    int number_of_blocks = random_number, random_number_2;
    for (size_t i = 0; i < number_of_blocks;)
    {
        random_number = rand() % number_of_rows;
        random_number_2 = rand() % number_of_columns;
        if (!is_on_the_path(path, random_number, random_number_2, length) && (random_number != 0 || random_number_2 != 0) && maze_map_numbers[random_number][random_number_2] != 0)
        {
            maze_map_numbers[random_number][random_number_2] = 0;
            i++;
        }
    }

    return 1;
}

/// <summary>this function returns 1 if path is not valid.</summary>
bool is_path_unvalid(int **path, int current_row, int current_column, int length, int number_of_rows, int number_of_columns, int up_move_counter, int right_move_counter, int down_move_counter, int left_move_counter)
{
    if ((is_on_the_path(path, current_row + 1, current_column, length) || current_row + 1 >= number_of_rows || down_move_counter == 0) && (is_on_the_path(path, current_row - 1, current_column, length) || current_row - 1 < 0 || up_move_counter == 0) && (is_on_the_path(path, current_row, current_column + 1, length) || current_column + 1 >= number_of_columns || right_move_counter == 0) && (is_on_the_path(path, current_row, current_column - 1, length) || current_column - 1 < 0 || left_move_counter == 0))
    {
        return 1;
    }
    return 0;
}

/// <summary>this function outputs menu with different color.</summary>
void output_menu_list(int n)
{
    print("1. ", color_red, color_black);
    cout << "Create a new map\n";
    print("  -1.1 ", color_red, color_black);
    if (n == 1)
    {
        print("  Easy\n", color_green, color_black);
    }
    else
    {
        print("  Easy\n", color_white, color_black);
    }
    print("  -1.2 ", color_red, color_black);
    if (n == 2)
    {
        print("  Hard\n", color_green, color_black);
    }
    else
    {
        print("  Hard\n", color_white, color_black);
    }
    print("2. ", color_red, color_black);
    cout << "Playground\n";
    print("  -2.1 ", color_red, color_black);
    if (n == 3)
    {
        print("  Choose from existing maps\n", color_green, color_black);
    }
    else
    {
        print("  Choose from existing maps\n", color_white, color_black);
    }
    print("  -2.2 ", color_red, color_black);
    if (n == 4)
    {
        print("  Import a custom map\n", color_green, color_black);
    }
    else
    {
        print("  Import a custom map\n", color_white, color_black);
    }
    print("3. ", color_red, color_black);
    cout << "Solve a maze\n";
    print("  -3.1 ", color_red, color_black);
    if (n == 5)
    {
        print("  Choose from existing maps\n", color_green, color_black);
    }
    else
    {
        print("  Choose from existing maps\n", color_white, color_black);
    }
    print("  -3.2 ", color_red, color_black);
    if (n == 6)
    {
        print("  Import a custom map\n", color_green, color_black);
    }
    else
    {
        print("  Import a custom map\n", color_white, color_black);
    }
    print("4. ", color_red, color_black);
    if (n == 7)
    {
        print("History\n", color_green, color_black);
    }
    else
    {
        print("History\n", color_white, color_black);
    }
    print("5. ", color_red, color_black);
    if (n == 8)
    {
        print("Leaderboard\n", color_green, color_black);
    }
    else
    {
        print("Leaderboard\n", color_white, color_black);
    }
    print("6. ", color_red, color_black);
    if (n == 9)
    {
        print("Exit\n", color_green, color_black);
    }
    else
    {
        print("Exit\n", color_white, color_black);
    }
}

/// <summary>player can select map here.</summary>
void select_map(string function)
{
    int index;
    string s;
    string path = find_address() + (char)92 + (char)92 + "Maps";
    int i = 0;
    while (i != maps_in_folder.size())
    {
        maps_in_folder.pop_back();
    }

    struct stat sb;
    maps_in_folder.push_back(make_pair(0, "Back to menu"));
    int iii = 1;
    for (const auto &entry : fs::directory_iterator(path))
    {
        iii++;
        filesystem::path outfilename = entry.path();
        string outfilename_str = outfilename.string();
        const char *path = outfilename_str.c_str();
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            index = outfilename_str.find("Maps");
            s = outfilename_str.substr(index + 5);
            maps_in_folder.push_back(make_pair(iii, s));
        }
    }
    i = 0;
    output_maps_list(0);
    char q = 'm';

    while ((int)q != 13)
    {
        q = getch();
        if ((int)q == 72 && i - 1 >= 0)
        {
            i--;
        }
        else if ((int)q == 80 && (i + 1) < iii)
        {
            i++;
        }

        clean();

        output_maps_list(i);
    }
    if (maps_in_folder[i].second == "Back to menu")
    {
        return;
    }

    string f = "";
    f = "Maps";
    f = f + (char)92;
    f = f + maps_in_folder[i].second;
    clean();
    if (function == "find")
    {
        make_maze_from_file(f, "find");
    }
    if (function == "play")
    {
        make_maze_from_file(f, "play");
    }
}

/// <summary>this function outputs maps list.</summary>
void output_maps_list(int i)
{
    int ii = 0;
    while (ii != maps_in_folder.size())
    {
        if (i == ii)
        {
            print(maps_in_folder[ii].second, color_green, color_black);
            cout << "\n";
        }
        else
        {
            cout << maps_in_folder[ii].second << "\n";
        }
        ii++;
    }
}