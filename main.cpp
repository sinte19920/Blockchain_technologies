#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <random>

using namespace std;

string generuotiAtsitiktineEilute()
{
    bool unique = false;
    string hexResult = "";

    while(!unique){
        string randomBinaryString = "";

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, 1);

        while (randomBinaryString.length() < 256)
        {
            int randomBit = distribution(gen);
            randomBinaryString += to_string(randomBit);
        }

        // Suskirstomas 256bit bin kodas į 4 dalis po 64bit
        for (int i = 0; i < 4; ++i)
        {
            string binaryChunk = randomBinaryString.substr(i * 64, 64);
            // Konvertuojamas kiekvienas 64 bitų dalis į 16taini formatą
            bitset<64> bitset(binaryChunk);
            unsigned long long chunkValue = bitset.to_ullong();
            char hexBuffer[17];
            snprintf(hexBuffer, sizeof(hexBuffer), "%016llx", chunkValue);
            hexResult += hexBuffer;
        }
        ifstream file("output_archive.txt");
        bool exists = false;
        string existingContent;

        while (getline(file, existingContent))
        {
            if (existingContent == hexResult)
            {
                exists = true;
                break;
            }
        }
        file.close();

        if (!exists)
            unique = true;
    }
    return hexResult;
}

int main()
{
    string userInput;
    cout << "Pasirinkite, su kuriuo failu norite dirbti: " << endl;
    
    cout << endl;
    system("ls -1 *.txt");
    cout << endl;
    
    cin >> userInput;

    ifstream inputFile(userInput);

    if (!inputFile)
    {
        cerr << "Nepavyko atidaryti failo." << endl;
        return 1;
    }

    string visaEilute;

    string eilute;
    while (getline(inputFile, eilute))
    {
        visaEilute += eilute;
    }

    bool rastas = false;
    ifstream inputArchive("input_archive.txt");
    ifstream outputArchive("output_archive.txt");

    if (!inputArchive || !outputArchive)
    {
        cerr << "Nepavyko atidaryti archyvų failų." << endl;
        return 1;
    }

    string eiluteIsArchyvo;
    string rastasOutputas;

    while (getline(inputArchive, eiluteIsArchyvo) && getline(outputArchive, rastasOutputas))
    {
        if (eiluteIsArchyvo == visaEilute)
        {
            rastas = true;
            cout << "Rastas outputas: " << rastasOutputas << endl;
            break;
        }
    }

    if (!rastas)
    {
        inputArchive.close();
        outputArchive.close();

        ofstream inputArchiveAppend("input_archive.txt", ios::app);
        ofstream outputArchiveAppend("output_archive.txt", ios::app);

        if (!inputArchiveAppend || !outputArchiveAppend)
        {
            cerr << "Nepavyko atidaryti archyvų failų naujam rašymui." << endl;
            return 1;
        }

        inputArchiveAppend << visaEilute << endl;

        string naujasOutputas = generuotiAtsitiktineEilute();
        outputArchiveAppend << naujasOutputas << endl;

        cout << "Naujas outputas: " << naujasOutputas << endl;
    }

    return 0;
}
