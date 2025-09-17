#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <gtest/gtest.h>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void loadStudents(std::vector<Student>& database, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.name >> student.age >> student.major >> student.gpa) {
            database.push_back(student);
        }
    }
    file.close();
}

void addStudent(std::vector<Student>& database, const std::string& name, int age, 
                const std::string& major, double gpa) {
    Student student;
    student.name = name;
    student.age = age;
    student.major = major;
    student.gpa = gpa;
    database.push_back(student);
}

void displayStudents(const std::vector<Student>& database) {
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

bool searchName(const std::vector<Student>& database, const std::string& name) {
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
    return found;
}

bool searchSpec(const std::vector<Student>& database, const std::string& spec) {
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
    return found;
}

TEST(LoadStudentsTest, LoadsValidFile) {
    std::vector<Student> database;
    // создаем тестовый файл 
    std::ofstream testFile("test.txt");
    testFile << "Иван_Иванов 20 Информатика 4.5\n";
    testFile << "Анна_Петрова 21 Математика 4.8\n";
    testFile.close();
    
    // загружаем студентов из файла в вектор
    loadStudents(database, "test.txt");
    // проверяем, что в векторе 2 студента
    ASSERT_EQ(database.size(), 2);
    // проверяем, что имя первого студента ива
    EXPECT_EQ(database[0].name, "Иван_Иванов");
    // проверяем, что возраст первого студента 
    EXPECT_EQ(database[0].age, 20);
    // проверяем, что специальность первого студента инфа
    EXPECT_EQ(database[0].major, "Информатика");
    // проверяем, что средний балл первого студента 
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(LoadStudentsTest, HandlesNonExistentFile) {
    // создаем пустой вектор 
    std::vector<Student> database;
    // пытаемся загрузить студентов из несуществующего файла
    loadStudents(database, "nonexist.txt");
    // проверяем, что вектор остался пустым
    ASSERT_TRUE(database.empty());
}

TEST(AddStudentTest, AddsValidStudent) {
    // создаем пустой вектор для студентов
    std::vector<Student> database;
    // добавляем студента в вектор
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    
    // проверяем, что в векторе 1 
    ASSERT_EQ(database.size(), 1);
    // проверяем, что имя студента нужное
    EXPECT_EQ(database[0].name, "Иван_Иванов");
    // проверяем, что возраст студента 20
    EXPECT_EQ(database[0].age, 20);
    // проверяем, что специальность студента инфа
    EXPECT_EQ(database[0].major, "Информатика");
    // проверяем, что средний балл студента нужный
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(SearchNameTest, FindsExistingStudent) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    // перехватываем вывод в консоль
    testing::internal::CaptureStdout();
    // ищем студента по имени
    bool found = searchName(database, "Иван_Иванов");
    // получаем  вывод
    std::string output = testing::internal::GetCapturedStdout();
    
    // проверяем, что студент найден
    EXPECT_TRUE(found);
    // проверяем, что в выводе есть имя Иван_Иванов
    EXPECT_NE(output.find("Имя: Иван_Иванов"), std::string::npos);
}

TEST(SearchNameTest, HandlesNonExistentStudent) {
    // создаем пустой вектор для студентов
    std::vector<Student> database;
    // добавляем студента в вектор
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    // перехватываем вывод в консоль
    testing::internal::CaptureStdout();
    // ищем несуществующего студента
    bool found = searchName(database, "Анна_Петрова");
    // получаем  вывод
    std::string output = testing::internal::GetCapturedStdout();
    
    // проверяем, что студент не найден
    EXPECT_FALSE(found);
}

TEST(SearchSpecTest, FindsExistingMajor) {
    // создаем пустой вектор для студентов
    std::vector<Student> database;
    // добавляем студента в вектор
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    // перехватываем вывод в консоль
    testing::internal::CaptureStdout();
    // ищем студентов по специальности
    bool found = searchSpec(database, "Информатика");
    // получаем  вывод
    std::string output = testing::internal::GetCapturedStdout();
    
    // проверяем, что специальность есть
    EXPECT_TRUE(found);
    // проверяем, что в выводе есть специальность инфа
    EXPECT_NE(output.find("Специальность: Информатика"), std::string::npos);
}

TEST(SearchSpecTest, HandlesNonExistentMajor) {
    // создаем пустой вектор для студентов
    std::vector<Student> database;
    // добавляем студента в вектор
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    // перехватываем вывод в консоль
    testing::internal::CaptureStdout();
    // ищем несуществующую специальность
    bool found = searchSpec(database, "Математика");
    // получаем  вывод
    std::string output = testing::internal::GetCapturedStdout();
    
    // проверяем, что специальность не найдена
    EXPECT_FALSE(found);
}

TEST(DisplayStudentsTest, DisplaysCorrectly) {
    // создаем пустой вектор для студентов
    std::vector<Student> database;
    // добавляем студента в вектор
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    // выводим список студентов
    displayStudents(database);
    // получаем  вывод
    std::string output = testing::internal::GetCapturedStdout();
    
    // проверяем, что в выводе есть имя ива
    EXPECT_NE(output.find("Имя: Иван_Иванов"), std::string::npos);
    // проверяем, что в выводе есть возраст 20
    EXPECT_NE(output.find("Возраст: 20"), std::string::npos);
    // проверяем, что в выводе есть специальность инфа
    EXPECT_NE(output.find("Специальность: Информатика"), std::string::npos);
    // проверяем, что в выводе есть средний балл
    EXPECT_NE(output.find("Средний балл: 4.5"), std::string::npos);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
