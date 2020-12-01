from controller_abc import ControllerABC

class Solution151(ControllerABC):

	GENERATOR_FACTOR = {'A':16807, 'B':48271}
	DIVISOR = 2147483647
	BASE_VAL = (2 << 15) - 1
	NO_OF_PAIRS = 40000000

	def __init__(self):
		self.valid_pair_count = 0
		self.generator_value = {}

	def line_reader(self, line):
		line_split = line.rstrip('\n').split()
		self.generator_value[line_split[1]] = int(line_split[4])

	def process_data(self):
		return self.generate_pairs(Solution151.NO_OF_PAIRS)

	def generate_pairs(self, no_of_pairs):
		for i in range(0, no_of_pairs):
			if self.compute_next('A') & Solution151.BASE_VAL == self.compute_next('B') & Solution151.BASE_VAL:
				self.valid_pair_count += 1
		return self.valid_pair_count

	def compute_next(self, key):
		self.generator_value[key] = (self.generator_value[key] * Solution151.GENERATOR_FACTOR[key]) % Solution151.DIVISOR
		return self.generator_value[key]
