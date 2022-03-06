#include <cassert>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main(void) {
    assert(max(1, 0) == 1);
}