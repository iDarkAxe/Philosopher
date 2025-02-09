#!/bin/sh

FAILED=0
SUCESS=0

testArg()
{
	ARG="$1 $2 $3 $4 $5"
	./philo	$ARG 2> /dev/null 1> /dev/null
	RESULT=$?
	if [ $RESULT != 0 ]; then
		echo "\033[0;31mFailed at $ARG\033[0m"
		FAILED=$((FAILED + 1))
	fi
	if [ $RESULT = 0 ]; then
		SUCESS=$((SUCESS + 1))
		echo "\033[0;32mSuccess at $ARG\033[0m"
	fi
}

testArg_4()
{
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
testArg_5()
{
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

testArg_4_var()
{
	echo "Testing with different values"
	testArg 1 1 1 1
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

testArg_5_var()
{
	testArg 1 1 1 1 1
	testArg -2 1 1 1 1
	testArg 1 -2 1 1 1
	testArg 1 1 -2 1 1
	testArg 1 1 1 -2 1
	testArg -2 -2 1 1 1
	testArg 1 -2 -2 1 1
	testArg 1 1 -2 -2 1
	testArg -2 1 -2 1 1
	testArg 1 -2 1 -2 1
	testArg -2 1 1 -2 1
	testArg 1 1 1 1 -2
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

testArgs()
{
	echo "Testing with 4 arguments"
	testArg_4
	testArg_4_var
	echo "Testing with 5 arguments"
	testArg_5
	testArg_5_var
	echo "Total tests: $((SUCESS + FAILED)) for $SUCESS success and $FAILED failed"
}

# Check Arguments rejecting
make
testArgs