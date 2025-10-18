#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация случайных температур
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-60.0, 60.0);
    
    std::vector<double> temperatures(20);
    std::generate(temperatures.begin(), temperatures.end(), [&]() { 
        return dist(gen); 
    });
    
    std::cout << "Исходные температуры: ";
    for (double temp : temperatures) std::cout << temp << " ";
    std::cout << std::endl;
    
    // 1. Удаление значений вне диапазона [-50, 50]
    temperatures.erase(
        std::remove_if(temperatures.begin(), temperatures.end(),
            [](double temp) { return temp < -50.0 || temp > 50.0; }),
        temperatures.end()
    );
    
    std::cout << "После фильтрации: ";
    for (double temp : temperatures) std::cout << temp << " ";
    std::cout << std::endl;
    
    if (temperatures.empty()) {
        std::cout << "Нет данных для анализа" << std::endl;
        return 0;
    }
    
    // 2. Статистика
    auto [minIt, maxIt] = std::minmax_element(temperatures.begin(), temperatures.end());
    double average = std::accumulate(temperatures.begin(), temperatures.end(), 0.0) 
                   / temperatures.size();
    
    std::cout << "Мин: " << *minIt << ", Макс: " << *maxIt 
              << ", Среднее: " << average << std::endl;
    
    // 3. Проверка, что все температуры > -10
    bool allAboveMinus10 = std::all_of(temperatures.begin(), temperatures.end(),
        [](double temp) { return temp > -10.0; });
    
    std::cout << "Все температуры > -10: " 
              << (allAboveMinus10 ? "да" : "нет") << std::endl;
    
    return 0;
}
