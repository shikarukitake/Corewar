#!/bin/sh

# FILES="./$1*"
# for f in $FILES
# do
#   echo $f
# done

SUBJECT_ASM=subject_resources/asm
MY_ASM=./asm
VALGRIND_MY_ASM="valgrind ./asm"
if [ $# -eq 1 ]
then
    FILES="./$1*"
    make
    for f in $FILES
    do
        echo "\n\033[1;35m$f:\033[0m"
        SUBSTR=$(echo "$f" | cut -d'.' -f 2)
        NAME=.${SUBSTR}.cor
        NAME_COPY=.${SUBSTR}_copy.cor
        echo "\033[1;34mMY ASM:\033[0m"
        $MY_ASM "$f"
        if [ $? -eq 0 ]; then
            cp "$NAME" "$NAME_COPY"
            echo "\033[1;34mSUBJECT ASM:\033[0m"
            $SUBJECT_ASM "$f"
            echo "\033[1;34mDIFF:\033[0m"
            diff $NAME $NAME_COPY
            xxd $NAME > bin_temp1
            xxd $NAME_COPY > bin_temp2
            diff bin_temp1 bin_temp2
            rm bin_temp1 bin_temp2
            rm $NAME $NAME_COPY
        else
            echo "\033[1;34mSUBJECT ASM:\033[0m"
            $SUBJECT_ASM "$f"
        fi
    done
elif [ $# -eq 2 ]
then
    if [ "$2" = "-v" ]
    then
        FILES="./$1*"
        for f in $FILES
        do
            echo "\n\033[1;35m$f:\033[0m"
            SUBSTR=$(echo "$f" | cut -d'.' -f 2)
            NAME=.${SUBSTR}.cor
            NAME_COPY=.${SUBSTR}_copy.cor
            make
            echo "\033[1;34mMY ASM:\033[0m"
            $VALGRIND_MY_ASM "$f"
            if [ $? -eq 0 ]; then
            cp "$NAME" "$NAME_COPY"
            echo "\033[1;34mSUBJECT ASM:\033[0m"
            $SUBJECT_ASM "$f"
            echo "\033[1;34mDIFF:\033[0m"
            diff $NAME $NAME_COPY
            xxd $NAME > bin_temp1
            xxd $NAME_COPY > bin_temp2
            diff bin_temp1 bin_temp2
            rm bin_temp1 bin_temp2
            rm $NAME $NAME_COPY
            else
                echo "\033[1;34mSUBJECT ASM:\033[0m"
                $SUBJECT_ASM "$f"
            fi
        done
    else
        echo "USAGE: ./help.sh map_folder [-v]"
    fi
else
    echo "USAGE: ./help.sh map_folder [-v]"
fi