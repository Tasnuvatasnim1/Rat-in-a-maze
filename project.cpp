#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int di[] = {1, 0, 0, -1};
int dj[] = {0, -1, 1, 0};

int pos_way = 0;
int maze[1000][1000];
bool vis[1000][1000];

vector<string> ans;

void solve(int i, int j, int n, string move)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (i == n - 1 && j == n - 1)
    {
        // Simulation Display
        pos_way++;
        cout << "----------------------------\n";
        cout << "Path " << pos_way << " : \n";
        SetConsoleTextAttribute(h, 185);
        cout << "\t" << move;
        SetConsoleTextAttribute(h, 240);
        cout << '\n';
        for (int i1 = 0; i1 < n; i1++)
        {
            cout << "\t";
            for (int j1 = 0; j1 < n; j1++)
            {
                if (maze[i1][j1] == 0)
                {
                    SetConsoleTextAttribute(h, 271);
                    cout << " 0 ";
                }
                else
                {
                    if (i1 == n - 1 && j1 == n - 1)
                    {
                        SetConsoleTextAttribute(h, 47);
                        cout << " 1 ";
                        continue;
                    }
                    if (vis[i1][j1])
                    {
                        SetConsoleTextAttribute(h, 207);
                        cout << " 1 ";
                    }
                    else
                    {
                        SetConsoleTextAttribute(h, 240);
                        cout << " 1 ";
                    }
                }
            }
            SetConsoleTextAttribute(h, 240);
            cout << '\n';
        }
        cout << "----------------------------\n";
        cout << '\n';
        // End

        ans.push_back(move);
        return;
    }
    string dir = "DLRU";
    for (int ind = 0; ind < 4; ind++)
    {
        int nexti = i + di[ind];
        int nextj = j + dj[ind];
        if (nexti >= 0 && nextj >= 0 && nexti < n && nextj < n && !vis[nexti][nextj] && maze[nexti][nextj] == 1)
        {
            vis[i][j] = 1;

            // Simulation Display
            SetConsoleTextAttribute(h, 185);
            cout << "\t" << move;
            SetConsoleTextAttribute(h, 240);
            cout << '\n';
            for (int i1 = 0; i1 < n; i1++)
            {
                cout << "\t";
                for (int j1 = 0; j1 < n; j1++)
                {
                    if (maze[i1][j1] == 0)
                    {
                        SetConsoleTextAttribute(h, 271);
                        cout << " 0 ";
                    }
                    else
                    {
                        if (vis[i1][j1])
                        {
                            if (i1 == i && j1 == j)
                            {
                                SetConsoleTextAttribute(h, 47);
                                cout << " 1 ";
                            }
                            else
                            {
                                SetConsoleTextAttribute(h, 207);
                                cout << " 1 ";
                            }
                        }
                        else
                        {
                            SetConsoleTextAttribute(h, 240);
                            cout << " 1 ";
                        }
                    }
                }
                SetConsoleTextAttribute(h, 240);
                cout << '\n';
            }
            cout << '\n';
            // End

            solve(nexti, nextj, n, move + dir[ind]);
            vis[i][j] = 0;
        }
    }
}

int main()
{
    system("color f0");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n;
    cout << "Enter the Maze Size (N) : ";
    cin >> n;
    cout << '\n';
    cout << "Enter '0' or '1' to the Cell. ( '1' = Usable Block, '0' = Dead End )\n\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            while (1)
            {
                bool flag = 0;
                string temp;
                cout << "( " << i + 1 << ", " << j + 1 << " ) Cell : ";
                cin >> temp;
                for (int k = 0; k < temp.size(); k++)
                {
                    if (!isdigit(temp[k]))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                {
                    cout << "Invalid Input! Enter the Correct Value.\n\n";
                }
                else
                {
                    int num = stoi(temp);
                    if (num == 0 || num == 1)
                    {
                        maze[i][j] = num;
                        break;
                    }
                    else
                    {
                        cout << "Invalid Input! Enter the Correct Value.\n\n";
                    }
                }
            }
        }
    }

    // Simulation Start
    cout << '\n';
    cout << "● For Simulation Purpose: \n\n";
    SetConsoleTextAttribute(h, 47);
    cout << "\t 1 ";
    SetConsoleTextAttribute(h, 240);
    cout << " = Current Position of Rat\n\n";

    SetConsoleTextAttribute(h, 207);
    cout << "\t 1 ";
    SetConsoleTextAttribute(h, 240);
    cout << " = Visited Position of Rat\n\n";

    SetConsoleTextAttribute(h, 271);
    cout << "\t 0 ";
    SetConsoleTextAttribute(h, 240);
    cout << " = Dead End Position\n\n\n";

    cout << "The Maze Layout : \n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\t";
        for (int j = 0; j < n; j++)
        {
            if (maze[i][j] == 0)
            {
                SetConsoleTextAttribute(h, 271);
                cout << " 0 ";
            }
            else
            {
                SetConsoleTextAttribute(h, 240);
                cout << " 1 ";
            }
            SetConsoleTextAttribute(h, 240);
        }
        cout << '\n';
    }
    cout << '\n';
    // End

    if (maze[0][0] == 1)
    {
        cout << "Simulation Starts !\n\n";
        solve(0, 0, n, "");
    }
    if (ans.size() == 0)
    {
        cout << "There is No Path Between Source to Destination.\n";
    }
    else
    {
        cout << "Total Path from Source to Destination = " << ans.size() << '\n';
    }

    return 0;
}
