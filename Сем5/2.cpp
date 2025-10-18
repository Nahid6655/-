#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Создание вектора из 10 чисел
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Вывод исходного вектора
    std::cout << "Исходный вектор: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Удвоение каждого элемента с помощью for_each и лямбда-функции
    std::for_each(numbers.begin(), numbers.end(), [](int &num) {
        num *= 2;  // Умножаем каждый элемент на 2
    });
    
    // Вывод измененного вектора
    std::cout << "Удвоенный вектор: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
