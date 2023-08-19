#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Book {
public:
    std::string title;
    std::string author;
    int year;

    Book(const std::string& _title, const std::string& _author, int _year)
        : title(_title), author(_author), year(_year) {}
};

class Library {
private:
    std::vector<Book> books;
    const std::string filename = "library.txt";

public:
    void addBook(const Book& book) {
        books.push_back(book);
        saveToFile();
    }

    void listBooks() {
        for (const Book& book : books) {
            std::cout << "Title: " << book.title << ", Author: " << book.author << ", Year: " << book.year << std::endl;
        }
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for writing." << std::endl;
            return;
        }

        for (const Book& book : books) {
            file << book.title << "|" << book.author << "|" << book.year << "\n";
        }

        std::cout << "Library data saved to " << filename << std::endl;
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);

            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                std::string title = line.substr(0, pos1);
                std::string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int year = std::stoi(line.substr(pos2 + 1));
                books.emplace_back(title, author, year);
            }
        }

        std::cout << "Library data loaded from " << filename << std::endl;
    }
};

int main() {
    Library library;
    library.loadFromFile();

    while (true) {
        std::cout << "Library Menu:" << std::endl;
        std::cout << "1. Add a Book" << std::endl;
        std::cout << "2. List Books" << std::endl;
        std::cout << "3. Quit" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string title, author;
            int year;

            std::cin.ignore(); 
            std::cout << "Enter book title: ";
            std::getline(std::cin, title);
            std::cout << "Enter author name: ";
            std::getline(std::cin, author);
            std::cout << "Enter publication year: ";
            std::cin >> year;

            library.addBook(Book(title, author, year));
        }
        else if (choice == 2) {
            library.listBooks();
        }
        else if (choice == 3) {
            library.saveToFile();
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
