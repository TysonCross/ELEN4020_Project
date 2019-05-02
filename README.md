#ELEN4020 Project
**Data Intensive Computing for Data Science**

***Tyson Cross      1239448*** <br>
***Michael Nortje   1389486*** <br>
**Joshua Isserow      675720** <br>

Source repository: <i>https://github.com/TysonCross/ELEN4020_Project.git<i>
## Build and Run Instructions
The code requires the OpenMP libraries, and the g++ compiler to be installed. We suggest using [CMake](https://cmake.org/) to build the executable. Download the [latest release](https://cmake.org/download/), or install with a package manager.

Once CMake is installed, run the following from the location where this git repo was cloned to:
<pre><code>$ mkdir build
$ cd build
$ cmake ..
$ make
</code></pre>

// Instructions HERE

### Additional Notes
Please make sure that your ENV variable OMP\_NUM\_THREADS is set to a sensible value (we suggest 8 for a 4-core machine with hyperthreading). You can check the value with
<pre><code>$ echo $OMP\_NUM\_THREADS</code></pre>
and set it with
<pre><code>$ export $OMP\_NUM\_THREADS=8</code></pre>

<br>
<i>Addtional commandline options:<i>

