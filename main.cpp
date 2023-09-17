#include "mylib.h"
#include "funkcijos.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    string userInput;
    map<string, string> codeMap = loadData();

    while (true)
    {
        cout << "Įveskite žodį, kurį norite užkoduoti (įveskite '.' norėdami baigti): ";
        cin >> userInput;

        if (userInput == ".")
        {
            saveData(codeMap);
            break;
        }

        // Tikrinimas, ar toks žodis yra jau žemėlapyje
        if (codeMap.find(userInput) != codeMap.end())
            cout << "Rezultatas: " << codeMap[userInput] << endl;

        else
        {
            string code;

            // Kartojama, kol sugeneruojamas unikalus rezultatas
            do
            {
                code = generateRandomCode();
            } while (codeMap.find(code) != codeMap.end());

            codeMap[userInput] = code;
            cout << "Rezultatas: " << code << endl;
        }
    }

    return 0;
}
