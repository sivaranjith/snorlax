from problem_1 import Solution051

class Solution052(Solution051):

	def offset_modifier(self, index):
		if self.jump_offset_list[index] >= 3:
			self.jump_offset_list[index] -= 1
		else:
			self.jump_offset_list[index] += 1