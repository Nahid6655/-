#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

int main() {
    // Создание генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    
    // Создание вектора из 20 случайных чисел
    std::vector<int> numbers(20);
    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
    
    // Вывод исходного вектора
    std::cout << "Исходный вектор: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << (i < numbers.size() - 1 ? " " : "\n");
    }
    
    // 1. Поиск минимального и максимального значения с помощью minmax_element
    auto minmax = std::minmax_element(numbers.begin(), numbers.end());
    std::cout << "Минимальное значение: " << *minmax.first << std::endl;
    std::cout << "Максимальное значение: " << *minmax.second << std::endl;
    std::cout << "Позиция минимума: " << std::distance(numbers.begin(), minmax.first) << std::endl;
    std::cout << "Позиция максимума: " << std::distance(numbers.begin(), minmax.second) << std::endl;
    
    // 2. Вычисление среднего значения с помощью accumulate
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    double average = sum / numbers.size();
    std::cout << "Сумма элементов: " << sum << std::endl;
    std::cout << "Среднее значение: " << average << std::endl;
    
    // 3. Нахождение медианы
    // Создаем копию для сортировки (чтобы не изменять исходный вектор)
    std::vector<int> sortedNumbers = numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    
    // Вывод отсортированного вектора
    std::cout << "Отсортированный вектор: ";
    for (size_t i = 0; i < sortedNumbers.size(); ++i) {
        std::cout << sortedNumbers[i] << (i < sortedNumbers.size() - 1 ? " " : "\n");
    }
    
    // Вычисление медианы
    double median;
    size_t size = sortedNumbers.size();
    
    if (size % 2 == 0) {
        // Четное количество элементов - медиана равна среднему двух центральных
        median = (sortedNumbers[size / 2 - 1] + sortedNumbers[size / 2]) / 2.0;
    } else {
        // Нечетное количество элементов - медиана равна центральному элементу
        median = sortedNumbers[size / 2];
    }
    
    std::cout << "Медиана: " << median << std::endl;
    
    return 0;
}
