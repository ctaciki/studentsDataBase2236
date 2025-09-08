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

// Функция для запуска тестов без завершения программы
int runTests() {
    std::cout << "Запуск тестов...\n";
    int argc = 1;
    char* argv[] = {(char*)"test_program", nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Исправленный тест
TEST(FunctionTesting, AddStudent) {
    std::vector<Student> database;
    std::streambuf* originalCin = std::cin.rdbuf();
    
    std::stringstream input;
    input << "Иван Иванов\n";
    input << "20\n";
    input << "Информатика\n";
    input << "4.5\n";
    
    std::cin.rdbuf(input.rdbuf());
    addStudent(database);
    std::cin.rdbuf(originalCin);
    
    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Иван Иванов");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
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
                runTests();
                std::cout << "Тесты завершены. Нажмите Enter для продолжения...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
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
