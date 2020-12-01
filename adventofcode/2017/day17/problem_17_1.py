from controller_abc import ControllerABC

class Solution171(ControllerABC):

	STOP_VAL = 2017

	def __init__(self):
		self.curr_position = 0

	def line_reader(self, line):
		self.steps_forward = int(line.rstrip('\n'))

	def process_data(self):
		self.circular_buffer = [0]
		self.run_insert_operation(Solution171.STOP_VAL)
		return self.circular_buffer[(self.curr_position + 1)%(Solution171.STOP_VAL + 1)]

	def run_insert_operation(self, stop_val):
		for insert_val in range(1, stop_val+1):
			self.curr_position = ((self.steps_forward + self.curr_position) % insert_val) + 1
			self.operate(insert_val)

	def operate(self, insert_val):
		self.circular_buffer.insert(self.curr_position, insert_val)