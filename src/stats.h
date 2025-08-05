#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct Stats {
    float min;
    float max;
    float average;
};

struct Stats compute_statistics(const float* numbers, int count);

#ifdef __cplusplus
}
#endif
