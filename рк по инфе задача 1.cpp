------------------------------------------------------------
-- 1. СОЗДАНИЕ ТАБЛИЦ
------------------------------------------------------------

CREATE TABLE students (
    student_id SERIAL PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    group_number VARCHAR(20) NOT NULL
);

CREATE TABLE subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(100) NOT NULL
);

CREATE TABLE grades (
    grade_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES students(student_id),
    subject_id INT REFERENCES subjects(subject_id),
    grade INT CHECK (grade BETWEEN 1 AND 10)
);

CREATE TABLE attendance (
    attendance_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES students(student_id),
    date_attended DATE NOT NULL,
    status VARCHAR(20) CHECK (status IN ('present', 'absent'))
);

CREATE TABLE notes (
    note_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES students(student_id),
    note_text TEXT
);

------------------------------------------------------------
-- 2. НАПОЛНЕНИЕ ДАННЫМИ
------------------------------------------------------------

-- 6 студентов
INSERT INTO students (full_name, group_number) VALUES
('Иванов Иван', 'A-01'),
('Петров Пётр', 'A-01'),
('Сидоров Алексей', 'A-01'),
('Кузнецов Максим', 'A-01'),
('Гордеев Антон', 'A-01'),
('Смирнова Анна', 'A-01');

-- 3 предмета
INSERT INTO subjects (subject_name) VALUES
('Математический анализ'),
('Аналитическая геометрия'),
('Информатика');

-- Оценки для всех студентов по всем предметам (случайные)
INSERT INTO grades (student_id, subject_id, grade)
SELECT s.student_id, sub.subject_id, (5 + RANDOM()*5)::int
FROM students s CROSS JOIN subjects sub;

-- Посещаемость на два дня
INSERT INTO attendance (student_id, date_attended, status)
SELECT student_id, '2025-01-10', 'present' FROM students;

INSERT INTO attendance (student_id, date_attended, status)
SELECT student_id, '2025-01-11', 'absent' FROM students;

-- Заметки
INSERT INTO notes (student_id, note_text) VALUES
(1, 'Любит информатику'),
(2, 'Нужна помощь по информатике'),
(3, 'Редко посещает занятия по информатике'),
(4, 'Отличник по всем предметам'),
(5, 'Хорошо работает в команде'),
(6, 'Прогресс по информатике');

------------------------------------------------------------
-- 3. ИНДЕКСЫ
------------------------------------------------------------

-- Быстрый поиск одногруппников
CREATE INDEX idx_students_group ON students(group_number);

-- Ускорение агрегированных запросов по студенту
CREATE INDEX idx_grades_student ON grades(student_id);

-- GIN для полнотекстового поиска
CREATE INDEX idx_notes_gin ON notes USING GIN (to_tsvector('russian', note_text));

------------------------------------------------------------
-- 4. ПРЕДСТАВЛЕНИЕ СРЕДНИХ БАЛЛОВ
------------------------------------------------------------

CREATE VIEW student_avg_grades AS
SELECT 
    s.student_id,
    s.full_name,
    AVG(g.grade) AS avg_grade
FROM students s
JOIN grades g ON s.student_id = g.student_id
GROUP BY s.student_id, s.full_name;

------------------------------------------------------------
-- 5. ТРАНЗАКЦИЯ ДОБАВЛЕНИЯ СТУДЕНТА С ОЦЕНКАМИ
------------------------------------------------------------

DO $$
DECLARE 
    new_student INT;
BEGIN
    INSERT INTO students(full_name, group_number)
    VALUES ('Новиков Илья', 'A-01')
    RETURNING student_id INTO new_student;

    INSERT INTO grades(student_id, subject_id, grade) VALUES
    (new_student, 1, 9),
    (new_student, 2, 8),
    (new_student, 3, 10);
END $$;

------------------------------------------------------------
-- 6. SQL-ЗАПРОСЫ
------------------------------------------------------------

-- 1) Найти 5 одногруппников студента (2 до и 3 после по student_id)
SELECT *
FROM students
WHERE group_number = (
    SELECT group_number FROM students WHERE student_id = 3
)
AND student_id != 3
ORDER BY student_id
LIMIT 5;

-- 2) Средний балл конкретного студента через представление
SELECT * FROM student_avg_grades WHERE student_id = 2;

-- 3) Средний балл по предмету "Информатика"
SELECT AVG(grade)
FROM grades g
JOIN subjects s ON g.subject_id = s.subject_id
WHERE s.subject_name = 'Информатика';

-- 4) Полнотекстовый поиск заметок
SELECT *
FROM notes
WHERE to_tsvector('russian', note_text) @@ to_tsquery('информатика');

-- 5) Транзакция обновления посещаемости студента
BEGIN;
UPDATE attendance
SET status = 'present'
WHERE student_id = 4 AND date_attended = '2025-01-11';
COMMIT;
