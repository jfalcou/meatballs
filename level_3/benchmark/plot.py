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

args = parser.parse_args()

data = open(args.filename, "r")
json_data = json.load(data)

openblas_metrics = json_data["openblas_metrics"]
gemm_metrics = json_data["gemm_metrics"]
dimensions = json_data["dimensions"]

fig, ax = plt.subplots()
ax.grid()

x = range(len(dimensions))
ax.semilogy(x, openblas_metrics, "-x", label="OpenBLAS")
ax.semilogy(x, gemm_metrics, "-x", label="xGEMM")
ax.set_title("Number of cpu cycles per computed entry for square matrices of dimension N")
ax.set_xlabel("N")
ax.set_ylabel("cycles/entry (lower is better)")
ax.set_xticks(x)
ax.set_xticklabels(dimensions, rotation=45)
ax.legend()

if args.output is not None:
    plt.savefig(args.output, bbox_inches="tight")
if args.show:
    plt.show()
