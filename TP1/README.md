# CPAR
Repository for the Parallel Computing class at FEUP.

## TP1

### Project setup

#### PAPI (Performance Application Programming Interface)

* Download the tar.gz for PAPI from [here](http://icl.cs.utk.edu/papi/software/)

* Extract the folder in whichever directory you want

* Go to the /src directory in the PAPI folder:
  * ```sh cd YourPathName/PAPI/src ```

* Run the commands:
  * ```sh ./configure ```
  * ```sh make ```
  * ```sh sudo make install ```
  * ```sh make test ```
  * ```sh sudo ldconfig ```

* Install the PAPI tools:
  * ```sh sudo apt-get install papi-tools ```

* Compile your CPP file (by default, matrixProd.cpp):
  * ```sh g++ -o YourExecutableName -fopenmp "YourCPPSourceName.cpp" -lpapi ```

* Run your executable and follow the on-screen instructions:
  * ```sh ./YourExecutableName ```