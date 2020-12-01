from controller_abc import ControllerABC

class Solution071(ControllerABC):

	class ProgramProperties:

		def __init__(self, weight, child_names):
			self.weight = int(weight)
			self.child_names = child_names
			self.sum_weight = -1

	def __init__(self):
		self.program_details = {}

	def line_reader(self, line):
		line_split = line.split()
		weight = line_split[1][1:-1]
		child_names = set()

		for index in range(3,len(line_split)):
			child_names.add(line_split[index].rstrip(','))

		self.program_details[line_split[0]] = Solution071.ProgramProperties(weight, child_names)

	def process_data(self):
		program_list = set(self.program_details.keys())

		for key, value in self.program_details.items():
			program_list -= value.child_names

		return program_list.pop()

