#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(100.0, 500.0);
    
    std::vector<double> consumption(24);
    std::generate(consumption.begin(), consumption.end(), [&]() { return dist(gen); });
    
    std::cout << "=== ЭНЕРГОПОТРЕБЛЕНИЕ ЗАВОДА ===\n";
    
    // 1. Суммарное и среднее потребление
    double total = std::accumulate(consumption.begin(), consumption.end(), 0.0);
    double avg = total / consumption.size();
    std::cout << "Суммарное: " << total << " кВт·ч\n";
    std::cout << "Среднее: " << avg << " кВт·ч/час\n";
    
    // 2. Пиковое потребление
    auto peakIt = std::max_element(consumption.begin(), consumption.end());
    int peakHour = std::distance(consumption.begin(), peakIt);
    std::cout << "Пик: " << peakHour << ":00 - " << *peakIt << " кВт·ч\n";
    
    // 3. Отклонения от среднего
    std::vector<double> deviations(24);
    std::transform(consumption.begin(), consumption.end(), deviations.begin(),
                   [avg](double c) { return c - avg; });
    
    std::cout << "Отклонения: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << i << ":00=" << deviations[i] << " ";
    }
    std::cout << "...\n";
    
    // 4. Топ-5 минимальных часов
    std::vector<std::pair<int, double>> hours;
    for (int i = 0; i < 24; ++i) {
        hours.emplace_back(i, consumption[i]);
    }
    
    std::sort(hours.begin(), hours.end(),
              [](auto a, auto b) { return a.second < b.second; });
    
    std::cout << "Топ-5 минимальных:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << hours[i].first << ":00 - " << hours[i].second << " кВт·ч\n";
    }
    
    return 0;
}
