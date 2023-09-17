
#include "funkcijos.h"

string generateRandomCode()
{
    const string characters = "abcdefghijklmnopqrstuvwxyz0123456789";
    string code;

    for (int i = 0; i < 64; i++)
    {
        int index = rand() % characters.length();
        code += characters[index];
    }

    return code;
}

void saveData(const map<string, string> &data)
{
    ofstream outputFile("data.txt");

    for (const auto &pair : data)
        outputFile << pair.first << " " << pair.second << endl;

    outputFile.close();
}

map<string, string> loadData()
{
    map<string, string> data;
    ifstream inputFile("data.txt");

    if (inputFile.is_open())
    {
        string word, code;

        while (inputFile >> word >> code)
            data[word] = code;

        inputFile.close();
    }

    return data;
}