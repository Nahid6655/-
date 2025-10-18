#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    // Создание вектора из 20 чисел
    std::vector<int> numbers = {15, 7, 23, 45, 12, 67, 34, 89, 56, 3, 
                               78, 91, 24, 47, 62, 18, 5, 83, 29, 41};
    
    // Вывод вектора
    std::cout << "Вектор чисел: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Поиск максимального элемента с помощью std::max_element
    auto maxElement = std::max_element(numbers.begin(), numbers.end());
    
    std::cout << "Максимальный элемент (без лямбды): " << *maxElement << std::endl;
    std::cout << "Позиция максимального элемента: " << std::distance(numbers.begin(), maxElement) << std::endl;
    
    return 0;
}
