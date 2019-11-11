# Breaking-RSA
### What is this?
The intention of this repository is to try and break RSA by brute force.
For `n=124822069` (a random large number):
 - The sequential program (`main.cpp`) is able to break it in approximately **10 seconds**.
 - The parallel program (`main.cu`) is able to break it in approximately **2 seconds**.

## Example
### Sequential
```
g++ main.cpp
./a.out 46054145 124822069
142857^3 = 46054145 (mod 124822069)
27549958^3 = 46054145 (mod 124822069)
97129254^3 = 46054145 (mod 124822069)
Execution finished in 10973ms
```
### Parallel

```
nvcc main.cu
./a.out 46054145 124822069
142857^3 = 46054145 (mod 124822069)
27549958^3 = 46054145 (mod 124822069)
97129254^3 = 46054145 (mod 124822069)
Execution finished in 2570ms
``` 
## Note
I'm a Java developer and pretty new to c++. If you notice anything in my code that's not a "best practice" or not the "c way of going things", please let me know by creating an issue or a pull request. I'll be very, very grateful.
