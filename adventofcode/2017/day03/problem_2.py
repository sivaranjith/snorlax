from problem_1 import Solution031

class Solution032(Solution031):

	def process_data(self):
		#value must be an odd number
		for matrix_size in range(1, 101, 2):
			if self.finding_matrix(matrix_size):
				break

		return self.matrix[self.starting_coordinate_x][self.starting_coordinate_y]

	def finding_matrix(self, matrix_size):
		self.starting_coordinate_x = matrix_size//2
		self.starting_coordinate_y = self.starting_coordinate_x
		self.matrix = [[0 for _2 in range(matrix_size)] for _1 in range(matrix_size)]
		self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = 1

		# print(self.matrix)
		is_coordinates_found = False
		for steps in range(1, matrix_size-1, 2):
			if self.fill_layer(steps, matrix_size):
				is_coordinates_found = True
				break

		return is_coordinates_found

	def fill_layer(self, steps, matrix_size):
		#one step to the right and checking
		self.starting_coordinate_y += 1
		self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = self.matrix[self.starting_coordinate_x][self.starting_coordinate_y-1] + self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y-1]

		# print(self.matrix)
		if self.check_coordinates_value():
			return True

		#steps moving up and checking
		for _ in range(0,steps):
			self.starting_coordinate_x -= 1

			self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y] + self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y-1] + self.matrix[self.starting_coordinate_x][self.starting_coordinate_y-1] + (self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y-1] if self.starting_coordinate_x != 0 else 0)

			if self.check_coordinates_value():
				return True
		# print(self.matrix)

		#steps + 1 moving in corresponding directions and checking
		#moving left
		for _ in range(0,steps+1):
			self.starting_coordinate_y -= 1

			self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = self.matrix[self.starting_coordinate_x][self.starting_coordinate_y+1] + self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y+1] + self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y] + (self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y-1] if self.starting_coordinate_y != 0 else 0)

			if self.check_coordinates_value():
				return True
		# print(self.matrix)

		#moving down
		for _ in range(0,steps+1):
			self.starting_coordinate_x += 1

			self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y] + self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y+1] + self.matrix[self.starting_coordinate_x][self.starting_coordinate_y+1] + (self.matrix[self.starting_coordinate_x+1][self.starting_coordinate_y+1] if self.starting_coordinate_x + 1 != matrix_size else 0)

			if self.check_coordinates_value():
				return True
		# print(self.matrix)

		#moving right
		for _ in range(0,steps+1):
			self.starting_coordinate_y += 1

			self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] = self.matrix[self.starting_coordinate_x][self.starting_coordinate_y-1] + self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y-1] + self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y] + (self.matrix[self.starting_coordinate_x-1][self.starting_coordinate_y+1] if self.starting_coordinate_y + 1 != matrix_size else 0)

			if self.check_coordinates_value():
				return True
		# print(self.matrix)

	def check_coordinates_value(self):
		return self.matrix[self.starting_coordinate_x][self.starting_coordinate_y] > self.data
