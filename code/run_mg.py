import subprocess

import numpy as np

N_ITERS = 50000
N_RUNS = 1

def to_array(values):
    return np.array([values]).flatten()


def run(args):
    command = ''
    for s in to_array(args['s']):
        for p in to_array(args['p']):
            for eps in to_array(args['eps']):
                for rhok in to_array(args['rhok']):
                    for rhos in to_array(args['rhos']):
                        for nm in to_array(args['nm']):
                            for np in to_array(args['np']):
                                for ns in to_array(args['ns']):
                                    for ni in to_array(args['ni']):
                                        for nr in to_array(args['nr']):
                                            command = './a.out --s {} --p {} --eps {} --rhok {} --rhos {} --nm {} --np {} --ns {} --ni {} --nr {}'.format(
                                                s, p, eps, rhok, rhos, nm, np, ns, ni, nr
                                            )
                                            print(command)
                                            subprocess.call(
                                                command, shell=True)

args_market_ecology = {
    's': 2,
    'p': np.power(2, np.arange(1, 16)),
    'eps': 0,
    'rhok': 0,
    'rhos': 0,
    'nm': 101,
    'ns': 0,
    'np': 0,
    'ni': N_ITERS,
    'nr': N_RUNS
}


run(args_market_ecology)
