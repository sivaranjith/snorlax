from problem_1 import Solution081

class Solution082(Solution081):

	def __init__(self):
		super().__init__()
		self.alltime_max_register_val = None

	def line_reader(self, line):
		super().line_reader(line)
		max_val = super().process_data()
		if self.alltime_max_register_val is None or max_val > self.alltime_max_register_val:
			self.alltime_max_register_val = max_val

	def process_data(self):
		return self.alltime_max_register_val