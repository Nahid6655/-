#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Генерация случайных скоростей
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 180);
    
    std::vector<int> speeds(50);
    std::generate(speeds.begin(), speeds.end(), [&]() { return dist(gen); });
    
    std::cout << "=== АНАЛИЗ СКОРОСТИ АВТОМОБИЛЯ ===" << std::endl;
    
    // 1. Превышения скорости > 120
    std::vector<int> overSpeed;
    std::copy_if(speeds.begin(), speeds.end(), std::back_inserter(overSpeed),
        [](int s) { return s > 120; });
    
    std::cout << "Превышения скорости (>120): " << overSpeed.size() << std::endl;
    
    // 2. Средняя скорость
    double avg = std::accumulate(speeds.begin(), speeds.end(), 0.0) / speeds.size();
    std::cout << "Средняя скорость: " << avg << " km/h" << std::endl;
    
    // 3. Проверка движения
    bool moving = std::all_of(speeds.begin(), speeds.end(), [](int s) { return s > 0; });
    std::cout << "Всегда двигался: " << (moving ? "да" : "нет") << std::endl;
    
    // 4. Топ-10 максимальных скоростей
    std::vector<int> sorted = speeds;
    std::sort(sorted.begin(), sorted.end(), std::greater<int>());
    
    std::cout << "Топ-10 скоростей: ";
    for (int i = 0; i < std::min(10, (int)sorted.size()); ++i) {
        std::cout << sorted[i] << (i < 9 ? ", " : "\n");
    }
    
    return 0;
}
