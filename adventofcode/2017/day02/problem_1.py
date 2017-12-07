class Solution021:

	def __init__(self):
		self.check_sum = 0

	def line_reader(self, line):
		ele_list = [int(ele) for ele in line.split()]
		self.check_sum += self.process_line(ele_list)

	def process_line(self, ele_list):
		return max(ele_list) - min(ele_list)

	def process_data(self):
		return self.check_sum
