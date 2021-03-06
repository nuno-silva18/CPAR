# CPAR
Repository for the Parallel Computing class at FEUP.

## TP1

### Project setup

#### PAPI (Performance Application Programming Interface)

* Download the tar.gz for PAPI from [here](http://icl.cs.utk.edu/papi/software/)

* Extract the folder in whichever directory you want

* Go to the /src directory in the PAPI folder:
  * ```cd YourPathName/PAPI/src```

* Run the commands:
  * ```./configure```
  * ```make```
  * ```sudo make install```
  * ```make test```
  * ```sudo ldconfig```

* Install the PAPI tools:
  * ```sudo apt-get install papi-tools```

* Compile your CPP file (by default, matrixProd.cpp):
  * ```g++ -o YourExecutableName -fopenmp "YourCPPSourceName.cpp" -lpapi```

* Run your executable and follow the on-screen instructions:
  * ```./YourExecutableName```