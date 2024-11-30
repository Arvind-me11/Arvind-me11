#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void listFiles(const std::string& path) {
    std::cout << "Contents of directory: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << "\n";
    }
}

void createDirectory(const std::string& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created: " << path << "\n";
    } else {
        std::cerr << "Failed to create directory: " << path << "\n";
    }
}

void viewFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        std::cout << "Contents of file " << filepath << ":\n";
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filepath << "\n";
    }
}

void copyFile(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied to: " << destination << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved to: " << destination << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error moving file: " << e.what() << "\n";
    }
}

int main() {
    std::string currentPath = fs::current_path().string();
    int choice;

    while (true) {
        std::cout << "\nBasic File Manager\n";
        std::cout << "Current Directory: " << currentPath << "\n";
        std::cout << "1. List Files\n";
        std::cout << "2. Create Directory\n";
        std::cout << "3. View File\n";
        std::cout << "4. Copy File\n";
        std::cout << "5. Move File\n";
        std::cout << "6. Change Directory\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string path, source, destination;

        switch (choice) {
        case 1:
            listFiles(currentPath);
            break;
        case 2:
            std::cout << "Enter directory name to create: ";
            std::cin >> path;
            createDirectory(currentPath + "/" + path);
            break;
        case 3:
            std::cout << "Enter file name to view: ";
            std::cin >> path;
            viewFile(currentPath + "/" + path);
            break;
        case 4:
            std::cout << "Enter source file name: ";
            std::cin >> source;
            std::cout << "Enter destination file name: ";
            std::cin >> destination;
            copyFile(currentPath + "/" + source, currentPath + "/" + destination);
            break;
        case 5:
            std::cout << "Enter source file name: ";
            std::cin >> source;
            std::cout << "Enter destination file name: ";
            std::cin >> destination;
            moveFile(currentPath + "/" + source, currentPath + "/" + destination);
            break;
        case 6:
            std::cout << "Enter directory to change to: ";
            std::cin >> path;
            if (fs::is_directory(path)) {
                currentPath = path;
            } else {
                std::cerr << "Invalid directory.\n";
            }
            break;
        case 7:
            std::cout << "Exiting File Manager. Goodbye!\n";
            return 0;
        default:
            std::cerr << "Invalid choice. Please try again.\n";
        }
    }
}
