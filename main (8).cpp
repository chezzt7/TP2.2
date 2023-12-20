#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

size_t wordCountInText(std::string str, std::string& word) {
    size_t count = 0;
    size_t pos = 0;
    while ((pos = str.find(word, pos)) != std::string::npos) {
        ++count;
        pos += word.length();
    }
    return count;
}


int main() {
    // Открываем файл для чтения
    setlocale(LC_ALL, "Ru");
    std::ifstream inputFile("text22.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для чтения!" << std::endl;
        return 1;
    }

    // Считываем текст из файла в строку
    std::string text;
    std::string wordToAdd;
    std::cout << "Введите слово для добавления: ";
    std::cin >> wordToAdd;

    // Считываем текст из файла
    std::string line;
    while (std::getline(inputFile, line)) {
        text += line + "\n";
    }

    // Закрываем файл
    inputFile.close();

    size_t pos = 0;
    size_t prev_pos = 0;
    // Подсчет количества вхождений слова в каждом предложении
    while ((pos = text.find('.', prev_pos)) != std::string::npos) {
        auto str = text.substr(prev_pos, pos - prev_pos);
        size_t wordCount = wordCountInText(text.substr(prev_pos, pos - prev_pos), wordToAdd);
        for (size_t i = 0; i < wordCount; ++i) {
            // Добавляем слово в конец предложения
            text.insert(pos, " ["+ wordToAdd + "]");
        }
        prev_pos = pos + wordCount * wordToAdd.size() + 4;
    }

    // Выводим обновленный текст
    std::cout << "\nОбновленный текст:\n" << text << std::endl;

    // Открываем файл для записи
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }

    // Записываем обновленный текст в файл
    outputFile << text;

    // Закрываем файл
    outputFile.close();

    return 0;
}
