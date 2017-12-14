from controller_abc import ControllerABC

class Solution101(ControllerABC):

	numbers_list_len = 256

	def __init__(self):
		self.numbers_list = list(range(0,Solution101.numbers_list_len))
		self.curr_index = 0
		self.skip_length = 0

	def line_reader(self, line):
		self.length_list = [int(no.strip()) for no in line.strip('\n').split(',')]

	def process_data(self):
		return self.operate()

	def operate(self):
		for length in self.length_list:
			self.rotate(self.curr_index, length)
			self.curr_index = (self.curr_index + length + self.skip_length) % Solution101.numbers_list_len
			self.skip_length += 1

		return self.numbers_list[0] * self.numbers_list[1]

	def rotate(self, curr_index, length):
		end_index = (curr_index + length - 1) % Solution101.numbers_list_len
		for _ in range(0, length//2):
			self.numbers_list[curr_index], self.numbers_list[end_index] = self.numbers_list[end_index], self.numbers_list[curr_index]
			curr_index = (curr_index + 1) % Solution101.numbers_list_len
			end_index -= 1

