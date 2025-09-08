#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"

// структура студента
struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// функция для чтения из файла
void loadStudents(std::vector<Student>& database, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "не удалось открыть файл " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.name >> student.age >> student.major >> student.gpa) {
            database.push_back(student);
        } else {
            std::cout << "ошибка чтения строки" << line << "\n";
        }
    }
}

// функция добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin.ignore(); 
    std::getline(std::cin, student.name); 
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin.ignore();
    std::getline(std::cin, student.major); 
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// отобразить информацию о студентах из базы данных
void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// найти информацию о студенте по имени
void searchName(const std::vector<Student>& database) {
    std::string name;
    std::cout << "Введите имя студента: ";
    std::cin.ignore(); 
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

// найти информацию о студенте по специальности
void searcSpecс(const std::vector<Student>& database) {
    std::string spec;
    std::cout << "Введите специальность: ";
    std::cin.ignore(); 
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

int main(int argc, char **argv){
    std::vector<Student> database;
    loadStudents(database, "bd.txt"); // Указываем имя файла
    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Найти по имени\n";
        std::cout << "4. Найти по специальности\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        TEST(FunctionTesting, AddStudent) {
            std::vector<Student> database;
            std::streambuf* originalCin = std::cin.rdbuf();
            std::stringstream input;
            input << "Иван Иванов\n20\nИнформатика\n4.5\n";
            std::cin.rdbuf(input.rdbuf());
            addStudent(database);
            std::cin.rdbuf(originalCin);
            ASSERT_EQ(database.size(), 1);
            EXPECT_EQ(database[0].name, "Иван Иванов");
            EXPECT_EQ(database[0].age, 20);
            EXPECT_EQ(database[0].major, "Информатика");
            EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
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
                searcSpecс(database); 
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();}
