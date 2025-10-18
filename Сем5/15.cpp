#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Данные
    std::vector<std::vector<double>> temp(5, std::vector<double>(30));
    std::vector<std::vector<double>> pressure(5, std::vector<double>(100));
    
    // Заполнение данными
    for (auto& t : temp) std::generate(t.begin(), t.end(), [&]() { return 20 + (gen() % 80); });
    for (auto& p : pressure) std::generate(p.begin(), p.end(), [&]() { return 1 + (gen() % 90) / 10.0; });
    
    // 1. Средние температуры
    std::vector<double> avgTemp(5);
    std::transform(temp.begin(), temp.end(), avgTemp.begin(),
        [](auto& channel) { 
            return std::accumulate(channel.begin(), channel.end(), 0.0) / channel.size(); 
        });
    
    // 2. Min-max давления
    std::vector<std::pair<double, double>> pressureMM(5);
    for (int i = 0; i < 5; ++i) {
        auto [min, max] = std::minmax_element(pressure[i].begin(), pressure[i].end());
        pressureMM[i] = {*min, *max};
    }
    
    // 3. Разности измерений
    std::vector<double> tempDiffs(temp[0].size() - 1);
    std::transform(temp[0].begin(), temp[0].end() - 1, temp[0].begin() + 1,
                   tempDiffs.begin(), [](double a, double b) { return b - a; });
    
    // 4. Канал с max вариацией температуры
    std::vector<double> tempVars(5);
    for (int i = 0; i < 5; ++i) {
        auto [min, max] = std::minmax_element(temp[i].begin(), temp[i].end());
        tempVars[i] = *max - *min;
    }
    int maxVarChan = std::distance(tempVars.begin(), 
                                  std::max_element(tempVars.begin(), tempVars.end())) + 1;
    
    // 5. Нормализация давления
    std::vector<std::vector<double>> normPressure(5);
    for (int i = 0; i < 5; ++i) {
        auto [min, max] = pressureMM[i];
        normPressure[i].resize(pressure[i].size());
        std::transform(pressure[i].begin(), pressure[i].end(), normPressure[i].begin(),
            [min, max](double v) { return (v - min) / (max - min); });
    }
    
    // 6. Пики давления (>0.9)
    std::cout << "Пики давления:\n";
    for (int i = 0; i < 5; ++i) {
        std::for_each(normPressure[i].begin(), normPressure[i].end(),
            [i](double v) { 
                if (v > 0.9) std::cout << "Канал " << i+1 << ": " << v << "\n"; 
            });
    }
    
    // 7. Канал с max средней температурой
    std::vector<std::pair<int, double>> ranked;
    for (int i = 0; i < 5; ++i) ranked.emplace_back(i+1, avgTemp[i]);
    std::sort(ranked.begin(), ranked.end(), 
              [](auto a, auto b) { return a.second > b.second; });
    
    std::cout << "Макс. температура: канал " << ranked[0].first 
              << " (" << ranked[0].second << "°C)\n";
    
    return 0;
}
