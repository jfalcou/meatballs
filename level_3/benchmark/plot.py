#!/usr/bin/env python3

import matplotlib.pyplot as plt
import json
import argparse

parser = argparse.ArgumentParser(
    description="Plots benchmarking data from a json file"
)

parser.add_argument("filename", help="The json file containing the results")
parser.add_argument("-o", "--output", type=str, nargs="?",
                    help="The image output file", default="plot.png")
parser.add_argument("-s", "--show", action="store_true",
                    help="Display the plot")
parser.add_argument("--cpv", action="store_true",
                    help="Plot the cycles per computed values")

args = parser.parse_args()

data = open(args.filename, "r")
json_data = json.load(data)

if args.cpv:
    openblas_metrics = json_data["cycles_per_value"]["openblas"]
    gemm_metrics = json_data["cycles_per_value"]["gemm"]
    title = "Nombre de cycles par valeur calculée d'une matrice carrée de dimension N"
    y_label = "cycles par valeur (bas = meilleur)"
else:
    openblas_metrics = json_data["gflops"]["openblas"]
    gemm_metrics = json_data["gflops"]["gemm"]
    title = "Nombre d'opérations flotantes par seconde pour une multiplication de matrices de dimension N"
    y_label = "Gflops"

dimensions = json_data["dimensions"]

fig, ax = plt.subplots()
ax.grid()

x = range(len(dimensions))
ax.plot(x, openblas_metrics, "-x", label="OpenBLAS")
ax.plot(x, gemm_metrics, "-x", label="xGEMM")
ax.set_title(title)
ax.set_xlabel("N")
ax.set_ylabel(y_label)
ax.set_xticks(x)
ax.set_xticklabels(dimensions, rotation=45)
ax.legend()

if args.output is not None:
    plt.savefig(args.output, bbox_inches="tight")
if args.show:
    plt.show()
