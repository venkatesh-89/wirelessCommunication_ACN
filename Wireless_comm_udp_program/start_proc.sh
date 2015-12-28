#!/bin/sh

if [ $# -ne 1 ]
then
    echo "Usage : $0 file_name"
    echo "Eg : $0 <File Name>"
    exit
fi


echo "Starting the program './spanningTree' for nodes B to T.... "
./spanningTree B $1 &
./spanningTree C $1 &
./spanningTree D $1 &
./spanningTree E $1 &
./spanningTree F $1 &
./spanningTree G $1 &
./spanningTree H $1 &
./spanningTree I $1 &
./spanningTree J $1 &
./spanningTree K $1 &
./spanningTree L $1 &
./spanningTree M $1 &
./spanningTree N $1 &
./spanningTree O $1 &
./spanningTree P $1 &
./spanningTree Q $1 &
./spanningTree R $1 &
./spanningTree S $1 &
./spanningTree T $1 &

echo "done"
