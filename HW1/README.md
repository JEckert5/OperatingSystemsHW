# Compilation

Run 

    make hw

in the HW1 directory.
I compiled this on an Ubuntu Docker image so there shouldn't be any issues.

# Running

    ./producer & ./consumer &

# Expected output

Will print the random numbers produced by the producer, wait 1 second, then show the consumed numbers. They should match the produced numbers. 

Example:

    int produced was 25
    int produced was 40
    Producer Waiting...
    Int consumed was: 25
    Int consumed was: 40
    Consumer Waiting... 

# Other utils

    make clean

Removes the `procuder` and `consumer` executables.
