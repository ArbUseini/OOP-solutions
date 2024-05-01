#include <stdio.h>
#include <string.h>
#define WEEKS 4
#define DAYS 5

/*



It's in C not C++ because of the compiler



*/




struct WorkingWeek{
    int hours[DAYS];
    int week;
};

typedef struct WorkingWeek WW;

struct Worker{
    char name[51];
    WW weeks[WEEKS];
};

typedef struct Worker W;

int calc(WW w){
    int sum = 0;
    for (int i = 0; i < DAYS; i++){
        sum += w.hours[i];
    }
    return sum;
}

int maxWeek(W *w){
    int max = 0;
    int idx = 0;
    for (int i = 0; i < WEEKS; i++){
        int sum = calc(w->weeks[i]);
        if (sum > max){
            max = sum;
            idx = i;
        }
    }
    return idx + 1;
}

void table(W *w, int n){
    printf("Wor\\t1\\t2\\t3\\t4\\tTotal\n");
    for (int i = 0; i < n; i++){
        printf("%s", w[i].name);
        int sum = 0;
        for (int j = 0; j < WEEKS; j++){
            printf("\\t%d", calc(w[i].weeks[j]));
            sum += calc(w[i].weeks[j]);
        }
        printf("\\t%d\n", sum);
    }
}


int main() {
    int n;
    scanf("%d", &n);
    W workers[100];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", workers[i].name);
        int j;
        for (j = 0; j < WEEKS; ++j) {
            int k;
            for (k = 0; k < DAYS; ++k) {
                scanf("%d", &workers[i].weeks[j].hours[k]);
            }

        }
    }
    printf("TABLE\n");
    table(workers, n);
    printf("MAX WEEK OF WORKER: %s\n", workers[n / 2].name);
    printf("%d\n", maxWeek(&workers[n / 2]));
    return 0;
}
