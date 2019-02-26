#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
// https://www.gnu.org/software/gsl/doc/html/index.html
#include "gsl/gsl_fit.h"

template<typename Tag>
struct Strong
{
    template<typename T> struct Value {
        T value;
    };
};
struct Distance_tag {};
struct Time_tag {};
struct TimeDiff_tag {};
struct Speed_tag {};

int main() {
    using Distances = Strong<Distance_tag>::Value<std::vector<double>>;
    Distances increments{{{10, 5, 4, 5, 7, 10, 10, 7}}};
    using Timestamps = Strong<Time_tag>::Value<std::vector<double>>;
    Timestamps timestamps{{{1, 2, 3, 4, 5, 6, 7, 8}}};

    struct Fit {
        double c0, c1;
        double cov00, cov01, cov11;
        double sumsq;
    } fit;
    const auto status = gsl_fit_linear(&timestamps.value[0], 1, &increments.value[0], 1, timestamps.value.size(),    
        &fit.c0, &fit.c1, &fit.cov00, &fit.cov01, &fit.cov11, &fit.sumsq
    );

    using Timediffs = Strong<TimeDiff_tag>::Value<std::vector<double>>;
    Timediffs delta_ts;
    std::adjacent_difference(begin(timestamps.value), end(timestamps.value), back_inserter(delta_ts.value));

    using Speeds = Strong<Speed_tag>::Value<std::vector<double>>;
    Speeds speeds;
    std::transform(
        begin(increments.value), end(increments.value),
        begin(delta_ts.value),
        back_inserter(speeds.value),
        [](auto dx, auto dt) { return dx/dt;});
    
    struct Force_tag {};
    using Forces = Strong<Force_tag>::Value<std::vector<double>>;
    Forces forces{{1, .15, .2, .2, .1, .4, 0, -.5}};

    struct Work_tag {};
    using Works = Strong<Work_tag>::Value<std::vector<double>>;
    Works works;
    std::transform(
        begin(speeds.value), end(speeds.value),
        begin(forces.value),
        back_inserter(works.value),
        [](auto v, auto f) { return f*v;});

}