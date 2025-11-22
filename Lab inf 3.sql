-- 1. Создание базы данных
CREATE DATABASE restaurant_menu;

-- Подключение к базе (в psql используйте \c restaurant_menu)
-- \c restaurant_menu

-- 2. Создание таблиц
-- Таблица категорий
CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    category_name VARCHAR(50) NOT NULL UNIQUE
);

-- Таблица блюд
CREATE TABLE dishes (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    category_id INT NOT NULL,
    price NUMERIC(10,2) NOT NULL,
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

-- Таблица заказов
CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,
    dish_id INT NOT NULL,
    order_date DATE NOT NULL,
    quantity INT NOT NULL,
    total_price NUMERIC(10,2) NOT NULL,
    FOREIGN KEY (dish_id) REFERENCES dishes(id)
);

-- 3. Добавление данных
-- Таблица категорий
INSERT INTO categories (category_name) VALUES
('Супы'),
('Основные блюда'),
('Закуски'),
('Десерты');

-- Таблица блюд
INSERT INTO dishes (name, category_id, price) VALUES
('Борщ', 1, 200.00),
('Котлета с картошкой', 2, 350.00),
('Салат Цезарь', 3, 250.00),
('Медовик', 4, 180.00);

-- Таблица заказов
INSERT INTO orders (dish_id, order_date, quantity, total_price) VALUES
(1, '2025-11-20', 2, 400.00),
(2, '2025-11-20', 1, 350.00),
(3, '2025-11-21', 3, 750.00),
(4, '2025-11-21', 1, 180.00);

-- 4. Примеры запросов

-- Список блюд определенной категории
SELECT d.name, d.price
FROM dishes d
JOIN categories c ON d.category_id = c.id
WHERE c.category_name = 'Основные блюда';

-- Все заказы за определенный период
SELECT *
FROM orders
WHERE order_date BETWEEN '2025-11-20' AND '2025-11-21';

-- Общая стоимость заказов за конкретный день
SELECT SUM(total_price) AS total_sales
FROM orders
WHERE order_date = '2025-11-20';

-- Наиболее популярные блюда
SELECT d.name, SUM(o.quantity) AS total_ordered
FROM orders o
JOIN dishes d ON o.dish_id = d.id
GROUP BY d.name
ORDER BY total_ordered DESC
LIMIT 5;
