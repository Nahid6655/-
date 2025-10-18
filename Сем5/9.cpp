#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-5.0, 100.0);
    
    std::vector<double> power(20);
    std::generate(power.begin(), power.end(), [&]() { return dist(gen); });
    
    std::cout << "=== СТАТИСТИКА МОЩНОСТИ ДВИГАТЕЛЯ ===\n";
    
    // 1. Удаление ошибок датчика
    power.erase(std::remove_if(power.begin(), power.end(), 
                [](double p) { return p < 0; }), power.end());
    
    std::cout << "Измерений после фильтрации: " << power.size() << std::endl;
    
    if (power.empty()) return 0;
    
    // 2. Основная статистика
    auto [min, max] = std::minmax_element(power.begin(), power.end());
    double avg = std::accumulate(power.begin(), power.end(), 0.0) / power.size();
    
    std::cout << "Мин: " << *min << " кВт, Макс: " << *max 
              << " кВт, Среднее: " << avg << " кВт\n";
    
    // 3. Проверка диапазона
    bool inRange = std::all_of(power.begin(), power.end(), 
                   [](double p) { return p >= 10 && p <= 90; });
    std::cout << "В диапазоне 10-90 кВт: " << (inRange ? "да" : "нет") << std::endl;
    
    // 4. Медиана
    std::sort(power.begin(), power.end());
    double median = (power.size() % 2 == 0) 
        ? (power[power.size()/2 - 1] + power[power.size()/2]) / 2.0
        : power[power.size()/2];
    
    std::cout << "Медиана: " << median << " кВт" << std::endl;
    
    return 0;
}
