#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    // Создание генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-50, 50);
    
    // Создание вектора случайных чисел
    std::vector<int> numbers(15);
    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
    
    // Вывод исходного вектора
    std::cout << "Исходный вектор: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Удаление отрицательных чисел с помощью remove_if и лямбды
    auto newEnd = std::remove_if(numbers.begin(), numbers.end(), 
        [](int num) {
            return num < 0;  // Возвращает true для отрицательных чисел
        });
    
    // Удаление "недействительных" элементов из вектора
    numbers.erase(newEnd, numbers.end());
    
    // Вывод результата
    std::cout << "Вектор после удаления отрицательных: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Размер вектора: " << numbers.size() << std::endl;
    
    return 0;
}
