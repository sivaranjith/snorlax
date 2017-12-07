from problem_1 import Solution061

class Solution062(Solution061):

	def process_data(self):
		super().process_data()
		return len(self.pattern_list) - self.pattern_list.index(self.matched_pattern)