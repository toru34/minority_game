#!/bin/bash

# Parameters
ss="2"
ps="16"
es="0.01"
nms="0"
nps="1200"
nss="1001"
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