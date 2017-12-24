from controller_abc import ControllerABC

class Solution221(ControllerABC):

	NO_OF_ITERATIONS = 10000
	# DIRECTIONS = ['N', 'E', 'S', 'W'] #written for understanding. since in the code only the corresponding index are used

	def __init__(self):
		self.infected_count = 0
		self.grid = []
		self.current_direction = 0

	def line_reader(self, line):
		self.grid.append(list(line.rstrip('\n').replace(' ','')))

	def process_data(self):
		return self.clean_infected(Solution221.NO_OF_ITERATIONS)

	def clean_infected(self, speed):
		self.get_starting_position()
		for _ in range(0, speed):
			self.change_state_direction()
			self.move_forward()
		return self.infected_count

	def change_state_direction(self):
		if self.grid[self.x][self.y] == '.':
			self.grid[self.x][self.y] = '#'
			self.infected_count += 1
			self.current_direction = (self.current_direction - 1) % 4
		else:
			self.grid[self.x][self.y] = '.'
			self.current_direction = (self.current_direction + 1) % 4

	def move_forward(self):
		if self.current_direction == 0:
			if self.x > 0:
				self.x -= 1
			else:
				self.insert_row()
		elif self.current_direction == 1:
			self.y += 1
			if self.y == len(self.grid[0]):
				self.insert_column()
		elif self.current_direction == 2:
			self.x += 1
			if self.x == len(self.grid):
				self.insert_row()
		else:
			if self.y > 0:
				self.y -= 1
			else:
				self.insert_column()

	def insert_row(self):
		ele_list = ['.' for _ in range(0, len(self.grid[0]))]
		self.grid.insert(self.x, ele_list)

	def insert_column(self):
		for row in self.grid:
			row.insert(self.y, '.')

	def get_starting_position(self):
		self.x = len(self.grid)//2
		self.y = len(self.grid[0])//2