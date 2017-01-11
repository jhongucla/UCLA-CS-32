#ifndef DELTA_INCLUDED
#define DELTA_INCLUDED

#include <iostream>

void createDelta(istream& oldf, istream& newf, ostream& deltaf);

bool applyDelta(istream& oldf, istream& deltaf, ostream& newf);

#endif // DELTA_INCLUDED
