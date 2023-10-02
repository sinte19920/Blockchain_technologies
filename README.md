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
