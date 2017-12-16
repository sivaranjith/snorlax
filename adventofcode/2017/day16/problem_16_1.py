from controller_abc import ControllerABC

class Solution161(ControllerABC):

	def __init__(self):
		self.programs = list('abcdefghijklmnop')

	def line_reader(self, line):
		self.dance_steps = line.rstrip('\n').split(',')

	def process_data(self):
		for step in self.dance_steps:
			if step[0] == 's':
				self.spin(int(step[1:]))
			elif step[0] == 'x':
				line_split = step[1:].split('/')
				self.exchange(int(line_split[0]), int(line_split[1]))
			elif step[0] == 'p':
				line_split = step[1:].split('/')
				self.partner(line_split[0], line_split[1])
		return ''.join(self.programs)

	def spin(self, quantity):
		self.programs = self.programs[-quantity:] + self.programs[:-quantity]

	def exchange(self, position_a, position_b):
		self.programs[position_a], self.programs[position_b] = self.programs[position_b], self.programs[position_a]

	def partner(self, char_a, char_b):
		self.exchange(self.programs.index(char_a), self.programs.index(char_b))