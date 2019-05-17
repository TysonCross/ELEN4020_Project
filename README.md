#ELEN4020 Project
**Data Intensive Computing for Data Science**

***Tyson Cross      1239448*** <br>
***Michael Nortje   1389486*** <br>
**Joshua Isserow      675720** <br>

Source repository: <i>https://github.com/TysonCross/ELEN4020_Project.git<i>
## Build and Run Instructions
The code requires the OpenMP libraries, and the g++ compiler to be installed, along with MPICH 3

Transfer the **src/** folder to the Jaguar cluster (dica01) and then compile the code:

<pre><code>$ mpicxx src/main.cpp src/transpose.cpp src/Matrix.h src/utilities.cpp -lstdc++ -o transpose</code></pre>


### Additional Notes
The code and batch files to compile and run the code are already installed in swbsutg08@dica01, using the default administrator provided password for the account.

simply run 
<pre><code>$ run_transpose [N] </code></pre>
(N must be a power of 2 greater than or equal to 4) <br>

You can also run a suite of sizes with 

<pre><code>$ run_transpose_short</code></pre>

or run a large number of tests, several times with 

<pre><code>$ run_transpose_long</code></pre>


