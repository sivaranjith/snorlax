from problem_22_1 import Solution221

class Solution222(Solution221):

	NO_OF_ITERATIONS = 10000000

	def process_data(self):
		return self.clean_infected(Solution222.NO_OF_ITERATIONS)

	def change_state_direction(self):
		if self.grid[self.x][self.y] == '.':
			self.grid[self.x][self.y] = ','
			self.current_direction = (self.current_direction - 1) % 4
		elif self.grid[self.x][self.y] == ',':
			self.grid[self.x][self.y] = '#'
			self.infected_count += 1
		elif self.grid[self.x][self.y] == '#':
			self.current_direction = (self.current_direction + 1) % 4
			self.grid[self.x][self.y] = '!'
		elif self.grid[self.x][self.y] == '!':
			self.grid[self.x][self.y] = '.'
			self.current_direction = (self.current_direction - 2) % 4
