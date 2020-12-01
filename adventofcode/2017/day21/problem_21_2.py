from problem_21_1 import Solution211

class Solution212(Solution211):

	NO_OF_ITERATIONS = 18

	def process_data(self):
		return self.find_switchon_pixels(Solution212.NO_OF_ITERATIONS)