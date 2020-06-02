#!/usr/bin/python
'''
	Python3 Driver for Malloc Lab Traces

	No assumption about malloc design,
	although designed to run a malloc trace through
	the mm.c implementation for malloc (implicit list first-find allocation)

	Behavior: {
		Runs mm_initializer in a subprocess call, where the traces are
		run through mm.c. The python driver is simply a mask to perform
		the simple execution. It redirects the standard output of the
		mm_initializer. If there are errors, those errors will be redirected.
	}

	Options: {
		-f <trace_file> : Takes in trace file as the second argument
		-h : Returns a list of options and their descriptions

	}

	TODO: {
		Add another field so the user can test every trace file they have in
		order of input, and match with ordered trace grading specifications
	}

	Current hardcoded situations: {
		Assumption of 4 cases (4 Cases of coalesce) in the Trace_file class
		and trace_cases list in run_traces

		Assumption of only 1 file possible. Need to extend this
	}
'''
import os, sys, getopt
import subprocess

'''
	Define trace specifications here
'''


'''
	Classes
'''

'''
	Trace_file is initialized with one argument called results, a list of
	4 elements corresponding to the 4 cases for coalesce_block, with the
	count of each result at each position
'''
class Trace_file:

	def __init__(self, results, number):
		self.case1 = results[0] #prev/next both allocated
		self.case2 = results[1] #prev allocated, next free
		self.case3 = results[2] #prev free, next allocated
		self.case4 = results[3] #prev free, next free
		self.case1E = "-"
		self.case2E = "0"
		self.case3E = "0"
		self.case4E = "0"
		self.opCount = results[4]
		self.allocCount = results[5]
		self.number = number
		if self.number == 0:
			self.case2E = "1"
		if self.number == 1:
			self.case3E = "1"
		if self.number == 2:
			self.case4E = "1"
	def __repr__(self):
		template = "{0:<50s}{1:>20s}{2:>20s}"
		return \
			"-"*90 + "\n" + \
			"Trace " + str(self.number + 1) + "\n" + \
			"-"*90 + "\n" + \
			template.format("Cases", "Actual", "Expected\n") + \
			"-"*90 + "\n" + \
			template.format("1: [Previous/Next both allocated]", str(self.case1), self.case1E + "\n") + \
			template.format("2: [Previous allocated, Next free]", str(self.case2), self.case2E + "\n") + \
			template.format("3: [Previous free, Next allocated]", str(self.case3), self.case3E + "\n") + \
			template.format("4: [Previous/Next both free]", str(self.case4), self.case4E + "\n") + \
			"-"*90


def run_benchmark(trace, number):
	#if number == 0:
	#	if trace.case1 == 1 and trace.case2 == 0 and trace.case3 == 0 and trace.case4 == 0:
	#		return 2.5
	#	else:
	#		return 0
	if number == 0:
		if trace.case2 == 1 and trace.case3 == 0 and trace.case4 == 0:
			return 3.0
		else:
			return 0
	elif number == 1:
		if trace.case3 == 1 and trace.case2 == 0 and trace.case4 == 0:
			return 3.0
		else:
			return 0
	elif number == 2:
		if trace.case4 == 1 and trace.case2 == 0 and trace.case3 == 0:
			return 4.0
		else:
			return 0


'''
	run_trace(bcommand)
	Designed to run a particular trace defined by the command that will be
		run with mm_initializer (which only takes 1 trace)

	Argument: bcommand := list of commandline arguments passed into
		mm_initializer

	mm_initializer takes in 1 trace per call
'''
def run_trace(bcommand, number):

	try:
		# Opens a log file to store results from mm_initializer
		logfile = open(".tracelog.txt", "w+")

	except:
		print("Logfile creation/open error")
		sys.exit(1)

	#Redirect child stdout to logfile
	process = subprocess.Popen(bcommand, shell=False, \
									universal_newlines=True, \
									stdout=logfile, \
									stderr=sys.stdout, \
									cwd=os.getcwd())

	ret_code = process.wait() #Let entire subprocess to die and reap
	logfile.flush()

	#Trace logfile
	if (ret_code == 1):
		#ERROR
		#Need to redirect error outputs for printing. Issue is that we
		#Clogged the stdout with both error messages and successes
		#Maybe write error code in subprocess to stderr and redirect
		#stderr to stdout in parent process

		#Close file
		return None

	try:
		logfile.seek(0, 0)

	except:
		print("file seek error in mtrace_driver")
		logfile.close();
		sys.exit(1)



	log_lines = logfile.read().splitlines()

	#Defined cases
	#Should probably make this more adaptable to new implementations
	trace_cases = [0,0,0,0,0,0]
	count = 0
	for line in log_lines:
		if count == 0:
			count += 1
			trace_cases[4] = line
			continue
		count += 1
		if (line == "Done"):
			break
		if (line == "1"):
			trace_cases[0] += 1

		elif (line == "2"):
			trace_cases[1] += 1

		elif (line == "3"):
			trace_cases[2] += 1

		elif (line == "4"):
			trace_cases[3] += 1
	trace_cases[5] = log_lines[-1]
	# Close file
	logfile.close()

	return Trace_file(trace_cases, number)



def main (argv):
	bcommand = [["./mm_initializer"], ["./mm_initializer"], ["./mm_initializer"], ["./mm_initializer"]]

	trace_files = ["./traces/tr1.rep", "./traces/tr2.rep", "./traces/tr3.rep", "./traces/tr4.rep"]
	# Does same parsing as the c file
	autograde = False

	try:
		opts, args = getopt.getopt(argv,"ht:A")

		if (len(opts) == 3):
			#No arguments
			print("Unknown arguments. Refer to -h for help")
			exit(2)

	except getopt.GetoptError:
		print("Unknown arguments. Refer to -h for help")
		sys.exit(2)

	for opt, arg in opts:
		if (opt == "-h"):
			print("-h : Show the help menu")
			#print("-f <input_file> : Specify a trace file to run through")
			print("-t <trace_number> : Specify a trace to run in the range [1,3]")
			print("No argument: Run on all trace files")
			return

		#elif (opt == "-f"): #Omitted because trace files are specific
		#	trace_file = arg
			#bcommand[0] += [opt, trace_file]
		elif (opt == "-t"):
			#Specify trace to test
			try:
				index = int(arg) - 1
				if index < 0 or index > 2:
					exit(1)

				trace_file = trace_files[index]
			except:
				print("Usage: -t <trace_number> : Specify a trace to run in the range [1,3]")
				exit(1)

			bcommand[index] += ["-f", trace_file]
			tmp_trace = run_trace(bcommand[index], index)

			#Error check
			if (tmp_trace == None):
				#print("Trace %d is not well-formatted." % index)
				sys.exit(1)

			results = run_benchmark(tmp_trace, index)
			print(tmp_trace)
			if index == 2:
				print("Score for trace %d: %0.1f/4.0" % (index, results))
			else:
				print("Score for trace %d: %0.1f/3.0" % (index, results))
			return

		elif (opt == "-A"):
			#Autograder requirement
			autograde = True
		else:
			print("Unknown arguments. Refer to -h for help")
			exit(2)

	traces = [0, 0, 0]
	results = [0, 0, 0]
	for i in range(len(results)):
		trace_file = trace_files[i]
		bcommand[i] += ["-f", trace_file]
		traces[i] = run_trace(bcommand[i], i)
		if traces[i] == None:
			print("Trace " + str(i+1) + " is not well-formatted.")
			continue
		results[i] = run_benchmark(traces[i], i)
		print(traces[i]) #Print output of trace

	autoresult = "{\"scores\": {\"Autograded\": %0.1f}}" % sum(results)
	if autograde:
		print(autoresult)
	else:
		print("Trace 1: " + str(results[0]) + "/3.0, Trace 2: " + str(results[1]) + "/3.0, Trace 3: " + str(results[2]) + "/4.0")

if __name__ == "__main__":
	main(sys.argv[1:])
