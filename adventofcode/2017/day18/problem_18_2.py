from problem_18_1 import Solution181

class Solution182(Solution181):

	PROGRAM_CONTAINER = {}

	def __init__(self):
		super().__init__()
		self.message_queue = []
		self.send_val_count = 0

	def set_params(self, program_id, instructions):
		self.program_id = program_id
		self.register_vals['p'] = program_id
		self.instructions = instructions

	def process_data(self):
		program_a = Solution182()
		program_b = Solution182()
		program_a.set_params(0, self.instructions)
		program_b.set_params(1, self.instructions)
		Solution182.PROGRAM_CONTAINER = {0:program_a, 1:program_b}

		while True:
			program_a.execute_instruction()
			program_b.execute_instruction()
			if len(program_a.message_queue) == 0 and len(program_b.message_queue) == 0:
				break

		return program_b.send_val_count

	def snd(self, register):
		self.send_val_count += 1
		Solution182.PROGRAM_CONTAINER[(self.program_id + 1) & 1].message_queue.append(self.get_val(str(register)))

	def rcv(self, register):
		return self.send_val_count if len(self.message_queue) == 0 else self.operate(['set', register, str(self.message_queue.pop(0))])
