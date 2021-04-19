#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point {
    double X;
    double Y;

    double IsVisited;
};

double getDistance(struct Point a, struct Point b);
struct Point* getPoints(int n);
int* findRoad(int n, struct Point* points);
void drawRoad(int n, struct Point* points, int* road);

int main()
{
    int n;
    srand((unsigned int)time(NULL));

    printf("Enter the number of points you want to draw: ");
    while (scanf_s("%d", &n) != 1) //dopóki nie uda się wczytać
    {
        printf("Error! Enter the number of points you want to draw:");
        scanf_s("%d", &n);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //pętla wyciągająca znaki z bufora
    }
    while (n < 1) {
        printf("Error! Enter the number of points you want to draw:");
        scanf_s("%d", &n);
    }

    struct Point* points = getPoints(n);
    int* road = findRoad(n, points);

    drawRoad(n, points, road);
    return 0;
}

double getDistance(struct Point a, struct Point b)
{
    return sqrt(0
        + pow(b.X - a.X, 2.0)
        + pow(b.Y - a.Y, 2.0));
}

struct Point* getPoints(int n)
{
    struct Point* result = (struct Point*)malloc(n * sizeof(struct Point));

    if (n > 0)
    {
        result[0].X = (double)(rand() % 1000) + 1;
        result[0].Y = (double)(rand() % 1000) + 1;
    }

    for (int i = 1; i < n; i++)
    {
        int tryAgain;
        double x, y;

        do
        {
            tryAgain = 0;

            x = (double)(rand() % 1000) + 1;
            y = (double)(rand() % 1000) + 1;

            for (int j = 0; j < i; j++)
            {
                if (result[j].X == x && result[j].Y == y)
                {
                    tryAgain = 1;
                    break;
                }
            }
        } while (tryAgain > 0);

        result[i].X = x;
        result[i].Y = y;
    }

    return result;
}

void drawRoad(int n, struct Point* points, int* road)
{
    for (int i = 0; i < n; i++)
    {
        struct Point point = points[road[i]];
        printf("%d:[%.2f, %.2f]\n", i + 1, point.X, point.Y);
    }
}

int* findRoad(int n, struct Point* points)
{
    int* road = (int*)malloc(n * sizeof(int));

    int firstPointIndex = 0;

    road[firstPointIndex] = 0;
    points[0].IsVisited = 1;

    int index = 0;
    for (int counter = 1; counter < n; counter++)
    {
        double minDistance = 1000000.0;

        for (int j = 0; j < n; j++)
        {
            if (index == j) continue;

            double distance = getDistance(points[index], points[j]);

            if (points[j].IsVisited != 1 && distance < minDistance)
            {
                minDistance = distance;
                index = j;
            }
        }

        road[counter] = index;
        points[index].IsVisited = 1;
    }

    return road;
}
