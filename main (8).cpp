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
    // ��������� ���� ��� ������
    setlocale(LC_ALL, "Ru");
    std::ifstream inputFile("text22.txt");
    if (!inputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }

    // ��������� ����� �� ����� � ������
    std::string text;
    std::string wordToAdd;
    std::cout << "������� ����� ��� ����������: ";
    std::cin >> wordToAdd;

    // ��������� ����� �� �����
    std::string line;
    while (std::getline(inputFile, line)) {
        text += line + "\n";
    }

    // ��������� ����
    inputFile.close();

    size_t pos = 0;
    size_t prev_pos = 0;
    // ������� ���������� ��������� ����� � ������ �����������
    while ((pos = text.find('.', prev_pos)) != std::string::npos) {
        auto str = text.substr(prev_pos, pos - prev_pos);
        size_t wordCount = wordCountInText(text.substr(prev_pos, pos - prev_pos), wordToAdd);
        for (size_t i = 0; i < wordCount; ++i) {
            // ��������� ����� � ����� �����������
            text.insert(pos, " ["+ wordToAdd + "]");
        }
        prev_pos = pos + wordCount * wordToAdd.size() + 4;
    }

    // ������� ����������� �����
    std::cout << "\n����������� �����:\n" << text << std::endl;

    // ��������� ���� ��� ������
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }

    // ���������� ����������� ����� � ����
    outputFile << text;

    // ��������� ����
    outputFile.close();

    return 0;
}
