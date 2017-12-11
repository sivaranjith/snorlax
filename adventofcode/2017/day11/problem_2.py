from problem_1 import Solution111

class Solution112(Solution111):

	def process_data(self):
		max_distance = 0
		for direction in self.directions_list:
			self.count_dict[direction] += 1
			temp_distance = self.distance_calculator()
			if max_distance < temp_distance:
				max_distance = temp_distance

		return max_distance

