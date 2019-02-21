#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<double> increments{{10, 5, 4, 5, 7, 10, 10, 7}};
    std::vector<double> timestamps{{1, 2, 3, 4, 5, 6, 7, 8}};

    std::vector<double> delta_ts;
    std::adjacent_difference(begin(timestamps), end(timestamps), back_inserter(delta_ts));

    std::vector<double> speeds;
    std::transform(
        begin(increments), end(increments),
        begin(delta_ts),
        back_inserter(speeds),
        [](auto dx, auto dt) { return dx/dt;});
    
    std::vector<double> forces{{1, .15, .2, .2, .1, .4, 0, -.5}};

    std::vector<double> works;
    std::transform(
        begin(speeds), end(speeds),
        begin(forces),
        back_inserter(works),
        [](auto v, auto f) { return f*v;});

}