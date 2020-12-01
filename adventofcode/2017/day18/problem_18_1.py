from controller_abc import ControllerABC

class Solution181(ControllerABC):

	OPERATIONS = {'add':(lambda val1, val2: val1 + val2), 'mul':(lambda val1, val2: val1 * val2), 'mod':(lambda val1, val2: val1 % val2)}

	def __init__(self):
		self.register_vals = {}
		self.played_frequency = None
		self.instructions = []
		self.curr_index = 0

	def line_reader(self, line):
		self.instructions.append(line.strip('\n').split())

	def process_data(self):
		return self.execute_instruction()
		
	def execute_instruction(self):
		while True:
			line_split = self.instructions[self.curr_index]
			if 'snd' == line_split[0]:
				self.snd(line_split[1])
			elif line_split[0] in ('set', 'add', 'mul', 'mod'):
				self.operate(line_split)
			elif 'rcv' == line_split[0]:
				rcv_val = self.rcv(line_split[1])
				if rcv_val != None:
					return rcv_val
			elif 'jgz' == line_split[0] and self.get_val(line_split[1]) > 0:
				self.curr_index += self.get_val(line_split[2])
				continue
			self.curr_index += 1

	def rcv(self, register):
		return self.played_frequency

	def snd(self, register):
		self.played_frequency = self.register_vals[register]

	def operate(self, line_split):
		val1 = self.get_val(line_split[2])
		val2 = self.register_vals[line_split[1]] if line_split[1] in self.register_vals else 0
		self.register_vals[line_split[1]] = val1 if 'set' == line_split[0] else Solution181.OPERATIONS[line_split[0]](val2, val1)

	def get_val(self, word):
		val1 = 0
		if word.lstrip('-').isnumeric():
			val1 = int(word)
		elif word in self.register_vals:
			val1 = self.register_vals[word]
		return val1