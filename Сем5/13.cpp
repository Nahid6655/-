#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.5, 12.5);
    
    std::vector<double> pressure(50);
    std::generate(pressure.begin(), pressure.end(), [&]() { return dist(gen); });
    
    std::cout << "=== МОНИТОРИНГ ДАВЛЕНИЯ ===\n";
    
    // 1. Удаление ошибок
    pressure.erase(std::remove_if(pressure.begin(), pressure.end(),
                   [](double p) { return p < 0 || p > 12; }), pressure.end());
    
    std::cout << "Измерений после фильтрации: " << pressure.size() << std::endl;
    
    if (pressure.empty()) return 0;
    
    // 2. Среднее давление
    double avg = std::accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
    std::cout << "Среднее давление: " << avg << " бар\n";
    
    // 3. Минимальное и максимальное
    auto [minIt, maxIt] = std::minmax_element(pressure.begin(), pressure.end());
    std::cout << "Мин: " << *minIt << " бар, Макс: " << *maxIt << " бар\n";
    
    // 4. Вывод значений > 8 бар через for_each
    std::cout << "Давление > 8 бар:\n";
    std::for_each(pressure.begin(), pressure.end(), [](double p) {
        if (p > 8.0) {
            std::cout << "  " << p << " бар\n";
        }
    });
    
    return 0;
}
