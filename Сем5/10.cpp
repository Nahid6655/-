#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(50.0, 200.0);
    
    std::vector<double> consumption(30);
    std::generate(consumption.begin(), consumption.end(), [&]() { return dist(gen); });
    
    std::cout << "=== ЭНЕРГОПОТРЕБЛЕНИЕ ЗДАНИЯ ===\n";
    
    // 1. Общее потребление
    double total = std::accumulate(consumption.begin(), consumption.end(), 0.0);
    std::cout << "Общее потребление: " << total << " кВт·ч\n";
    
    // 2. Среднесуточное
    double average = total / consumption.size();
    std::cout << "Среднесуточное: " << average << " кВт·ч\n";
    
    // 3. Максимальное и минимальное
    auto [minIt, maxIt] = std::minmax_element(consumption.begin(), consumption.end());
    int minDay = std::distance(consumption.begin(), minIt) + 1;
    int maxDay = std::distance(consumption.begin(), maxIt) + 1;
    
    std::cout << "Мин: день " << minDay << " (" << *minIt << " кВт·ч)\n";
    std::cout << "Макс: день " << maxDay << " (" << *maxIt << " кВт·ч)\n";
    
    // 4. Пиковые дни
    double peakLevel = average * 1.2;
    std::cout << "Пиковые дни (> " << peakLevel << " кВт·ч): ";
    
    for (size_t i = 0; i < consumption.size(); ++i) {
        if (consumption[i] > peakLevel) {
            std::cout << "день " << (i + 1) << " ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}
