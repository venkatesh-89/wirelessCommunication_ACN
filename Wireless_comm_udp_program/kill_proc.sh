#!/bin/sh
#set -x

str=`ps -ef| grep Tree | grep -v grep | awk '{print $2}'`
if [ -z "$str" ]
then
    echo "No process running..."
    #echo "Deleting *txt files..."
    #rm -rf *txt
    echo "Bye...."
    exit;
fi

echo kill -9 $str 
`kill -9 $str`

echo `ps -ef| grep Tree | grep -v grep`
echo "No process running..."
#echo "Deleting *txt files..."
#rm -rf *txt
echo "Bye...."
