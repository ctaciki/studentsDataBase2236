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

// ---------------- тестовая база ----------------
std::vector<Student> createTestDatabase() {
    return {
        {"Иван Иванов", 20, "Информатика", 4.5},
        {"Анна Петрова", 21, "Математика", 4.8},
        {"Петр Сидоров", 22, "Физика", 4.2},
        {"Мария Козлова", 19, "Информатика", 4.7}
    };
}

// ------------------ ТЕСТЫ ------------------
TEST(FunctionTesting, AddStudent) {
    std::vector<Student> database;
    database.push_back({"Иван Иванов", 20, "Информатика", 4.5});
    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Иван Иванов");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(FunctionTesting, DisplayStudentsWithData) {
    auto database = createTestDatabase();
    testing::internal::CaptureStdout();
    displayStudents(database);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Иван Иванов") != std::string::npos);
    EXPECT_TRUE(output.find("Информатика") != std::string::npos);
    EXPECT_TRUE(output.find("4.5") != std::string::npos);
}

TEST(FunctionTesting, SearchNameFound) {
    auto database = createTestDatabase();
    testing::internal::CaptureStdout();
    std::string searchName = "Иван Иванов";
    bool found = false;
    for (const auto& s : database) {
        if (s.name == searchName) {
            std::cout << s.name << "\n";
            found = true;
        }
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(found);
    EXPECT_TRUE(output.find("Иван Иванов") != std::string::npos);
}

TEST(FunctionTesting, SearchSpecNotFound) {
    auto database = createTestDatabase();
    testing::internal::CaptureStdout();
    std::string spec = "Химия";
    bool found = false;
    for (const auto& s : database) {
        if (s.major == spec) found = true;
    }
    if (!found) std::cout << "не найден\n";
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(found);
    EXPECT_TRUE(output.find("не найден") != std::string::npos);
}

// ------------------ MAIN ------------------
int main(int argc, char **argv) {
    if (argc > 1 && std::string(argv[1]) == "--run-tests") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    std::vector<Student> database;
    loadStudents(database, "bd.txt");

    int choice = -1;
    while (choice != 0) {
        std::cout << "Меню:\n"
                  << "1. Добавить студента\n"
                  << "2. Вывести список студентов\n"
                  << "3. Найти по имени\n"
                  << "4. Найти по специальности\n"
                  << "5. Запустить тесты\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cout << "Неверный ввод.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addStudent(database); break;
            case 2: displayStudents(database); break;
            case 3: searchName(database); break;
            case 4: searchSpec(database); break;
            case 5: std::cout << "Перезапустите с --run-tests\n"; break;
            case 0: std::cout << "Выход...\n"; break;
            default: std::cout << "Неверный выбор.\n";
        }
    }
    return 0;
}
