# 1-oji užduotis: Hash funkcijos generatoriaus kūrimas

## v0.1.1 pseudo-kodas:

```
START

Function generateRandomLine()
    unique = False
    hexResult = ""

    WHILE not unique
        randomBinaryString = ""

        Initialize random device and generator
        distribution = Uniform distribution between 0 and 1

        WHILE length of randomBinaryString < 256
            randomBit = Generate a random bit using distribution
            Append randomBit to randomBinaryString

        // Divide the 256-bit binary code into 4 parts of 64 bits each
        FOR i FROM 0 TO 3
            binaryChunk = Substring of randomBinaryString from i * 64 to (i + 1) * 64
            Convert binaryChunk to a 64-bit unsigned integer (chunkValue)
            Convert chunkValue to a 16-character hexadecimal string (hexBuffer)
            Append hexBuffer to hexResult

        Open "output_archive.txt" file
        exists = False
        existingContent = ""

        WHILE there are lines in the file
            IF existingContent is equal to hexResult
                exists = True
                Exit loop

        Close the file

        IF not exists
            unique = True

    Return hexResult

Main Function
    userInput = Input from the user
    Display "Select the file you want to work with: "

    Display the list of ".txt" files in the directory

    Read userInput from the user

    Open inputFile using userInput

    IF failed to open the file
        Print an error message
        Exit with code 1

    visaEilute = ""

    WHILE there are lines in inputFile
        Concatenate the line to visaEilute

    rastas = False

    Open "input_archive.txt" and "output_archive.txt" files

    IF failed to open one or both files
        Print an error message
        Exit with code 1

    WHILE there are lines in both inputArchive and outputArchive files
        IF eiluteIsArchyvo is equal to visaEilute
            rastas = True
            Display "Found output: " + rastasOutputas
            Exit loop

    IF not rastas
        Close inputArchive and outputArchive

        Open "input_archive.txt" and "output_archive.txt" files for appending

        IF failed to open one or both files
            Print an error message
            Exit with code 1

        Append visaEilute to inputArchive

        naujasOutputas = Call generateRandomLine()

        Append naujasOutputas to outputArchive

        Display "New output: " + naujasOutputas

Exit with code 0
```
