using namespace std;

#define MAX_SIZE 10

void sortByRow(int mat[][MAX_SIZE], int n, bool ascending)
{
    for (int i = 0; i < n; i++)
    {
        if (ascending)
            sort(mat[i], mat[i] + n);
        else
            sort(mat[i], mat[i] + n, greater<int>());
    }
}

void transpose(int mat[][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)

            swap(mat[i][j], mat[j][i]);
}

void sortMatRowAndColWise(int mat[][MAX_SIZE], int n)
{
    sortByRow(mat, n, true);

    transpose(mat, n);

    sortByRow(mat, n, false);

    transpose(mat, n);
}

void printMat(int mat[][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    int n = 3;

    int mat[n][MAX_SIZE] = {{3, 2, 1},
                            {9, 8, 7},
                            {6, 5, 4}};

    cout << "Original Matrix:\n";
    printMat(mat, n);

    sortMatRowAndColWise(mat, n);

    cout << "\nMatrix After Sorting:\n";
    printMat(mat, n);

    return 0;
}