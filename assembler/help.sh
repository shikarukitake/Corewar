#!/bin/sh

SUBJECT_ASM=subject_resources/asm
MY_ASM=./asm
VALGRIND_MY_ASM="valgrind --log-file="valgrindout" ./asm"
if [ $# -eq 1 ]
then
  SUBSTR=$(echo "$1" | cut -d'.' -f 1)
  NAME=${SUBSTR}.cor
  NAME_COPY=${SUBSTR}_copy.cor
  make
  echo "\033[1;34mMY ASM:\033[0m"
  $MY_ASM "$1"
  if [ $? -eq 0 ]; then
    cp "$NAME" "$NAME_COPY"
    echo "\033[1;34mSUBJECT ASM:\033[0m"
    $SUBJECT_ASM "$1"
    echo "\033[1;34mDIFF:\033[0m"
    diff $NAME $NAME_COPY
    xxd $NAME > bin_temp1
    xxd $NAME_COPY > bin_temp2
    diff bin_temp1 bin_temp2
    rm bin_temp1 bin_temp2
  else
      echo "\033[1;34mSUBJECT ASM:\033[0m"
      $SUBJECT_ASM "$1"
  fi
elif [ $# -eq 2 ]
then
  if [ "$2" = "-v" ]
  then
    SUBSTR=$(echo "$1" | cut -d'.' -f 1)
    NAME=${SUBSTR}.cor
    NAME_COPY=${SUBSTR}_copy.cor
    make
    echo "\033[1;34mMY ASM:\033[0m"
    $VALGRIND_MY_ASM "$1"
    echo valgrindout | grep lost
    rm valgrindout
    if [ $? -eq 0 ]; then
      cp "$NAME" "$NAME_COPY"
      echo "\033[1;34mSUBJECT ASM:\033[0m"
      $SUBJECT_ASM "$1"
      echo "\033[1;34mDIFF:\033[0m"
      diff $NAME $NAME_COPY
      xxd $NAME > bin_temp1
      xxd $NAME_COPY > bin_temp2
      diff bin_temp1 bin_temp2
      rm bin_temp1 bin_temp2
    else
        echo "\033[1;34mSUBJECT ASM:\033[0m"
        $SUBJECT_ASM "$1"
    fi
  else
    echo "USAGE: ./help.sh map [-v]"
  fi
else
  echo "USAGE: ./help.sh map [-v]"
fi