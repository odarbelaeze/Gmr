#include <iostream>

typedef void (*CALLBACK) (float, float);

void defaultCallback (float a, float b)
{
    std::cout << a * b << std::endl;
}

void otherCallback (float a, float b)
{
    std::cout << a + b << std::endl;
}

struct TalCosa
{
    float a;
    float b;
    CALLBACK cb;
};

int main(int argc, char const *argv[])
{
    TalCosa tc;
    tc.cb = defaultCallback;
    tc.cb(5,3);
    tc.cb = otherCallback;
    tc.cb(5,3);
    return 0;
}