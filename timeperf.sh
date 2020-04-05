#!/bin/bash

INPUTFILE=/Volumes/ramdisk/randomdata.dat
ITER=5
RESULTS=results.txt
CIPHERS="des-ecb des-ede aes-128-ecb aes-256-ecb bf-ecb des-cbc des-ede-cbc aes-128-cbc aes-256-cbc bf-cbc"

# compute the size of the file with random content
# as stat syntax on macOS is different than Linux
# check the OS
if [ "$(uname)" = "Darwin" ]; then
  FILESIZE=$(echo "$(stat -f %z $INPUTFILE) * 8" | bc)
else
  FILESIZE=$(echo "$(stat -c %s $INPUTFILE) * 8" | bc)
fi

# remove results file if exists
if [ -f $RESULTS ]; then
  rm $RESULTS
fi

# generate a temporary file for storing results
TMPOUTPUT=$(mktemp)

# repeat the experiment for each cipher
for cipher in $CIPHERS ; do
  echo "doing $cipher"

  # if the temporary file exists, remove it
  if [ -f $TMPOUTPUT ]; then
    rm $TMPOUTPUT
  fi

  # repeat the experiment a number of times
  for loop in $(seq 1 $ITER); do
    echo "iteration ${loop}/${ITER}"
    { time -p openssl enc -$cipher -in $INPUTFILE -K deadbeefdeadbeef -iv 24 > /dev/null ;} \
	2>&1 | grep -v real | awk '{ print $2 }' | paste -sd+ - | bc -l >> $TMPOUTPUT
  done
  SUM=$(cat $TMPOUTPUT | paste -sd+ - | bc -l)
  AVERAGE=$(echo "scale=3;$FILESIZE / $SUM * $ITER" | bc -l)
  echo "$cipher $AVERAGE" | tee -a $RESULTS
  echo ""
done

echo "Results:"
cat $RESULTS
