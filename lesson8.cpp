#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <span>
#include <format>
#include <concepts>

template <typename T>
// concept Numeric = std::integral<T> || std::floating_point<T>;
concept my_numeric_concept = required(T& t)
{
    {t.key_integral()} -> std::convertible_to<std::integral>;
    {t.key_floating_point()} -> std::convertible_to<std::floating_point>;
}

std::vector<int> filterAndTransform(const std::vector<int>& data) {
    std::vector<int> result;
    auto evenNumbers = data | std::views::filter([](int n) { return n % 2 == 0; })
                            | std::views::transform([](int n) { return n * 2; });
    result.assign(evenNumbers.begin(), evenNumbers.end());
    return result;
}

int computeSum(std::span<const int> subset) {
    return std::accumulate(subset.begin(), subset.end(), 0);
}

int main() {

    std::vector<int> data(10);
    std::iota(data.begin(), data.end(), 1);
    
    auto filteredTransformed = filterAndTransform(data);
    
    int sum = computeSum(std::span(filteredTransformed.begin(), filteredTransformed.begin() + 3));
    
    // Print results
    std::cout << std::format("Original data: {}\n", std::format("{{ {} }}", std::views::all(data)))
              << std::format("Filtered and transformed data: {}\n", std::format("{{ {} }}", std::views::all(filteredTransformed)))
              << std::format("Sum of subset: {}\n", sum);
    
    return 0;
}
