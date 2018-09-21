#!/bin/sh
MINE=dcc
GIVEN=dcc_solution

./$MINE <$1 &>temp.$MINE
./$GIVEN <$1 &>temp.$GIVEN
diff -w temp.$MINE temp.$GIVEN

rm temp.$MINE temp.$GIVEN
