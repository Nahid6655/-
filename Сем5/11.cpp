#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация данных
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 2.5);
    
    std::vector<double> vibrations(50);
    std::generate(vibrations.begin(), vibrations.end(), [&]() { return dist(gen); });
    
    std::cout << "=== ВИБРАЦИОННЫЙ АНАЛИЗ ===\n";
    
    // 1. Удаление шумов
    vibrations.erase(std::remove_if(vibrations.begin(), vibrations.end(),
                     [](double v) { return v < 0.1; }), vibrations.end());
    
    std::cout << "Измерений после фильтрации: " << vibrations.size() << std::endl;
    
    if (vibrations.empty()) return 0;
    
    // 2. Среднее и максимальное
    double avg = std::accumulate(vibrations.begin(), vibrations.end(), 0.0) / vibrations.size();
    double max = *std::max_element(vibrations.begin(), vibrations.end());
    
    std::cout << "Средняя амплитуда: " << avg << " мм/с\n";
    std::cout << "Максимальная амплитуда: " << max << " мм/с\n";
    
    // 3. Проверка порога
    bool aboveThreshold = std::all_of(vibrations.begin(), vibrations.end(),
                          [](double v) { return v > 0.5; });
    std::cout << "Все выше 0.5 мм/с: " << (aboveThreshold ? "да" : "нет") << std::endl;
    
    // 4. Топ-10 амплитуд
    std::sort(vibrations.begin(), vibrations.end(), std::greater<double>());
    
    std::cout << "Топ-10 амплитуд: ";
    for (int i = 0; i < std::min(10, (int)vibrations.size()); ++i) {
        std::cout << vibrations[i] << (i < 9 ? ", " : "\n");
    }
    
    return 0;
}
