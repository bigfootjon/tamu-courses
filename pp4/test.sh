#!/bin/sh
MINE=dcc
GIVEN=dcc_pp3

./$MINE <$1 &>temp.$MINE
./$GIVEN <$1 &>temp.$GIVEN
diff -w temp.$MINE temp.$GIVEN
result=$?

rm temp.$MINE temp.$GIVEN
exit $result
