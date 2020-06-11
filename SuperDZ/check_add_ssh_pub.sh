#!/bin/bash
# check from file & add ssh .pub key to authorized keys
# chpeckdev 5/10/2020 3:01am
# SEE IT IF PUB KEY EXIST ECHO True
# ITS ABILITY OF ssh-keygen CANT WORK WITH PIPE ONLY FILE

PATH_SSH_TMP_KEY=/home/pi/ArturBot/bot3/ssh.tmp
PATH_SSH_KEYS=/home/pi/.ssh/authorized_keys

IS_NOT_PUB=$(ssh-keygen -lf $PATH_SSH_TMP_KEY 2>&1 | grep -c "is not a public key file")

if [[ $IS_NOT_PUB == 0 ]]; then
	IS_PUB_EXIST=$(cat $PATH_SSH_KEYS | grep -c -f $PATH_SSH_TMP_KEY)
	if [[ $IS_PUB_EXIST == 0 ]]; then
		cat $PATH_SSH_TMP_KEY >> $PATH_SSH_KEYS
		echo True
	else
		#echo "PUB KEY EXIST"
		echo True
	fi
else
	echo False
fi
