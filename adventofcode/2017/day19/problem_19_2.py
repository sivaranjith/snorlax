from problem_19_1 import Solution191

class Solution192(Solution191):

	def __init__(self):
		super().__init__()
		self.steps = 1

	def process_data(self):
		super().process_data()
		return self.steps

	def change_direction(self):
		super().change_direction()
		self.steps += 1