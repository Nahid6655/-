#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных с реалистичным расходом
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(15.0, 100.0);
    
    std::vector<double> fuel(50);
    std::generate(fuel.begin(), fuel.end(), [&]() { return dist(gen); });
    
    // Имитация расхода
    for (size_t i = 1; i < fuel.size(); ++i) {
        if (fuel[i] > fuel[i-1]) {
            fuel[i] = fuel[i-1] - 0.5;  // Постоянный расход
        }
    }
    
    std::cout << "=== УПРАВЛЕНИЕ ЗАПАСАМИ ТОПЛИВА ===\n";
    
    // 1. Минимальный уровень
    double minLevel = *std::min_element(fuel.begin(), fuel.end());
    std::cout << "Мин. уровень: " << minLevel << "%\n";
    
    // 2. Проверка падения ниже 5% от максимального
    double maxLevel = *std::max_element(fuel.begin(), fuel.end());
    double threshold = maxLevel * 0.05;
    bool belowThreshold = std::any_of(fuel.begin(), fuel.end(),
                          [threshold](double f) { return f < threshold; });
    std::cout << "Падал ниже " << threshold << "%: " << (belowThreshold ? "да" : "нет") << "\n";
    
    // 3. Среднее потребление
    double consumption = fuel.front() - fuel.back();
    double timeHours = (fuel.size() - 1) * 10 / 60.0;
    double avgConsumption = consumption / timeHours;
    std::cout << "Среднее потребление: " << avgConsumption << "%/час\n";
    
    // 4. Медиана
    std::vector<double> sorted = fuel;
    std::sort(sorted.begin(), sorted.end());
    double median = (sorted.size() % 2 == 0) 
        ? (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2.0
        : sorted[sorted.size()/2];
    
    std::cout << "Медиана: " << median << "%\n";
    
    return 0;
}
