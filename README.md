# Adrian's autograder

## Who
By Adrian Frauca
adf73@georgetown.edu

## Why
Made for semi-manually evaluating student submissions for COSC1020 and COSC130 projects.

## How (to use)
* Populate "submissions" folder with student submissions.
* Run `./autograder`. If need to recompile, use the following command: ` g++ -std=c++17 autograder.cpp -o autograder -lstdc++fs`
* Inspect outputs directory for results of compiling and testing for each submission