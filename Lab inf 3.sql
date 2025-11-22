-- 1. Создание базы данных
CREATE DATABASE IF NOT EXISTS restaurant_menu;
USE restaurant_menu;

-- 2. Создание таблиц

-- Таблица категорий
CREATE TABLE IF NOT EXISTS categories (
    id INT AUTO_INCREMENT PRIMARY KEY,
    category_name VARCHAR(100) NOT NULL
);

-- Таблица блюд
CREATE TABLE IF NOT EXISTS dishes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(150) NOT NULL,
    category_id INT NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

-- Таблица заказов
CREATE TABLE IF NOT EXISTS orders (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    dish_id INT NOT NULL,
    order_date DATE NOT NULL,
    quantity INT NOT NULL,
    total_price DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (dish_id) REFERENCES dishes(id)
);

-- 3. Добавление данных

-- Категории
INSERT INTO categories (category_name) VALUES
('Супы'),
('Основные блюда'),
('Закуски'),
('Десерты');

-- Блюда
INSERT INTO dishes (name, category_id, price) VALUES
('Борщ', 1, 150.00),
('Куриный суп', 1, 130.00),
('Стейк', 2, 550.00),
('Паста Болоньезе', 2, 320.00),
('Сырные палочки', 3, 180.00),
('Тирамису', 4, 260.00);

-- Заказы
INSERT INTO orders (dish_id, order_date, quantity, total_price) VALUES
(1, '2025-01-10', 2, 300.00),
(3, '2025-01-10', 1, 550.00),
(4, '2025-01-11', 3, 960.00),
(6, '2025-01-11', 2, 520.00),
(3, '2025-01-12', 2, 1100.00),
(5, '2025-01-12', 4, 720.00);

-- 4. Запросы

-- 4.1 Все блюда категории "Основные блюда"
SELECT d.id, d.name, d.price
FROM dishes d
JOIN categories c ON d.category_id = c.id
WHERE c.category_name = 'Основные блюда';

-- 4.2 Все заказы за период (пример)
SELECT *
FROM orders
WHERE order_date BETWEEN '2025-01-10' AND '2025-01-11';

-- 4.3 Общая стоимость заказов за день
SELECT SUM(total_price) AS total_income
FROM orders
WHERE order_date = '2025-01-11';

-- 4.4 Наиболее популярные блюда
SELECT d.name, SUM(o.quantity) AS total_ordered
FROM orders o
JOIN dishes d ON o.dish_id = d.id
GROUP BY d.id, d.name
ORDER BY total_ordered DESC;
