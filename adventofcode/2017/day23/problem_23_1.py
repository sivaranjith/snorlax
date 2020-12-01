from controller_abc import ControllerABC

class Solution231(ControllerABC):

	def __init__(self):
		self.register_vals = {'a':0, 'b':0, 'c':0, 'd':0, 'e':0, 'f':0, 'g':0, 'h':0}
		self.instructions = []

	def line_reader(self, line):
		self.instructions.append(line.rstrip('\n').split())

	def process_data(self):
		index = 0
		instructions_len = len(self.instructions)
		result = 0
		while index < instructions_len:
			instruction = self.instructions[index]
			if instruction[0] == 'set':
				self.register_vals[instruction[1]] = self.get_val(instruction[2])
			elif instruction[0] == 'sub':
				self.register_vals[instruction[1]] -= self.get_val(instruction[2])
			elif instruction[0] == 'mul':
				self.register_vals[instruction[1]] *= self.get_val(instruction[2])
				result += 1
			elif instruction[0] == 'jnz':
				if self.get_val(instruction[1]) != 0:
					index += self.get_val(instruction[2])
					continue
			index += 1

		return result

	def get_val(self, var):
		return int(var) if len(var) > 1 or (ord(var) >= 48 and ord(var) <= 57) else self.register_vals[var]