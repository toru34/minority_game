#!/bin/bash

# Parameters
ss="2"
ps="16"
es="0.01"
rhoks="0.00"
rhoss="0.00"
nms="0"
nps="1200"
nss="1001"
nis="50000"
nrs="10"

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