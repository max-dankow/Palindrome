#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

std::string restore_way_back(std::vector<std::vector<std::pair<long long,long long> > > way,
                             long long sx, long long sy, std::string str)
{
    std::string palindrome = "";
    std::string middle = "";
    while (sx != -1 && sy != -1)
    {
        long long new_x = way[sx][sy].first;
        long long new_y = way[sx][sy].second;

        if ((new_x + 1 == sx && new_y - 1 == sy) ||
            (new_x ==  -1 && new_y == -1))
        {
            if (sx != sy)
            {
                palindrome = palindrome + str[sx];
            }
            else
            {
                middle = str[sx];
            }
        }

        sx = new_x;
        sy = new_y;
    }

    std::string reverse_str = palindrome;
    std::reverse(reverse_str.begin(), reverse_str.end());
    palindrome = palindrome + middle + reverse_str;

    return palindrome;
}

std::string get_max_palindrome(std::string input)
{
    long long len = input.size();
    std::vector<std::vector<long long> > max_palindrome (len, std::vector<long long>(len, 0));

    std::vector<std::vector<std::pair<long long,long long> > >
            back_way (len, std::vector<std::pair<long long,long long> >(len, std::make_pair(0, 0)));

    //print_table(max_palindrome);
    for (int i = 0; i < len; ++i)
    {
        max_palindrome[i][i] = 1;
        back_way[i][i] = std::make_pair(-1, -1);
    }

    //print_table(max_palindrome);

    for (int j = 0; j + 1 < len; ++j)
    {
        if (input[j] == input[j + 1])
        {
            max_palindrome[1 + j][j] = 2;
            back_way[1 + j][j] = std::make_pair(-1, -1);
        }
        else
        {
            max_palindrome[1 + j][j] = 1;
            back_way[1 + j][j] = std::make_pair(j, j);
        }
    }

    //print_table(max_palindrome);

    for (int i = 2; i < len; ++i)
    {
        for (int j = 0; j + i < len; ++j)
        {
            if (input[i + j] == input[j])
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
            //print_table(max_palindrome);
        }
    }

    //print_table(max_palindrome);
    return restore_way_back(back_way, len - 1, 0, input);
}

int main()
{

    std::string in_str;
    std::cin >> in_str;
    std::string answer = get_max_palindrome(in_str);
    std::cout << answer.size() << '\n' << answer << '\n';
    return 0;
}

