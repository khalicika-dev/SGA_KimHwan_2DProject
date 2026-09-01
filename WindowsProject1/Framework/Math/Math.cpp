#include "Framework.h"
#include "Math.h"

int Math::Random(const int& min, const int& max)
{
    int result = rand() % (max - min) + min;

    return result;
}

UINT Math::Random(const UINT& min, const UINT& max)
{
    UINT result = rand() % (max - min) + min;

    return result;
}

float Math::Random(const float& min, const float& max)
{
    float normal = rand() / (float)RAND_MAX;
    // 0.0f < normal < 1.0f

    return normal * (max - min) + min;
}
