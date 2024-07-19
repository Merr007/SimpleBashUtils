#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF="Files s21_grep.txt and grep.txt are identical"

leaks -atExit -- ../s21_grep e test.txt
../s21_grep e test.txt > s21_grep.txt
grep e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success no flags"
else
    let "FAIL++"
    echo "$COUNTER - Fail no flags"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -e "te" test.txt
../s21_grep -e "te" test.txt > s21_grep.txt
grep -e "te" test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -e"
else
    let "FAIL++"
    echo "$COUNTER - Fail -e"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -i e test.txt
../s21_grep -i e test.txt > s21_grep.txt
grep -i e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -i"
else
    let "FAIL++"
    echo "$COUNTER - Fail -i"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -v e test.txt
../s21_grep -v e test.txt > s21_grep.txt
grep -v e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -v"
else
    let "FAIL++"
    echo "$COUNTER - Fail -v"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -c e test.txt
../s21_grep -c e test.txt > s21_grep.txt
grep -c e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -c"
else
    let "FAIL++"
    echo "$COUNTER - Fail -c"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -l e test.txt test.txt test.txt
../s21_grep -l e test.txt test.txt test.txt > s21_grep.txt
grep -l e test.txt test.txt test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -l"
else
    let "FAIL++"
    echo "$COUNTER - Fail -l"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -n e test.txt
../s21_grep -n e test.txt > s21_grep.txt
grep -n e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -n"
else
    let "FAIL++"
    echo "$COUNTER - Fail -n"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -h e test.txt
../s21_grep -h e test.txt > s21_grep.txt
grep -h e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -h"
else
    let "FAIL++"
    echo "$COUNTER - Fail -h"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -s e test.txt
../s21_grep -s e test.txt > s21_grep.txt
grep -s e test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -s"
else
    let "FAIL++"
    echo "$COUNTER - Fail -s"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -f pattern.txt test.txt
../s21_grep -f pattern.txt test.txt > s21_grep.txt
grep -f pattern.txt test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -f"
else
    let "FAIL++"
    echo "$COUNTER - Fail -f"
fi
rm s21_grep.txt grep.txt

leaks -atExit -- ../s21_grep -o te test.txt
../s21_grep -o te test.txt > s21_grep.txt
grep -o te test.txt > grep.txt
let "COUNTER++"
if [ "$DIFF" == "$(diff -s s21_grep.txt grep.txt)" ]
then
    let "SUCCESS++"
    echo "$COUNTER - Success -o"
else
    let "FAIL++"
    echo "$COUNTER - Fail -o"
fi
rm s21_grep.txt grep.txt

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"