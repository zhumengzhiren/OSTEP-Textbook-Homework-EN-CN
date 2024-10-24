#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    struct timespec start, end;
    long long duration;
    int iterations = 1000000;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterations; i++) {
        // 空的系统调用，例如读取0字节
        read(0, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Average system call cost: %lld nanoseconds\n", duration / iterations);

    return 0;
}