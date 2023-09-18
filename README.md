# 1-oji užduotis: Hash funkcijos generatoriaus kūrimas

## v0.1 pseudo-kodas:

```
START
    Initialize random number generator with current time
    Declare string userInput
    Declare map<string, string> codeMap and load data from a file

    WHILE true
        Display "Įveskite žodį, kurį norite užkoduoti (įveskite '.' norėdami baigti): "
        Read userInput from user

        IF userInput is equal to "."
            Save codeMap to a file
            Exit loop
        END IF

        IF userInput exists in codeMap
            Display "Rezultatas:", codeMap[userInput]
        ELSE
            Declare string code

            REPEAT
                Generate a random code and store it in 'code'
            UNTIL code does not exist in codeMap

            Add userInput and code to codeMap
            Display "Rezultatas:", code
        END IF
    END WHILE
END
```
