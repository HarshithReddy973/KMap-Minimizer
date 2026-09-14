#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int kmap[32], ones[32], n1;
int vars, rows, cols;

int groups[100][32], gsize[100], ng;
int selected[100];
int solutions[100][100], solCount[100], totalSolutions;
int bestCount = 100;

int gray(int x)
{
    return x ^ (x >> 1);
}

int getMinterm(int r, int c)
{
    int rb = vars / 2;
    int cb = vars - rb;
    return (gray(r) << cb) | gray(c);
}

bool isOne(int m)
{
    for (int i = 0; i < n1; i++)
        if (ones[i] == m)
            return true;
    return false;
}

bool alreadyGroup(int g[], int size)
{
    for (int i = 0; i < ng; i++)
    {
        if (gsize[i] != size)
            continue;

        bool same = true;

        for (int j = 0; j < size; j++)
        {
            bool found = false;

            for (int k = 0; k < size; k++)
                if (groups[i][k] == g[j])
                    found = true;

            if (!found)
                same = false;
        }

        if (same)
            return true;
    }

    return false;
}

void makeGroup(int r, int c, int h, int w)
{
    if (h > rows || w > cols)
        return;

    int g[32], size = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int rr = (r + i) % rows;
            int cc = (c + j) % cols;
            int m = getMinterm(rr, cc);

            if (!isOne(m))
                return;

            g[size++] = m;
        }
    }

    if (!alreadyGroup(g, size))
    {
        for (int i = 0; i < size; i++)
            groups[ng][i] = g[i];

        gsize[ng] = size;
        ng++;
    }
}

void generateGroups()
{
    int sizes[] = {1, 2, 4, 8, 16};

    for (int s = 0; s < 5; s++)
    {
        int size = sizes[s];

        for (int h = 1; h <= rows; h++)
        {
            if (size % h != 0)
                continue;

            int w = size / h;

            if (w > cols)
                continue;

            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    makeGroup(r, c, h, w);
        }
    }
}

bool contains(int g, int m)
{
    for (int i = 0; i < gsize[g]; i++)
        if (groups[g][i] == m)
            return true;

    return false;
}

void findSolutions(int pos, int count)
{
    if (count > bestCount)
        return;

    bool all = true;

    for (int i = 0; i < n1; i++)
    {
        bool covered = false;

        for (int j = 0; j < count; j++)
        {
            if (contains(selected[j], ones[i]))
            {
                covered = true;
                break;
            }
        }

        if (!covered)
        {
            all = false;
            break;
        }
    }

    if (all)
    {
        if (count < bestCount)
        {
            bestCount = count;
            totalSolutions = 0;
        }

        if (count == bestCount)
        {
            for (int i = 0; i < count; i++)
                solutions[totalSolutions][i] = selected[i];

            solCount[totalSolutions] = count;
            totalSolutions++;
        }

        return;
    }

    for (int i = pos; i < ng; i++)
    {
        selected[count] = i;
        findSolutions(i + 1, count + 1);
    }
}

void printTerm(int g)
{
    int common[5];

    for (int i = 0; i < vars; i++)
        common[i] =
            (groups[g][0] >> (vars - 1 - i)) & 1;

    for (int j = 1; j < gsize[g]; j++)
    {
        for (int i = 0; i < vars; i++)
        {
            int bit =
                (groups[g][j] >> (vars - 1 - i)) & 1;

            if (bit != common[i])
                common[i] = -1;
        }
    }

    for (int i = 0; i < vars; i++)
    {
        if (common[i] == 0)
            cout << char('a' + i) << "'";
        else if (common[i] == 1)
            cout << char('a' + i);
    }
}

int main()
{
    ifstream file("kmap.txt");

    if (!file)
    {
        cout << "File not found\n";
        return 0;
    }

    int x, total = 0;

    while (file >> x)
        kmap[total++] = x;

    if (total != 4 && total != 8 &&
        total != 16 && total != 32)
    {
        cout << "Invalid K-map\n";
        return 0;
    }

    vars = log2(total);

    if (vars == 2)
        rows = 2, cols = 2;
    else if (vars == 3)
        rows = 2, cols = 4;
    else if (vars == 4)
        rows = 4, cols = 4;
    else
        rows = 4, cols = 8;

    int p = 0;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (kmap[p] == 1)
                ones[n1++] = getMinterm(r, c);

            p++;
        }
    }

    cout << "Variables = " << vars << "\n";

    cout << "Minterms = ";
    for (int i = 0; i < n1; i++)
        cout << ones[i] << " ";

    cout << "\n\n";

    generateGroups();
    findSolutions(0, 0);

    cout << "Minimum number of groups = "
         << bestCount << "\n\n";

    cout << "All minimum expressions:\n";

    for (int s = 0; s < totalSolutions; s++)
    {
        cout << s + 1 << ". ";

        for (int i = 0; i < solCount[s]; i++)
        {
            if (i)
                cout << " + ";

            printTerm(solutions[s][i]);
        }

        cout << "\n";
    }

    return 0;
}
