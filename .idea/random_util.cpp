#include "random_util.h"

namespace random_util {
    std::random_device rd;
    std::mt19937 gen(rd());

}