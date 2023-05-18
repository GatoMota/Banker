#include <fmt/core.h>
#include <fmt/ranges.h>
#include <ranges>
#include <vector>
#include <algorithm>

using namespace std::views;
namespace ra = std::ranges;
namespace rv = ra::views;

auto main(void) -> int {
    auto const max = {753, 322, 902, 222, 433};
    auto const allocation = {10, 200, 302, 211, 2};
    auto available = 332;

    auto const need = zip_transform(std::minus{}, max, allocation);

    std::vector<int> proc;
    ra::transform(need, allocation, std::back_inserter(proc),
        [&available](auto e, auto a) { return e <= available ? available += a : false; });    

    std::vector<bool> mask(proc.size());
    std::transform(proc.begin(), proc.end(), mask.begin(),
        [](auto e) { return e ? true : false; });
    
    auto const result = proc;
    proc.clear();

    for (auto [e, a, m] : rv::zip(need, allocation, mask)) {
        proc.push_back(!m ? (e <= available ? available += a : false) : false);
    }

    auto indexes = result 
        | enumerate
        | filter([](const auto& pair) { return [](auto e) { return e; }(std::get<1>(pair)); })
        | transform([](const auto& pair) { return std::get<0>(pair); });

    auto  indexes2 = proc 
        | enumerate
        | filter([](const auto& pair) { return [](auto e) { return e; }(std::get<1>(pair)); })
        | transform([](const auto& pair) { return std::get<0>(pair); });

    fmt::print("{} {} {}", indexes, indexes2, ra::max(proc));

    exit(EXIT_SUCCESS);
}