#!/usr/bin/python3

'''
This file tests student written cachelab traces. It tests them by running the
trace on csim-ref and comparing the hits/misses/evictions with the expected
hits/misses/evictions. It also checks if the trace is well written.

If run with the -f [tracefile] it only judges whether tracefile is well written
or not.
'''

import subprocess
import re
import os
import sys
import argparse

traces = ["tr1.trace", "tr2.trace", "tr3.trace"]
params = [[3, 1, 4], [1, 3, 4], [2, 3, 4]] # Format: [s, E, b]
maxOps = [5, 5, 10]
expected = [[2, -1, 1], [2, 2, -1], [5, 4, 1]] #Format: [hits, misses, evictions]
maxPoints = [3, 3, 4]

pathToTraces = "./traces/"

def countOps(trace):
    count = 0
    with open(pathToTraces + trace, "r") as f:
        operations = f.read()
        for op in ["L", "S"]:
            count += operations.count(op)
    return count

# Verify that the trace file being run is well written, i.e. it is in the
# format " (L|S) addr,len"
def isValidTrace(trace):
    with open(pathToTraces + trace, "r") as f:
        data = f.read()
        if data == "":
            print("{} is not a well written trace.".format(trace))
            return False
        instructions = data.split("\n")

    for i, instr in enumerate(instructions[:-1], start=1):
        if re.match(r"[LS] \w+,\d+", instr) == None:
            print("\"{}\" is not a well written instruction.".format(instr))
            return False

    return True

# Run a tracefile through csim-ref and return the hits, misses and evictions
# from running the trace
def runTrace(trace, parameters, maxOps):
    if not os.path.exists(pathToTraces + trace):
        print("Could not find {}".format(trace))
        return -1, -1, -1

    if countOps(trace) > maxOps:
        print("{} contains too many instructions, use a maximum of {} for this trace".format(trace, maxOps))
        return -1, -1, -1

    if not isValidTrace(trace):
        return -1, -1, -1

    # Remove previous results
    if os.path.exists(".csim_results"):
        os.remove(".csim_results")

    p = subprocess.run("./csim-ref -s {} -E {} -b {} -t {}".format(parameters[0], \
                        parameters[1], parameters[2], pathToTraces + trace), \
                        shell=True, stdout=subprocess.DEVNULL)

    if p.returncode != 0:
        # Not run successfully
        print("Running {} on csim-ref failed!".format(trace))
        return -1, -1, -1

    with open(".csim_results", "r") as f:
        results = f.read()

    results = list(map(int,results.split(" ")))

    # Return hits, misses, evictions
    print("{} results:".format(trace))
    return (results[0], results[1], results[2])

# Compare a value from a trace with an expected value, if expected is -1,
# the result doesn't matter
def cmp(real, exp):
    for i, val in enumerate(real):
        if exp[i] != -1 and val != exp[i]:
            return False
    return True

def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-f", help="Verify a specifici trace is well written")
    group.add_argument("-A", action="store_true", dest="autograde",
                         help="emit autoresult string for Autolab")
    args = parser.parse_args()
    autograde = args.autograde

    # If run with the -f flag, check if a tracefile is well written
    if args.f != None:
        # Check if a trace is well written
        trace = args.f
        if trace.endswith(".trace"):
            if isValidTrace(trace):
                print("{} is a well written trace".format(trace))
                return
        else:
            print("Please specify a .trace file!")
            return

    else:
        # Run all traces
        points = [0, 0, 0]

        for i, tr in enumerate(traces):
            traceResults = runTrace(tr, params[i], maxOps[i])
            if traceResults == (-1, -1, -1):
                print("Error running {}\n".format(tr))
                continue

            if cmp(traceResults, expected[i]):
                    points[i] = maxPoints[i]

            print("Real values       - Hits: {} Misses: {} Evictions: {}".format(traceResults[0], traceResults[1], traceResults[2]))
            print("Expected values   - Hits: {} Misses: {} Evictions: {}".format(expected[i][0], expected[i][1], expected[i][2]))
            print("{} points = {} / {}\n".format(tr, points[i], maxPoints[i]))

        if autograde:
            autoresult = "{\"scores\": {\"Autograded\": %d}}" % sum(points)
            print(autoresult)


if __name__ == "__main__":
    main()
