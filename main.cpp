#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TOTAL_ITERATIONS 100000000UL

typedef unsigned long ulong;

void performFloatingPointCalculation() {
    volatile double result = 0.0;
    for (ulong i = 0; i < TOTAL_ITERATIONS; ++i) {
        result += sqrt((double) i);
    }
}

void performIntegerCalculation() {
    volatile ulong result = 0;
    for (ulong i = 0; i < TOTAL_ITERATIONS; ++i) {
        result += i;
    }
}

void performMemoryAccessTest() {
    volatile ulong sum = 0;
    for (ulong i = 0; i < TOTAL_ITERATIONS; ++i) {
        sum += i;
    }
}

void performCachePerformanceTest() {
    volatile ulong sum = 0;
    for (ulong i = 0; i < TOTAL_ITERATIONS; ++i) {
        sum += i % 1000;
    }
}

double measurePerformance(void (*testFunction)(), ulong runs) {
    double totalTime = 0.0;

    for (ulong run = 0; run < runs; ++run) {
        clock_t start = clock();
        testFunction();
        clock_t end = clock();

        totalTime += (double) (end - start) / CLOCKS_PER_SEC;
    }

    return totalTime / runs;
}

double calculateScore(double time) {
    return (time > 0) ? 100.0 / time : 100.0;
}

int main() {
    ulong runs;

    printf("CPU Benchmark\n");
    printf("Enter number of test runs: ");
    scanf("%lu", &runs);

    printf("\nStarting Benchmark Tests...\n");

    double fpTime = measurePerformance(performFloatingPointCalculation, runs);
    double fpScore = calculateScore(fpTime);
    printf("Floating Point Test - Avg Time: %.3f sec, Score: %.2f\n", fpTime, fpScore);

    double intTime = measurePerformance(performIntegerCalculation, runs);
    double intScore = calculateScore(intTime);
    printf("Integer Calculation Test - Avg Time: %.3f sec, Score: %.2f\n", intTime, intScore);

    double memTime = measurePerformance(performMemoryAccessTest, runs);
    double memScore = calculateScore(memTime);
    printf("Memory Access Test - Avg Time: %.3f sec, Score: %.2f\n", memTime, memScore);

    double cacheTime = measurePerformance(performCachePerformanceTest, runs);
    double cacheScore = calculateScore(cacheTime);
    printf("Cache Performance Test - Avg Time: %.3f sec, Score: %.2f\n", cacheTime, cacheScore);

    double averageScore = (fpScore + intScore + memScore + cacheScore) / 4.0;
    printf("\nOverall Performance Score: %.2f\n", averageScore);

    return 0;
}