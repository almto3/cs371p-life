// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl

#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----------------------
    // Life<ConwayCell> 21x13
    // ----------------------

    cout << "*** Life<ConwayCell> 21x13 ***\n" << endl;
    /*
    Simulate 12 evolutions.
    Print every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    {
        Life<ConwayCell> l1(cin, 21, 13);
        l1.print(cout);
        for (int i = 1; i <= 12; i++) {
            l1.evolve_all();
            l1.print(cout);
        }
    }

    // ----------------------
    // Life<ConwayCell> 20x29
    // ----------------------

    cout << "*** Life<ConwayCell> 20x29 ***\n" << endl;
    /*
    Simulate 28 evolutions.
    Print every 4th grid (i.e. 0, 4, 8, ... 28)
    */
    {
        Life<ConwayCell> l2(cin, 20, 29);
        l2.print(cout);
        for (int i = 1; i <= 28; i++) {
            l2.evolve_all();
            if (i % 4 == 0)
                l2.print(cout);
        }
    }

    // -----------------------
    // Life<ConwayCell> 109x69
    // -----------------------

    cout << "*** Life<ConwayCell> 109x69 ***\n" << endl;
    /*
    Simulate 283 evolutions.
    Print the first 10 grids (i.e. 0, 1, 2, ... 9).
    Print the 283rd grid.
    Simulate 40 evolutions.
    Print the 323rd grid.
    Simulate 2177 evolutions.
    Print the 2500th grid.
    */
    {
        Life<ConwayCell> l3(cin, 109, 69);
        l3.print(cout);
        for (int i = 1; i <= 2500; i++) {
            l3.evolve_all();
            if (i < 10 || i == 283 || i == 323 || i == 2500)
                l3.print(cout);
        }
    }

    // -----------------------
    // Life<FredkinCell> 20x20
    // -----------------------

    cout << "*** Life<FredkinCell> 20x20 ***\n" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    {
        Life<FredkinCell> l4(cin, 20, 20);
        l4.print(cout);
        for (int i = 1; i <= 5; i++) {
            l4.evolve_all();
            l4.print(cout);
        }
    }

    // ----------------
    // Life<Cell> 20x20
    // ----------------

    cout << "*** Life<Cell> 20x20 ***\n" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    {
        Life<Cell> l5(cin, 20, 20);
        l5.print(cout);
        for (int i = 1; i <= 5; i++) {
            l5.evolve_all();
            l5.print(cout);
        }
    }

    return 0;
}
