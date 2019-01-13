#!/bin/bash

# Parameters
s_array="2"
p_array="2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384"
eps_array="0"
rhok_array="0.2"
rhos_array="0.09 0.17 0.23 0.28 0.33"
nm_array="101"
np_array="0"
ns_array="0"
ni_array="1000"
nr_array="1"

for s in $s_array; do
    for p in $p_array; do
        for eps in $eps_array; do
            for rhok in $rhok_array; do
                for rhos in $rhos_array; do
                    for nm in $nm_array; do
                        for np in $np_array; do
                            for ns in $ns_array; do
                                for ni in $ni_array; do
                                    for nr in $nr_array; do
                                        command="./a.out --s $s --p $p --eps $eps --rhok $rhok --rhos $rhos --nm $nm --np $np --ns $ns --ni $ni --nr $nr"

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