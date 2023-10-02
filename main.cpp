#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cmath>

using namespace std;

string intToBinary(int num)
{
    bitset<8> binary(num);
    
    return binary.to_string();
}

string binaryToHex(const string &binary)
{
    bitset<8> bits(binary);
    stringstream stream;
    stream << hex << bits.to_ulong();
    
    return stream.str();
}

void processBlock(const string &block, int unicodeValue, int bitCount, string &output)
{
    vector<string> subblocks;
    output.clear();

    size_t blockSize = (block.size() == 256) ? 64 : 256;
    for (size_t i = 0; i < block.size(); i += blockSize)
    {
        string subblock = block.substr(i, blockSize);
        subblocks.push_back(subblock);
    }

    for (const string &subblock : subblocks)
    {
        string shiftedSubblock;
        int value = (unicodeValue / 13 + bitCount) % 5;
        for (size_t i = 0; i < subblock.size(); i += 18)
        {
            string subblockPart = subblock.substr(i, 18);
            int shiftAmount = i % 8 + value;
            string shiftedPart = subblockPart.substr(shiftAmount) + subblockPart.substr(0, shiftAmount);
            shiftedSubblock += shiftedPart;
        }

        vector<string> nibbles;
        // 64bit sukarpymas į 16x4bit
        for (size_t i = 0; i < shiftedSubblock.size(); i += 4)
        {
            string nibble = shiftedSubblock.substr(i, 4);
            nibbles.push_back(nibble);
        }
        for (const string &nibble : nibbles)
        {
            string hexNibble = binaryToHex(nibble);
            output += hexNibble;
        }
    }
}

int main()
{
    int unicodeValue = 0;
    int choice;
    cout << "Pasirinkite: 1 - įvedimas ranka, 2 - skaitymas iš failo: ";
    cin >> choice;

    string input;
    if (choice == 1)
    {
        cout << "Įveskite žodį, kurį norite užkoduoti: " << endl;
        cin >> input;
    }
    else if (choice == 2)
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
        
        string eilute;
        while (getline(inputFile, eilute))
            input += eilute;
        inputFile.close();
    }

    int bitCount1 = input.size() * 8;
    int bitCount = input.size();

    for (int i = 0; i < input.size(); i++){

        if(i == input.size() / 2)
            unicodeValue += static_cast<int>(input[i]) * 17;

        unicodeValue += static_cast<int>(input[i]);
    }

    int targetBitCount = (bitCount1 < 256) ? 256 : ((bitCount1 / 256) + 1) * 256;

    string binaryInput;
    for (char c : input)
    {
        bitset<8> binaryChar(c);
        binaryInput += binaryChar.to_string();
    }

    int number = bitCount;

    while (binaryInput.size() < targetBitCount)
    {
        binaryInput += intToBinary(number);
        number += bitCount + static_cast<int>(input[0]);
    }

    vector<string> blocks;
    for (size_t i = 0; i < input.size(); i += 256)
    {
        string block = binaryInput.substr(i, 256);
        blocks.push_back(block);
    }

    string output;

    for (const string &block : blocks)
    {
        int blockBitCount = block.size();

        processBlock(block, unicodeValue, bitCount, output);
    }

    cout << "Rezultatas (hexadecimal): " << output << endl;

    blocks.clear();

    return 0;
}
