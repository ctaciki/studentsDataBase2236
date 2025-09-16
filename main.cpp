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
    // Create a temporary test file
    std::ofstream testFile("test.txt");
    testFile << "Иван_Иванов 20 Информатика 4.5\n";
    testFile << "Анна_Петрова 21 Математика 4.8\n";
    testFile.close();
    
    loadStudents(database, "test.txt");
    ASSERT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Иван_Иванов");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(LoadStudentsTest, HandlesNonExistentFile) {
    std::vector<Student> database;
    loadStudents(database, "nonexistent.txt");
    ASSERT_TRUE(database.empty());
}

TEST(AddStudentTest, AddsValidStudent) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    
    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Иван_Иванов");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

TEST(SearchNameTest, FindsExistingStudent) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    bool found = searchName(database, "Иван_Иванов");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(found);
    EXPECT_NE(output.find("Имя: Иван_Иванов"), std::string::npos);
}

TEST(SearchNameTest, HandlesNonExistentStudent) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    bool found = searchName(database, "Анна_Петрова");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_FALSE(found);
}

TEST(SearchSpecTest, FindsExistingMajor) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    bool found = searchSpec(database, "Информатика");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(found);
    EXPECT_NE(output.find("Специальность: Информатика"), std::string::npos);
}

TEST(SearchSpecTest, HandlesNonExistentMajor) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    bool found = searchSpec(database, "Математика");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_FALSE(found);
}

TEST(DisplayStudentsTest, DisplaysCorrectly) {
    std::vector<Student> database;
    addStudent(database, "Иван_Иванов", 20, "Информатика", 4.5);
    testing::internal::CaptureStdout();
    displayStudents(database);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Имя: Иван_Иванов"), std::string::npos);
    EXPECT_NE(output.find("Возраст: 20"), std::string::npos);
    EXPECT_NE(output.find("Специальность: Информатика"), std::string::npos);
    EXPECT_NE(output.find("Средний балл: 4.5"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
