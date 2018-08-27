#!/usr/bin/env python3

import csv, json
import numpy as np
from util import *

keys = []
data = []
with open("data.csv") as f:
    for r, row in enumerate(csv.reader(f)):
        if r == 0:
            keys = row
        else:
            data.append(dict(zip(keys, [as_numeric(item) for item in row])))

print(json.dumps(data, indent=4))

signal_keys = [ 'Raw AMD',
                'Sedimentation 1 Outlet',
                'DSR 1',
                'DSR 2',
                'DSR 3',
                'Slag Outlet'
                ]

signals = []
for key in signal_keys:
    signals.append(normalize([datum[key] for datum in data]))

# ctx = drawing.Context(2000, 800, margin=50, hsv=False)
# for s, signal in enumerate(signals):
#     ctx.plot(signal, stroke=colors[s % len(colors)], thickness=2.0)
# ctx.output("graphs/")        

for s, signal in enumerate(signals):
    print("float data[] = {%s};" % (",".join(["%.5f" % point for point in signal])))

# red, blue, brown, purple, burnt, yellow