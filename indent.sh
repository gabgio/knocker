#!/bin/sh

SECONDS=10

echo
echo Warning, you are about to change source code indentation !
echo executing in $SECONDS seconds, press ctrl + c to abort.

for (( i=0 ; $i <= (SECONDS=$SECONDS-1) ; i=$i+1 ))
do  
  sleep 1 
  echo -n ". "
done

echo

indent --indent-level2 --line-length140 --comment-line-length140 \
--no-blank-lines-after-declarations --no-blank-lines-after-procedures \
--dont-break-function-decl-args --dont-break-procedure-type \
-nut --space-after-if  src/*.c

# -nut = --no-tabs ( but --not-tabs is not working -nut does work ) 

echo Source code indentation complete.





