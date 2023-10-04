# 1-oji užduotis: Hash funkcijos generatoriaus kūrimas

## v0.2 pseudo-kodas:

```
START

function intToBinary(num)
    binary = convert num to binary representation with 8 bits
    return binary as string

function binaryToHex(binary)
    bits = create bitset from binary
    hexValue = convert bits to decimal and then to hexadecimal
    return hexValue as string

function processBlock(block, unicodeValue, bitCount, output)
    subblocks = split block into subblocks of size 64 or 256
    output = ""

    for each subblock in subblocks
        value = (unicodeValue / 13 + bitCount) % 5
        shiftedSubblock = ""

        for i from 0 to subblock.size() step 18
            subblockPart = extract 18 bits from subblock starting at i
            shiftAmount = i % 8 + value
            shiftedPart = shift subblockPart circularly by shiftAmount
            shiftedSubblock += shiftedPart

        nibbles = split shiftedSubblock into 4-bit nibbles
        for each nibble in nibbles
            hexNibble = binaryToHex(nibble)
            output += hexNibble

function main()
    unicodeValue = 0
    choice = 0
    output = ""

    print "Pasirinkite: 1 - įvedimas ranka, 2 - skaitymas iš failo: "
    read choice

    if choice is 1
        print "Įveskite žodį, kurį norite užkoduoti:"
        read input
    else if choice is 2
        print "Pasirinkite, su kuriuo failu norite dirbti:"
        list all files with ".txt" extension
        read userInput

        open inputFile with userInput
        if inputFile does not exist
            print "Nepavyko atidaryti failo."
            exit

        if inputFile is empty
            print "Failas yra tuščias."

        while there are lines in inputFile
            read line from inputFile
            append line to input
        close inputFile

    bitCount1 = size of input * 8
    bitCount = size of input

    for i from 0 to size of input
        if i is half of size of input
            unicodeValue += ASCII value of input[i] multiplied by 17

        unicodeValue += ASCII value of input[i]

    targetBitCount = maximum of 256 and next multiple of 256 after bitCount1

    binaryInput = ""
    for each character c in input
        binaryChar = convert c to binary with 8 bits
        append binaryChar to binaryInput

    number = bitCount

    while size of binaryInput is less than targetBitCount
        binaryInput += intToBinary(number)
        number += bitCount + ASCII value of first character in input

    blocks = split binaryInput into blocks of size 256

    for each block in blocks
        blockBitCount = size of block
        processBlock(block, unicodeValue, bitCount, output)

    if output is not empty
        print "Rezultatas (hexadecimal):", output

Exit with code 0
```
# Eksperimentinis tyrimas ir rezultatų analizė

Testavimui naudoti tekstiniai failai:

* A.txt - vienas simbolis 'A'.
* B.txt - vienas simbolis 'B'.
* 1003.txt - 1003 atsitiktinai sugeneruoti simboliai.
* 2050.txt - 2050 atsitiktinai sugeneruoti simboliai.
* 1003x.txt - 1002 atsitiktinai sugeneruoti simboliai ir 502 vietoje 'x'.
* 1003y.txt - tokie patys 1002 simboliai, kaip '1003x.txt', tik 502 vietoje 'y'.
* tuscias.txt - tuščias failas.
* konstitucija.txt - Lietuvos Respublikos Konstitucija.
* poros10.txt - 25 000 atsitiktinai sugeneruotos 10 simbolių ilgio eilutės.
* poros100.txt - 25 000 atsitiktinai sugeneruotos 100 simbolių ilgio eilutės.
* poros500.txt - 25 000 atsitiktinai sugeneruotos 500 simbolių ilgio eilutės.
* poros1000.txt - 25 000 atsitiktinai sugeneruotos 1000 simbolių ilgio eilutės.
* diffsymb10.txt - 25 000 atsitiktinai sugeneruotos 10 simbolių ilgio eilutės, kurios porose skiriasi vienu (paskutiniu) simboliu.
* diffsymb100.txt - 25 000 atsitiktinai sugeneruotos 100 simbolių ilgio eilutės, kurios porose skiriasi vienu (paskutiniu) simboliu.
* diffsymb500.txt - 25 000 atsitiktinai sugeneruotos 500 simbolių ilgio eilutės, kurios porose skiriasi vienu (paskutiniu) simboliu.
* diffsymb1000.txt - 25 000 atsitiktinai sugeneruotos 1000 simbolių ilgio eilutės, kurios porose skiriasi vienu (paskutiniu) simboliu.


## Hash funkcijos veikimas:

|  Failo pavadinimas  |  Sugeneruota reikšmė                                               |
|---------------------|--------------------------------------------------------------------|
|    **A.txt**        |  82029c2e01293af19e22dcaea32b3af3be42dd2f452d3af5de62ddafe72f3af7  |
|    **B.txt**        |  0805487c1354a3245865c9fe795a232ab8c5cb7fdf60a33019260cf135662736  |
|    **1003.txt**     |  aacaacae49226a388242c849c927ebbab99ac72e8ab6acb15ac2ce6617ba292c  |
|    **2050.txt**     |  55217483d0d32515e5b536542dd617549db9673453964613354c6496ca1d264c  |
|    **1003x.txt**    |  77765ce5335531634c58751106a73295636d64c1f695458575666d54c7848a14  |
|    **1003y.txt**    |  eeecb9ca66aa62c698b0aa221d4e612bc6da8983fd2a8b0aeacc9aa99f091029  |
|    **tuscias.txt**  |  2001090da85a51ece809292da8daf3ecf011094df95b51edf819296df9dbf3ed  |

## Hash funkcijos efektyvumas:

<img width="906" alt="Screenshot 2023-10-04 at 13 47 53" src="https://github.com/sinte19920/Blockchain_technologies/assets/66333376/da0297b9-32c4-488e-b9ec-3311c5a9e39a">

<img width="430" alt="image" src="https://github.com/sinte19920/Blockchain_technologies/assets/66333376/5e3e3ace-84b1-4eb7-9d5a-74d423d99963">

## Hash funkcijos atsparumas kolizijai:

|  Failo pavadinimas  |  Kolizijų skaičius  |
|---------------------|---------------------|
|  **poros10.txt**    |          0          |
|  **poros100.txt**   |          0          |
|  **poros500.txt**   |          0          |
|  **poros1000.txt**  |          0          |

## Hash funkcijos lavinos efektas:

<img width="405" alt="Screenshot 2023-10-04 at 13 38 33" src="https://github.com/sinte19920/Blockchain_technologies/assets/66333376/0f333742-33aa-44fe-be8f-25c40591a020">

<img width="356" alt="Screenshot 2023-10-04 at 13 46 13" src="https://github.com/sinte19920/Blockchain_technologies/assets/66333376/6e13bc4b-83aa-450e-9a7d-ba551e3a80db">

## Išvados:
