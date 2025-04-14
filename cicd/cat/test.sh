#!/bin/bash

SUCCESS=0
FAIL=0
TOTAL=205
DIFF_RES=""
RESULT=""
FILE="test.txt"
FLAGS="b e n s t"

testing() {
    ./s21_cat "$var" "$FILE" > "test_s21_cat.log"
    cat "$var" "$FILE" > "test_sys_cat.log"
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${SUCCESS}/${TOTAL}] ${RESULT}" cat "$var" "$FILE"
    rm test_s21_cat.log test_sys_cat.log
}

# 1 параметр
for var1 in $FLAGS
do
    var="-$var1"
    testing
done

# 2 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        if [ $var1 != $var2 ]
        then
            var="-$var1$var2"
            testing
        fi
    done
done

# 3 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                var="-$var1$var2$var3"
                testing
            fi
        done
    done
done

# 4 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            for var4 in $FLAGS
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    var="-$var1$var2$var3$var4"
                    testing $i
                fi
            done
        done
    done
done

echo "SUCCESS: ${SUCCESS}"
echo "FAIL: ${FAIL}"
