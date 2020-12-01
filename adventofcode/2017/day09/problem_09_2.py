from problem_09_1 import Solution091

class Solution092(Solution091):

	def process_data(self):
		return self.get_garbage_count()

	def get_garbage_count(self):
		is_valid = True
		curr_index = 0
		garbage_count = 0
		while curr_index < len(self.line):
			if is_valid and self.line[curr_index] == '<':
				is_valid = False
			elif self.line[curr_index] == '!':
				curr_index += 1
			elif not is_valid and self.line[curr_index] == '>':
				is_valid = True
			elif not is_valid:
				garbage_count += 1
			curr_index += 1

		return garbage_count

