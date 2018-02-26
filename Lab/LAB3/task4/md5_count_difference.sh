#!/bin/bash

# This is bash!! do not run it using "sh"!
 
# set the file which we want to hash
FILE1="Testfile1"
FILE2="Testfile2"
# you also can try sha256 / md5
ENCRY="md5"

echo 'Running.. Please wait'

# upper case H1 and H2, for ibase/obase convertion
declare -u H1
declare -u H2

H1=`openssl dgst -$ENCRY $FILE1 | awk '{print $2}'`
H2=`openssl dgst -$ENCRY $FILE2 | awk '{print $2}'`

echo "The hash value (in HEX) of $FILE1 is $H1."
echo "The hash value (in HEX) of $FILE2 is $H2."

BITS1=`echo "ibase=16;obase=2;$H1" | bc`
BITS2=`echo "ibase=16;obase=2;$H2" | bc`

# now count how many bits are actually different (the "one" bits)
BITS1=`echo "$BITS1" | sed 's/\\\r*//g'`
BITS2=`echo "$BITS2" | sed 's/\\\r*//g'`

LEN=`expr length "$BITS1"`

COUNT=0
for i in `seq 1 $LEN`
do
    B1=$(echo $BITS1 | awk "{print substr (\$0, $i, 1)}")
    B2=$(echo $BITS2 | awk "{print substr (\$0, $i, 1)}")
    if [ "$B1" -ne "$B2" ]; then
        COUNT=`expr $COUNT + 1`
    fi
done
 
echo "$COUNT bits are different."