from controller_abc import ControllerABC

class Solution051(ControllerABC):

	def __init__(self):
		self.jump_offset_list = []

	def line_reader(self, line):
		self.jump_offset_list.append(int(line))

	def process_data(self):
		step_count = 0
		index = 0
		offset_list_len = len(self.jump_offset_list)

		while True:
			offset = self.jump_offset_list[index]
			self.offset_modifier(index)
			index += offset
			step_count += 1

			if index < 0 or index >= offset_list_len:
				break

		return step_count

	def offset_modifier(self, index):
		self.jump_offset_list[index] += 1
