#!/bin/sh

FAILED=0
SUCCESS=0

sendInfos()
{
	LOG_FILE=$1
	RESULT_FILE=$2
}

print()
{
	echo "Log vaut $LOG_FILE"
	echo "Res vaut $RESULT_FILE"
}

testArg() 
{
	ARG="$1 $2 $3 $4 $5"
	./philo $ARG 2>>$LOG_FILE 1>>$RESULT_FILE
	RESULT=$?
	if [ $RESULT != 0 ]; then
		echo "\033[0;31mFailed at $ARG\033[0m"
		echo "Failed at $ARG\n" >>$LOG_FILE
		FAILED=$((FAILED + 1))
	fi
	if [ $RESULT = 0 ]; then
		SUCCESS=$((SUCCESS + 1))
		echo "\033[0;32mSuccess at $ARG\033[0m"
		echo "Success at $ARG\n" >>$RESULT_FILE
	fi
}

testArg_4() {
	testArg 1 1 1 1
	testArg 0 1 1 1
	testArg 1 0 1 1
	testArg 1 1 0 1
	testArg 1 1 1 0
	testArg 0 0 1 1
	testArg 1 0 0 1
	testArg 1 1 0 0
	testArg 0 1 0 1
	testArg 1 0 1 0
	testArg 0 1 1 0
	echo "Check Arguments rejecting done for 4 arguments"
}

testArg_5() {
	testArg 1 1 1 1 1
	testArg 0 1 1 1 1
	testArg 1 0 1 1 1
	testArg 1 1 0 1 1
	testArg 1 1 1 0 1
	testArg 0 0 1 1 1
	testArg 1 0 0 1 1
	testArg 1 1 0 0 1
	testArg 0 1 0 1 1
	testArg 1 0 1 0 1
	testArg 0 1 1 0 1
	testArg 1 1 1 1 0
	testArg 0 1 1 1 0
	testArg 1 0 1 1 0
	testArg 1 1 0 1 0
	testArg 1 1 1 0 0
	testArg 0 0 1 1 0
	testArg 1 0 0 1 0
	testArg 1 1 0 0 0
	testArg 0 1 0 1 0
	testArg 1 0 1 0 0
	testArg 0 1 1 0 0
	echo "Check Arguments rejecting done for 5 arguments"
}

testArg_4_var() {
	echo "Testing with different values"
	testArg -2 1 1 1
	testArg 1 -2 1 1
	testArg 1 1 -2 1
	testArg 1 1 1 -2
	testArg -2 -2 1 1
	testArg 1 -2 -2 1
	testArg 1 1 -2 -2
	testArg -2 1 -2 1
	testArg 1 -2 1 -2
	testArg -2 1 1 -2
	echo "Check Arguments rejecting done for 4 arguments"
}

testArg_5_var() {
	testArg -2 1 1 1 1
	testArg 1 -2 1 1 1
	testArg 1 1 -2 1 1
	testArg 1 1 1 -2 1
	testArg 1 1 1 1 -2
	testArg -2 -2 1 1 1
	testArg 1 -2 -2 1 1
	testArg 1 1 -2 -2 1
	testArg -2 1 -2 1 1
	testArg 1 -2 1 -2 1
	testArg -2 1 1 -2 1
	testArg -2 1 1 1 -2
	testArg 1 -2 1 1 -2
	testArg 1 1 -2 1 -2
	testArg 1 1 1 -2 -2
	testArg -2 -2 1 1 -2
	testArg 1 -2 -2 1 -2
	testArg 1 1 -2 -2 -2
	testArg -2 1 -2 1 -2
	testArg 1 -2 1 -2 -2
	testArg -2 1 1 -2 -2
	echo "Check Arguments rejecting done for 5 arguments"
}

testArg_5_letter() {
	testArg e 1 1 1 1
	testArg 1 e 1 1 1
	testArg 1 1 e 1 1
	testArg 1 1 1 e 1
	testArg 1 1 1 1 e
	testArg e e 1 1 1
	testArg 1 e e 1 1
	testArg 1 1 e e 1
	testArg e 1 e 1 1
	testArg 1 e 1 e 1
	testArg e 1 1 e 1
	testArg e 1 1 1 e
	testArg 1 e 1 1 e
	testArg 1 1 e 1 e
	testArg 1 1 1 e e
	testArg e e 1 1 e
	testArg 1 e e 1 e
	testArg 1 1 e e e
	testArg e 1 e 1 e
	testArg 1 e 1 e e
	testArg e 1 1 e e
	echo "Check Arguments rejecting done for 5 arguments"
}

testArgs() {
	echo "Testing with 4 arguments"
	testArg_4
	testArg_4_var
	echo "Testing with 5 arguments"
	testArg_5
	testArg_5_var
	testArg_5_letter
	echo "Tests complete."
	echo "Total tests: $((SUCCESS + FAILED)) for \033[0;32m$SUCCESS success\033[0m and \033[0;31m$FAILED failed\033[0m"
	echo ""
	echo "Files copied to: "
	FILE='\e]8;;file://'$LOG_FILE'\e\\'"ERRORS :"'\e]8;;\e\\'
	echo $FILE
	echo "file://$LOG_FILE"
	FILE='\e]8;;file://'$RESULT_FILE'\e\\'"SUCCESS :"'\e]8;;\e\\'
	echo $FILE
	echo "file://$RESULT_FILE"
}
