#!/bin/sh

SUBJECT_ASM=subject_resources/asm
MY_ASM=./asm

if [ $# -eq 1 ]; then
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
    xxd temp.cor > bin_temp1
    xxd temp_copy.cor > bin_temp2
    diff bin_temp1 bin_temp2
    rm bin_temp1 bin_temp2
  else
      echo "\033[1;34mSUBJECT ASM:\033[0m"
      $SUBJECT_ASM "$1"
  fi
else
  echo "USAGE: ./help.sh map"
fi