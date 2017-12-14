from problem_07_1 import Solution071

class Solution072(Solution071):

	def process_data(self):
		for key, value in self.program_details.items():
			if value.sum_weight == -1:#condition as in the calculate_sum_weights function just to avoid a function call
				self.calculate_sum_weights(key)

		root_element = super().process_data()
		self.find_wrong_weight_program(root_element)

		return self.wrong_weight

	def calculate_sum_weights(self, key):
		value = self.program_details[key]
		value.sum_weight = value.weight

		for child in value.child_names:
			value.sum_weight += self.calculate_sum_weights(child)
		return value.sum_weight

	def find_wrong_weight_program(self, key):
		value = self.program_details[key]
		child_list = list(value.child_names)
		weight_list = [self.program_details[child].sum_weight for child in child_list]
		max_weight = max(weight_list)
		min_weight = min(weight_list)
		max_child = None if max_weight == min_weight else child_list[weight_list.index(max_weight)]

		if not max_child is None:
			max_child1 = self.find_wrong_weight_program(max_child)
			if max_child1 is None:
				self.wrong_weight = self.program_details[max_child].weight - (max_weight - min_weight)
				max_child = key
		return max_child