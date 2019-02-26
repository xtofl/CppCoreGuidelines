#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
// https://www.gnu.org/software/gsl/doc/html/index.html
#include "gsl/gsl_fit.h"

int main() {
    std::vector<double> increments{{10, 5, 4, 5, 7, 10, 10, 7}};
    std::vector<double> timestamps{{1, 2, 3, 4, 5, 6, 7, 8}};

    struct Fit {
        double c0, c1;
        double cov00, cov01, cov11;
        double sumsq;
    } fit;
    const auto status = gsl_fit_linear(&timestamps[0], 1, &increments[0], 1, timestamps.size(),    
        &fit.c0, &fit.c1, &fit.cov00, &fit.cov01, &fit.cov11, &fit.sumsq
    );

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