/* 
Assignment 2: Marriage Pact

This assignment asks you to discover your one true love using containers and pointers.
There are two parts: implement get_applicants and find_matches.

Submit to Paperless by 11:59pm on 2/1/2024.
*/

#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_set>

std::string STUDENT_TXT_PATH = R"(D:\ComputerScience\C++\MarriagePact\students.txt)";

std::string get_initials(const std::string& name) {
    std::string initials;
    initials += static_cast<char>(std::toupper(name[0])); // Add the first character of the name

    // Find the position of the space and add the character after it
    size_t space_pos = name.find(' ');
    if (space_pos != std::string::npos && space_pos + 1 < name.size()) {
        initials += static_cast<char>(std::toupper(name[space_pos + 1]));
    }

    return initials;
}

std::string* get_random_student(std::queue<std::string*>& students) {
    if (students.empty()) {
        return nullptr; // Return null if the queue is empty
    }

    std::random_device rd; // random seed
    std::mt19937 gen(rd());// random number generator
    std::uniform_int_distribution<> dis(0, static_cast<int>(students.size()) - 1);

    int random_index = dis(gen);

    for (int i = 0; i < random_index; ++i) {
        students.push(students.front());
        students.pop();
    }

    return students.front();
}

std::unordered_set<std::string> get_applicants(const std::string &filename) {
    // TODO: Implement this function. Feel free to change std::set to std::unordered_set if you wish!
    // parse all of the names into a set
    std::ifstream inFile(filename);
    std::unordered_set<std::string> names;
    std::string line;

    while (std::getline(inFile, line)) {
        names.insert(line);
        // As you add names to your set, print them out to the console
        // std::cout << line << std::endl;
    }
    return names;
}

std::queue<std::string *> find_matches(std::unordered_set<std::string> &students, const std::string &name) {
    // TODO: Implement this function.
    // take all names that share your initials and place pointers to them in a new std::queue.
    std::queue<std::string *> matches;
    for(const auto & student : students) {
        // compare initials
        if (get_initials(student) == get_initials(name)) {
            matches.push(&const_cast<std::string &>(student));
        }
    }
    return matches;

}


int main() {
    // Your code goes here. Don't forget to print your true love!
    std::string name;

    std::cout << "Enter your Name format as : John Lennon" << std::endl;
    std::getline(std::cin, name);
    std::cout << "The initials of " << name << " are " << get_initials(name) << std::endl;

    std::unordered_set<std::string> students = get_applicants(STUDENT_TXT_PATH);
    std::queue<std::string *> matches = find_matches(students, name);
    // choose some method of acquiring one student from the queue, random select one student from the queue

    std::string* true_love = get_random_student(matches);
    if (true_love != nullptr) {
        std::cout << "Your one true match is: " << *true_love << std::endl;
    } else {
        std::cout << "No match found." << std::endl;
    }

    return 0;
}
