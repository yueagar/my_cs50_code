#include <stdio.h>

const int N = 3;

float average(int length, int array[]);

int main(void) {
    /* int score1 = 72;
    int score2 = 73;
    int score3 = 33; */
    int scores[N];

    /*scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;*/
    for (int i = 0; i < N; i++)
    {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    };

    // printf("Average: %d", (score1 + score2 + score3) / 3);
    // printf("Average: %f", (score1 + score2 + score3) / 3.0);
    // printf("Average: %f", (score1 + score2 + score3) / (float) 3);
    // printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) 3);
    printf("Average: %f\n", average(N, scores));
};

float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    };
    return sum / (float) length;
};