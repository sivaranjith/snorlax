from problem_15_1 import Solution151

class Solution152(Solution151):

	DIVISOR_VALS = {'A':4, 'B':8}
	Solution151.NO_OF_PAIRS = 5000000

	def compute_next(self, key):
		while super().compute_next(key) % Solution152.DIVISOR_VALS[key] != 0:
			pass
		return self.generator_value[key]