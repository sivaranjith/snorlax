from problem_12_1 import Solution121

class Solution122(Solution121):

	def process_data(self):
		programs = set(list(range(0, len(self.program_connections))))
		groups = 0
		while len(programs) > 0:
			programs -= self.get_connect_components(next(iter(programs)))
			groups += 1

		return groups