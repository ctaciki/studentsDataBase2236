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
    std::stringstream input;
    input << "\nИван Иванов\n20\nИнформатика\n4.5\n"; // Добавляем начальный \n для первого ignore
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    addStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    ASSERT_EQ(database.size(), 1) << "Database size should be 1";
    EXPECT_EQ(database[0].name, "Иван Иванов") << "Name mismatch";
    EXPECT_EQ(database[0].age, 20) << "Age mismatch";
    EXPECT_EQ(database[0].major, "Информатика") << "Major mismatch";
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5) << "GPA mismatch";
    EXPECT_TRUE(output.str().find("Студент добавлен") != std::string::npos) << "Output missing 'Студент добавлен'";
}

TEST(FunctionTesting, AddStudentInvalidAge) {
    std::vector<Student> database;
    std::stringstream input;
    input << "\nИван Иванов\n-1\n20\nИнформатика\n4.5\n"; // Начальный \n и исправление возраста
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    addStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    ASSERT_EQ(database.size(), 1) << "Database size should be 1";
    EXPECT_EQ(database[0].age, 20) << "Age should be 20";
    EXPECT_TRUE(output.str().find("Неверный возраст") != std::string::npos) << "Output missing 'Неверный возраст'";
}

TEST(FunctionTesting, AddStudentInvalidGPA) {
    std::vector<Student> database;
    std::stringstream input;
    input << "\nИван Иванов\n20\nИнформатика\n6.0\n4.5\n"; // Начальный \n и исправление GPA
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    addStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    ASSERT_EQ(database.size(), 1) << "Database size should be 1";
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5) << "GPA should be 4.5";
    EXPECT_TRUE(output.str().find("Неверный балл") != std::string::npos) << "Output missing 'Неверный балл'";
}

TEST(FunctionTesting, DisplayStudentsWithData) {
    auto database = createTestDatabase();
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    displayStudents(database);
    std::cout.rdbuf(old_cout);
    std::string output_str = output.str();
    EXPECT_TRUE(output_str.find("Иван Иванов") != std::string::npos) << "Output missing 'Иван Иванов'";
    EXPECT_TRUE(output_str.find("Информатика") != std::string::npos) << "Output missing 'Информатика'";
    EXPECT_TRUE(output_str.find("4.5") != std::string::npos) << "Output missing '4.5'";
}

TEST(FunctionTesting, DisplayStudentsEmpty) {
    std::vector<Student> database;
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    displayStudents(database);
    std::cout.rdbuf(old_cout);
    EXPECT_EQ(output.str(), "Список студентов:\n") << "Output mismatch for empty database";
}

TEST(FunctionTesting, SearchNameFound) {
    auto database = createTestDatabase();
    std::stringstream input;
    input << "\nИван Иванов\n"; // Начальный \n для ignore
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    searchName(database);
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    std::string output_str = output.str();
    EXPECT_TRUE(output_str.find("Иван Иванов") != std::string::npos) << "Output missing 'Иван Иванов'";
    EXPECT_TRUE(output_str.find("Информатика") != std::string::npos) << "Output missing 'Информатика'";
}

TEST(FunctionTesting, SearchNameNotFound) {
    auto database = createTestDatabase();
    std::stringstream input;
    input << "\nНеизвестный\n"; // Начальный \n для ignore
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    searchName(database);
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("не найден") != std::string::npos) << "Output missing 'не найден'";
}

TEST(FunctionTesting, SearchSpecFound) {
    auto database = createTestDatabase();
    std::stringstream input;
    input << "\nИнформатика\n"; // Начальный \n для ignore
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    searchSpec(database);
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    std::string output_str = output.str();
    EXPECT_TRUE(output_str.find("Иван Иванов") != std::string::npos) << "Output missing 'Иван Иванов'";
    EXPECT_TRUE(output_str.find("Мария Козлова") != std::string::npos) << "Output missing 'Мария Козлова'";
}

TEST(FunctionTesting, SearchSpecNotFound) {
    auto database = createTestDatabase();
    std::stringstream input;
    input << "\nХимия\n"; // Начальный \n для ignore
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    searchSpec(database);
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("не найден") != std::string::npos) << "Output missing 'не найден'";
}

TEST(FunctionTesting, LoadStudentsSuccess) {
    std::ofstream file("test.txt");
    file << "Иван Иванов 20 Информатика 4.5\n";
    file.close();
    std::vector<Student> database;
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    loadStudents(database, "test.txt");
    std::cout.rdbuf(old_cout);
    ASSERT_EQ(database.size(), 1) << "Database size should be 1";
    EXPECT_EQ(database[0].name, "Иван Иванов") << "Name mismatch";
    EXPECT_EQ(database[0].age, 20) << "Age mismatch";
    EXPECT_EQ(database[0].major, "Информатика") << "Major mismatch";
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5) << "GPA mismatch";
}

TEST(FunctionTesting, LoadStudentsFileNotFound) {
    std::vector<Student> database;
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    loadStudents(database, "nonexistent.txt");
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("Не удалось открыть файл") != std::string::npos) << "Output missing 'Не удалось открыть файл'";
    EXPECT_EQ(database.size(), 0) << "Database size should be 0";
}

TEST(FunctionTesting, LoadStudentsInvalidLine) {
    std::ofstream file("test.txt");
    file << "Иван Иванов 20 Информатика\n";
    file.close();
    std::vector<Student> database;
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
    loadStudents(database, "test.txt");
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("Ошибка чтения строки") != std::string::npos) << "Output missing 'Ошибка чтения строки'";
    EXPECT_EQ(database.size(), 0) << "Database size should be 0";
}

TEST(FunctionTesting, MainMenuInvalidInput) {
    std::stringstream input;
    input << "invalid\n0\n";
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());
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
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    EXPECT_TRUE(output.str().find("Неверный ввод") != std::string::npos) << "Output missing 'Неверный ввод'";
    EXPECT_TRUE(output.str().find("Выход...") != std::string::npos) << "Output missing 'Выход...'";
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
