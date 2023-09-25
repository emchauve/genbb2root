#!/bin/bash

# bxgenbb_inspector \
#     --configuration dbd.conf \
#     --action list

BASE_PATH=./
DATA_PATH=$BASE_PATH/data
mkdir -p $DATA_PATH $ROOT_PATH

if (( $# < 2 )) ; then
    echo "usage: $0 [GENERATOR] [NBEVENTS]"
    echo "       with generator = bi214, tl208, ..."
    exit
fi

GENERATOR=$1
NBEVENTS=$2

echo "processing $GENERATOR ..."

bxgenbb_inspector \
    --action shoot \
    --configuration conf/genbb.conf \
    --generator $GENERATOR \
    --number-of-events $NBEVENTS \
    --modulo 100000 \
    --output-mode plain \
    --output-file ${DATA_PATH}/${GENERATOR}.data.gz

build/genbb2root \
    -i ${DATA_PATH}/${GENERATOR}.data.gz \
    -o ${DATA_PATH}/${GENERATOR}.root

# # remove the original GENBB file
# rm -vf ${DATA_PATH}/${GENERATOR}.txt
