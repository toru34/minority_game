import subprocess

import numpy as np

N_ITERS = 50000
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
                                            command = './a.out --s {} --p {} --eps {} --rhok {} --rhos {} --nm {} --np {} --ns {} --ni {} --nr {} --save_agents_history {}'.format(
                                                s, p, eps, rhok, rhos, nm, np, ns, ni, nr, args['save_agents_history']
                                            )
                                            print(command)
                                            subprocess.call(command, shell=True)

args_volatility = {
    's': 2,
    'p': 16,
    'eps': 0.01,
    'rhok': 0,
    'rhos': 0,
    'nm': 0,
    'ns': 501,
    'np': 1001,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_autocorrelation = {
    's': 2,
    'p': 16,
    'eps': 0.01,
    'rhok': 0,
    'rhos': 0,
    'nm': 0,
    'ns': 501,
    'np': 1000,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_fat_tail = {
    's': 2,
    'p': 16,
    'eps': 0.01,
    'rhok': 0,
    'rhos': 0,
    'nm': 0,
    'ns': 1001,
    'np': 1200,
    'ni': N_ITERS,
    'nr': N_RUNS
}

args_market_predictability1 = {
    's': 2,
    'p': 64,
    'eps': 0.01,
    'rhok': 0,
    'rhos': 0,
    'nm': 200,
    'ns': 0,
    'np': np.linspace(0, 200, 11),
    'ni': N_ITERS,
    'nr': N_RUNS,
    'save_agents_history': 0
}

args_market_predictability2 = {
    's': 2,
    'p': 64,
    'eps': 0.01,
    'rhok': 0,
    'rhos': 0,
    'nm': 200,
    'ns': np.linspace(0, 200, 11),
    'np': 200,
    'ni': N_ITERS,
    'nr': N_RUNS,
    'save_agents_history': 0
}

# run(args_market_ecology)
# run(args_volatility)
# run(args_autocorrelation)
# run(args_fat_tail)
run(args_market_predictability1)
run(args_market_predictability2)
