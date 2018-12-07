#!/bin/bash

# Parameters
ss="2"
ps="2 4 8 16 32 64 128 256 512 1024 2048 4095 8192 16384"
es="0"
rhoks="0.2 0.4 0.6"
rhoss="0.09"
nms="101"
nps="0"
nss="0"
nis="50000"
nrs="1"

for s in $ss; do
    for p in $ps; do
        for e in $es; do
            for rhok in $rhoks; do
                for rhos in $rhoss; do
                    for nm in $nms; do
                        for np in $nps; do
                            for ns in $nss; do
                                for ni in $nis; do
                                    for nr in $nrs; do
                                        command="./a.out --s $s --p $p --e $e --rhok $rhok --rhos $rhos --nm $nm --np $np --ns $ns --ni $ni --nr $nr"

                                        $command
                                    done
                                done
                            done
                        done
                    done
                done
            done
        done
    done
done