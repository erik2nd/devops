#!/bin/bash

SUCCESS=0
FAIL=0
TOTAL=600
DIFF_RES=""
RESULT=""
FILES="test.txt grep.c"
FLAGS="i v c l n h s o"
PATTERNS="word while"
FILE_PATTERN="patterns.txt"

testing() {
    ./s21_grep "$var" "$file" > "test_s21_grep.log"
    grep "$var" "$file" > "test_sys_grep.log"
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${SUCCESS}/${TOTAL}] ${RESULT}" grep "$var" "$file"
    rm test_s21_grep.log test_sys_grep.log
}

testing_multi() {
    ./s21_grep "$var" "$file11" "$file22" > "test_s21_grep.log"
    grep "$var" "$file11" "$file22" > "test_sys_grep.log"
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${SUCCESS}/${TOTAL}] ${RESULT}" grep "$var" "$file11" "$file22"
    rm test_s21_grep.log test_sys_grep.log
}

testing_file() {
    ./s21_grep "-f" "$FILE_PATTERN" "$var" "$file" > "test_s21_grep.log"
    grep "-f" "$FILE_PATTERN" "$var" "$file" > "test_sys_grep.log"
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${SUCCESS}/${TOTAL}] ${RESULT}" grep "-f" "$FILE_PATTERN" "$var" "$file"
    rm test_s21_grep.log test_sys_grep.log
}

# flag e

for file1 in $FILES
do
    for var1 in $FLAGS
    do
        for pattern in $PATTERNS
        do
            file=$file1
            var="-e $pattern -$var1"
            testing
        done
    done
done

for file1 in $FILES
do
    for var1 in $FLAGS
    do
        for var2 in $FLAGS
        do
            if [ $var1 != $var2 ]
            then
                for pattern in $PATTERNS
                do
                    file=$file1
                    var="-e $pattern -$var1$var2"
                    testing
                done
            fi
        done
    done
done

for file1 in $FILES
do
    for file2 in $FILES
    do
        if [ $file1 != $file2 ]
        then
            for var1 in $FLAGS
            do
                for var2 in $FLAGS
                do
                    if [ $var1 != $var2 ]
                    then
                        for pattern in $PATTERNS
                        do
                            file11="$file1"
                            file22="$file2"
                            var="-e $pattern -$var1$var2"
                            testing_multi
                        done
                    fi
                done
            done
        fi
    done
done

#flag f

for file1 in $FILES
do
    for var1 in $FLAGS
    do
        file=$file1
        var="-$var1"
        testing_file
    done
done

for file1 in $FILES
do
    for var1 in $FLAGS
    do
        for var2 in $FLAGS
        do
            if [ $var1 != $var2 ] && ! { [ "$var1" = "o" ] && [ "$var2" = "v" ]; } && ! { [ "$var1" = "v" ] && [ "$var2" = "o" ]; } && ! { [ "$var1" = "l" ] && [ "$var2" = "c" ]; } && ! { [ "$var1" = "c" ] && [ "$var2" = "l" ]; }
            then
                file=$file1
                var="-$var1$var2"
                testing_file
            fi
        done
    done
done

echo "SUCCESS: ${SUCCESS}"
echo "FAIL: ${FAIL}"
