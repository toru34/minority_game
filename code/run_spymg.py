import subprocess

import numpy as np

N_ITERS = 1000
N_RUNS = 10

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
                                            subprocess.call(command, shell=True)

args_fig_11 = {
    's': 2,
    'p': np.power(2, np.arange(2, 15)),
    'eps': 0,
    'rhok': [0.2, 0.4, 0.6],
    'rhos': 0.09,
    'nm': 101,
    'np': 0,
    'ns': 0,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_fig_12 = {
    's': 2,
    'p': np.power(2, np.arange(2, 15)),
    'eps': 0,
    'rhok': 0,
    'rhos': 0,
    'nm': 101,
    'np': 0,
    'ns': 0,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_fig_2 = {
    's': 2,
    'p': np.power(2, np.arange(1, 15)),
    'eps': 0,
    'rhok': 0.2,
    'rhos': [0.09, 0.17, 0.23, 0.28, 0.33],
    'nm': 101,
    'np': 0,
    'ns': 0,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_fig_3 = {
    's': 2,
    'p': np.array([4, 64, 1024]),
    'eps': 0,
    'rhok': 0.2,
    'rhos': np.linspace(0.02, 0.5, 25),
    'nm': 101,
    'np': 0,
    'ns': 0,
    'ni': N_ITERS,
    'nr': N_RUNS
}

run(args_fig_11)
run(args_fig_12)
run(args_fig_2)
run(args_fig_3)