from controller_abc import ControllerABC

class Solution251(ControllerABC):

	def __init__(self):
		self.state = {}
		self.turing_machine = [0]
		self.curr_position = 0

	def line_reader(self, line):
		line = line.strip().rstrip('\n')
		if line.startswith("Begin in state"):
			self.staring_state = line[15]
		elif line.startswith("Perform a diagnostic checksum after "):
			self.steps = int(line.lstrip("Perform a diagnostic checksum after ").rstrip(" steps."))
		elif line.startswith("In state "):
			self.curr_state = line[9]
			self.state[self.curr_state] = {}
		elif line.startswith("If the current value is "):
			self.curr_val = int(line[24])
			self.state[self.curr_state][self.curr_val] = []
		elif line.startswith("- Write the value "):
			self.state[self.curr_state][self.curr_val].append(int(line[18]))
		elif line.startswith("- Move one slot to the "):
			self.state[self.curr_state][self.curr_val].append(1 if line[23] == 'r' else -1)
		elif line.startswith("- Continue with state "):
			self.state[self.curr_state][self.curr_val].append(line[22])

	def process_data(self):
		self.curr_state = self.staring_state
		for _ in range(0, self.steps):
			self.curr_val = self.turing_machine[self.curr_position]
			instructions = self.state[self.curr_state][self.curr_val]
			self.turing_machine[self.curr_position] = instructions[0]
			if instructions[1] == -1:
				if self.curr_position == 0:
					self.turing_machine.insert(0, 0)
				else:
					self.curr_position -= 1
			else:
				if self.curr_position + 1 == len(self.turing_machine):
					self.turing_machine.append(0)
				self.curr_position += 1
			self.curr_state = instructions[2]
		return self.count_checksum()

	def count_checksum(self):
		count = 0
		for ele in self.turing_machine:
			if ele == 1:
				count += 1
		return count