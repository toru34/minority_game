#!/bin/bash

# Parameters
ss="2"
ps="2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768"
es="0.01"
nms="101"
nps="00"
nss="0"
nis="50000"
nrs="1"

for s in $ss; do
    for p in $ps; do
        for e in $es; do
            for nm in $nms; do
                for np in $nps; do
                    for ns in $nss; do
                        for ni in $nis; do
                            for nr in $nrs; do
                                command="./a.out --s $s --p $p --e $e --nm $nm --np $np --ns $ns --ni $ni --nr $nr"

                                $command
                            done
                        done
                    done
                done
            done
        done
    done
done