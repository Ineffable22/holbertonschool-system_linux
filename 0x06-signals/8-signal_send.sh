#!/usr/bin/env sh
# Sends the signal SIGQUIT to a process, given its PID

if [ $# != 1 ]
then
   echo "Usage: ${0} <pid>"
   return 1
fi

kill -QUIT "${1}"
