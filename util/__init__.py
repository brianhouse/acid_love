import numpy as np
from . import drawing
from .colors import colors

def as_numeric(s):
    if type(s) == int or type(s) == float or type(s) == bool:
        return s
    try:
        s = int(s)
    except (ValueError, TypeError):
        try:
            s = float(s)
        except (ValueError, TypeError):
            pass
    return s


def normalize(signal, minimum=None, maximum=None):
    signal = np.array(signal).astype('float')
    if minimum is None:
        minimum = np.min(signal)
    if maximum is None:
        maximum = np.max(signal)
    signal -= minimum
    maximum -= minimum
    signal /= maximum
    signal = np.clip(signal, 0.0, 1.0)
    return signal    
