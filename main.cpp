#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<std::pair<long long,long long> > > Way;
static const long long WAY_END = -1;

void print_table(std::vector<std::vector<long long> > table)
{
    for (int i = 0; i < table.size(); ++i)
    {
        for (int j = 0; j < table[i].size(); ++j)
        {
            std::cout << ' ';
            std::cout.width(4);
            std::cout << table[i][j];
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}

std::string restore_way_back(Way way, long long row, long long column, std::string str)
{
    std::string prefix;
    std::string middle;

    while (row != WAY_END && column != WAY_END)
    {
        long long new_row = way[row][column].first;
        long long new_col = way[row][column].second;

        if ((new_row + 1 == row && new_col - 1 == column) ||
            (new_row ==  WAY_END && new_col == WAY_END))
        {
            if (row != column)
            {
                prefix = prefix + str[row];
            }
            else
            {
                middle = str[row];
            }
        }

        row = new_row;
        column = new_col;
    }

    std::string suffix = prefix;
    std::reverse(suffix.begin(), suffix.end());

    return prefix + middle + suffix;
}

std::string get_max_palindrome(std::string input_str)
{
    long long len = input_str.size();
    std::vector<std::vector<long long> >
            max_palindrome(len, std::vector<long long>(len, 0));

    Way back_way(len, std::vector<std::pair<long long,long long> >
                      (len, std::make_pair(0, 0)));

    for (int i = 0; i < len; ++i)
    {
        max_palindrome[i][i] = 1;
        back_way[i][i] = std::make_pair(WAY_END, WAY_END);
    }

    for (int j = 0; j + 1 < len; ++j)
    {
        if (input_str[j] == input_str[j + 1])
        {
            max_palindrome[1 + j][j] = 2;
            back_way[1 + j][j] = std::make_pair(WAY_END, WAY_END);
        }
        else
        {
            max_palindrome[1 + j][j] = 1;
            back_way[1 + j][j] = std::make_pair(j, j);
        }
    }

    for (int i = 2; i < len; ++i)
    {
        for (int j = 0; j + i < len; ++j)
        {
            if (input_str[i + j] == input_str[j])
            {
                max_palindrome[i + j][j] = max_palindrome[i + j - 1][j + 1] + 2;
                back_way[i + j][j] = std::make_pair(i + j - 1, j + 1);
            }
            else
            {
                max_palindrome[i + j][j] = max_palindrome[i + j - 1][j];
                back_way[i + j][j] = std::make_pair(i + j - 1, j);

                if (max_palindrome[i + j][j] < max_palindrome[i + j][j + 1])
                {
                    max_palindrome[i + j][j] = max_palindrome[i + j][j + 1];
                    back_way[i + j][j] = std::make_pair(i + j, j + 1);
                }
            }
        }
    }

    return restore_way_back(back_way, len - 1, 0, input_str);
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::string in_str;
    std::cin >> in_str;

    std::string answer = get_max_palindrome(in_str);
    std::cout << answer.size() << '\n' << answer << '\n';

    return 0;
}

