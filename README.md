# Kemy : An AQM generator based on machine learning.

--------
Kemy is an offline machine learning algorithm.
This project is the training code of Kemy.

--------

Before run the training code, please make sure the following tools have been correctly installed in you running environment.
>**Required tools:**

* C++ 11 compiler (we use gcc 4.8)
* [Google Protocol Buffers](https://code.google.com/p/protobuf/)
* [Boost C++ libraries](http://www.boost.org/)

After the required tools have been installed, please follow the step below to reproduce the result.
>**steps:**

 1. ``` git clone https://github.com/jkemy/Kemy-training.git ```
 2. ``` cd kemy-clear ```
 3. ``` ./autogen.sh ```
 4. ``` ./configure ```
 5. ``` make ```
 6. ``` cd src ```
 7. if successful,you can run kemy now:
    ```./kemy ```

