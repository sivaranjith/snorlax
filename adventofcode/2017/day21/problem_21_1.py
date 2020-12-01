from controller_abc import ControllerABC
import numpy as np

class Solution211(ControllerABC):

	NO_OF_ITERATIONS = 5

	def __init__(self):
		self.current_matrix = Solution211.str_to_matrix('.#./..#/###')
		self.hashmap = {}

	def line_reader(self, line):
		line_split = line.rstrip('\n').split(' => ')
		self.hashmap[line_split[0].replace('/', '')] = Solution211.str_to_matrix(line_split[1])

	def process_data(self):
		return self.find_switchon_pixels(Solution211.NO_OF_ITERATIONS)

	def find_switchon_pixels(self, iterations):
		for _ in range(0, iterations):
			self.form_new_grid(2) if len(self.current_matrix) & 1 == 0 else self.form_new_grid(3)
		return (self.current_matrix == '#').sum()

	def form_new_grid(self, mod_val):
		new_matrix = None
		for start_x in range(0, len(self.current_matrix), mod_val):
			row_width_matrix = None
			for start_y in range(0, len(self.current_matrix), mod_val):
				current_matrix = self.current_matrix[start_x : start_x + mod_val, start_y : start_y + mod_val]
				for i in range(0, 4):
					window = self.find_in_hash(np.rot90(current_matrix, i), start_x, start_y, mod_val)
					if not window is None:
						break
				if row_width_matrix is None:
					row_width_matrix = window
				else:
					row_width_matrix = np.concatenate((row_width_matrix, window), axis = 1)
			if new_matrix is None:
				new_matrix = row_width_matrix
			else:
				new_matrix = np.concatenate((new_matrix, row_width_matrix), axis = 0)
		self.current_matrix = new_matrix

	def find_in_hash(self, current_matrix, start_x, start_y, mod_val):
		flips = [Solution211.identity, np.fliplr]
		for flip in flips:
			cur = Solution211.matrix_to_str(flip(current_matrix), start_x, start_y, mod_val)
			if cur in self.hashmap:
				return self.hashmap[cur]

	def identity(current_matrix):
		return current_matrix

	def matrix_to_str(current_matrix, start_x, start_y, mod_val):
		result_str = ''
		for x in range(0, len(current_matrix)):
			for y in range(0, len(current_matrix)):
				result_str += current_matrix[x][y]
		return result_str

	def str_to_matrix(line):
		result = []
		for row in line.split('/'):
			result.append(list(row))
		return np.array(result, str)