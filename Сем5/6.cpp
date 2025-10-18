#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    // Создание генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 15);  // Диапазон 1-15 для гарантии повторений
    
    // Создание вектора из 20 чисел
    std::vector<int> numbers(20);
    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
    
    // Вывод исходного вектора
    std::cout << "Исходный вектор: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << (i < numbers.size() - 1 ? " " : "\n");
    }
    
    // 1. Проверка наличия числа 7 с помощью find
    auto found = std::find(numbers.begin(), numbers.end(), 7);
    if (found != numbers.end()) {
        std::cout << "Число 7 найдено на позиции: " << std::distance(numbers.begin(), found) << std::endl;
    } else {
        std::cout << "Число 7 не найдено в векторе" << std::endl;
    }
    
    // 2. Удаление всех повторяющихся чисел (sort + unique)
    
    // Сначала сортируем вектор
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "Отсортированный вектор: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << (i < numbers.size() - 1 ? " " : "\n");
    }
    
    // Затем используем unique для перемещения дубликатов в конец
    auto uniqueEnd = std::unique(numbers.begin(), numbers.end());
    
    // Удаляем "неуникальные" элементы
    numbers.erase(uniqueEnd, numbers.end());
    
    // 3. Вывод оставшихся элементов
    std::cout << "Уникальные элементы: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << (i < numbers.size() - 1 ? " " : "\n");
    }
    std::cout << "Количество уникальных элементов: " << numbers.size() << std::endl;
    
    return 0;
}
