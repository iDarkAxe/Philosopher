#!/bin/sh

# export LOG_FILE=~/philosopher/philo/tests/log
# export RESULT_FILE=~/philosopher/philo/tests/result

LOG_FILE=~/Documents/philosopher_reboot/philo_reboot/tests/log
RESULT_FILE=~/Documents/philosopher_reboot/philo_reboot/tests/result

GREENCOLOR="\033[0;32m"
REDCOLOR="\033[0;31m"
ENDCOLOR="\033[0m"

if [ ! -z "$1" ] && [ $1 = "rm" ]; then
	echo "Removing files only"
	rm -rf $LOG_FILE
	rm -rf $RESULT_FILE
	exit 0
fi

# Check Arguments rejecting
make
rm -rf $LOG_FILE
rm -rf $RESULT_FILE
. ~/Documents/philosopher_reboot/philo_reboot/tests/fx_for_tests.sh
sendInfos $LOG_FILE $RESULT_FILE
testArgs