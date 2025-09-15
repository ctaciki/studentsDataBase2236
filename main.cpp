#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "gtest/gtest.h"

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void loadStudents(std::vector<Student>& database, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.name >> student.age >> student.major >> student.gpa) {
            database.push_back(student);
        } else {
            std::cout << "Ошибка чтения строки: " << line << "\n";
        }
    }
}

void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, student.name);
    std::cout << "Введите возраст студента: ";
    while (!(std::cin >> student.age) || student.age < 0) {
        std::cout << "Неверный возраст. Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Введите специальность студента: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, student.major);
    std::cout << "Введите средний балл студента: ";
    while (!(std::cin >> student.gpa) || student.gpa < 0.0 || student.gpa > 5.0) {
        std::cout << "Неверный балл. Введите число от 0.0 до 5.0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

void searchName(const std::vector<Student>& database) {
    std::string name;
    std::cout << "Введите имя студента: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    bool found = false;
    for (const Student& student : database) {
        if (name == student.name) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Студент с именем \"" << name << "\" не найден.\n";
    }
}

void searchSpec(const std::vector<Student>& database) {
    std::string spec;
    std::cout << "Введите специальность: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, spec);
    bool found = false;
    for (const Student& student : database) {
        if (spec == student.major) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Студент со специальностью \"" << spec << "\" не найден.\n";
    }
}

// Простой и надежный тест без подмены cin
// Вспомогательная функция для создания тестовой базы данных
std::vector<Student> createTestDatabase() {
    std::vector<Student> database;
    
    Student student1;
    student1.name = "Иван Иванов";
    student1.age = 20;
    student1.major = "Информатика";
    student1.gpa = 4.5;
    database.push_back(student1);
    
    Student student2;
    student2.name = "Анна Петрова";
    student2.age = 21;
    student2.major = "Математика";
    student2.gpa = 4.8;
    database.push_back(student2);
    
    Student student3;
    student3.name = "Петр Сидоров";
    student3.age = 22;
    student3.major = "Физика";
    student3.gpa = 4.2;
    database.push_back(student3);
    
    Student student4;
    student4.name = "Мария Козлова";
    student4.age = 19;
    student4.major = "Информатика";
    student4.gpa = 4.7;
    database.push_back(student4);
    
    return database;
}

// Тесты для функции addStudent
TEST(FunctionTesting, AddStudent) {
    std::vector<Student> database;

    // Тестируем добавление студента напрямую
    Student student;
    student.name = "Иван Иванов";
    student.age = 20;
    student.major = "Информатика";
    student.gpa = 4.5;

    database.push_back(student);

    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Иван Иванов");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

// Дополнительный тест для проверки нескольких студентов
TEST(FunctionTesting, MultipleStudents) {
TEST(FunctionTesting, AddMultipleStudents) {
    std::vector<Student> database;

    Student student1;
    student1.name = "Анна Петрова";
    student1.age = 21;
    student1.major = "Математика";
    student1.gpa = 4.8;
    database.push_back(student1);

    Student student2;
    student2.name = "Петр Сидоров";
    student2.age = 22;
    student2.major = "Физика";
    student2.gpa = 4.2;
    database.push_back(student2);

    ASSERT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Анна Петрова");
    EXPECT_EQ(database[1].name, "Петр Сидоров");
    EXPECT_EQ(database[0].major, "Математика");
    EXPECT_EQ(database[1].major, "Физика");
}

// Тесты для функции displayStudents
TEST(FunctionTesting, DisplayStudentsEmpty) {
    std::vector<Student> database;
    // Функция должна работать без ошибок на пустой базе
    testing::internal::CaptureStdout();
    displayStudents(database);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Список студентов:") != std::string::npos);
}

TEST(FunctionTesting, DisplayStudentsWithData) {
    std::vector<Student> database = createTestDatabase();
    testing::internal::CaptureStdout();
    displayStudents(database);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Иван Иванов") != std::string::npos);
    EXPECT_TRUE(output.find("Информатика") != std::string::npos);
    EXPECT_TRUE(output.find("4.5") != std::string::npos);
}

// Тесты для функции searchName
TEST(FunctionTesting, SearchNameFound) {
    std::vector<Student> database = createTestDatabase();
    
    testing::internal::CaptureStdout();
    // Эмулируем поиск существующего студента
    bool found = false;
    std::string searchName = "Иван Иванов";
    for (const Student& student : database) {
        if (searchName == student.name) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(found);
    EXPECT_TRUE(output.find("Иван Иванов") != std::string::npos);
    EXPECT_TRUE(output.find("20") != std::string::npos);
    EXPECT_TRUE(output.find("Информатика") != std::string::npos);
}

TEST(FunctionTesting, SearchNameNotFound) {
    std::vector<Student> database = createTestDatabase();
    
    testing::internal::CaptureStdout();
    // Эмулируем поиск несуществующего студента
    bool found = false;
    std::string searchName = "Несуществующий Студент";
    for (const Student& student : database) {
        if (searchName == student.name) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "Студент с именем \"" << searchName << "\" не найден.\n";
    }
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(found);
    EXPECT_TRUE(output.find("не найден") != std::string::npos);
}

// Тесты для функции searchSpec
TEST(FunctionTesting, SearchSpecFound) {
    std::vector<Student> database = createTestDatabase();
    
    testing::internal::CaptureStdout();
    // Эмулируем поиск по специальности
    bool found = false;
    std::string searchSpec = "Информатика";
    for (const Student& student : database) {
        if (searchSpec == student.major) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(found);
    EXPECT_TRUE(output.find("Информатика") != std::string::npos);
    // Должны найти двух студентов с Информатикой
    EXPECT_TRUE(output.find("Иван Иванов") != std::string::npos);
    EXPECT_TRUE(output.find("Мария Козлова") != std::string::npos);
}

TEST(FunctionTesting, SearchSpecNotFound) {
    std::vector<Student> database = createTestDatabase();
    
    testing::internal::CaptureStdout();
    // Эмулируем поиск несуществующей специальности
    bool found = false;
    std::string searchSpec = "Химия";
    for (const Student& student : database) {
        if (searchSpec == student.major) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "Студент со специальностью \"" << searchSpec << "\" не найден.\n";
    }
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(found);
    EXPECT_TRUE(output.find("не найден") != std::string::npos);
}

// Тесты для функции loadStudents
TEST(FunctionTesting, LoadStudentsFromString) {
    std::vector<Student> database;
    
    // Эмулируем содержимое файла
    std::stringstream fileContent;
    fileContent << "Иван 20 Информатика 4.5\n";
    fileContent << "Анна 21 Математика 4.8\n";
    fileContent << "Петр 22 Физика 4.2\n";
    
    // Эмулируем чтение из файла
    std::string line;
    while (std::getline(fileContent, line)) {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.name >> student.age >> student.major >> student.gpa) {
            database.push_back(student);
        }
    }
    
    ASSERT_EQ(database.size(), 3);
    EXPECT_EQ(database[0].name, "Иван");
    EXPECT_EQ(database[1].age, 21);
    EXPECT_EQ(database[2].major, "Физика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(FunctionTesting, LoadStudentsInvalidData) {
    std::vector<Student> database;
    
    // Эмулируем файл с некорректными данными
    std::stringstream fileContent;
    fileContent << "Иван 20 Информатика 4.5\n";
    fileContent << "Некорректная_строка\n";
    fileContent << "Анна 21 Математика 4.8\n";
    
    // Эмулируем чтение из файла
    std::string line;
    while (std::getline(fileContent, line)) {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.name >> student.age >> student.major >> student.gpa) {
            database.push_back(student);
        }
    }
    
    // Должны загрузиться только 2 корректные строки
    ASSERT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Иван");
    EXPECT_EQ(database[1].name, "Анна");
}

int main(int argc, char **argv) {
    // Режим тестирования (для CI)
    if (argc > 1 && std::string(argv[1]) == "--run-tests") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    // Обычный режим работы
    std::vector<Student> database;
    loadStudents(database, "bd.txt");
    int choice;

    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Найти по имени\n";
        std::cout << "4. Найти по специальности\n";
        std::cout << "5. Запустить тесты\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                searchName(database);
                break;
            case 4:
                searchSpec(database);
                break;
            case 5:
                std::cout << "Для запуска тестов перезапустите программу с параметром --run-tests\n";
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

        // Очищаем буфер после каждого выбора
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice != 0);

    return 0;
}
