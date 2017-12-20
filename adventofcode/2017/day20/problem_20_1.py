from controller_abc import ControllerABC

class Solution201(ControllerABC):

	def __init__(self):
		self.particle_list = []

	def line_reader(self, line):
		line_split = line.rstrip('\n').rstrip('>').split('>, ')
		details_list = []
		for pharse in line_split:
			pharse_split = pharse.split('<')[1].split(',')
			details = [int(pharse_split[0]), int(pharse_split[1]), int(pharse_split[2])]
			details_list.append(details)
		self.particle_list.append(details_list)

	def process_data(self):
		distance_list = self.update_details_list(10000000)
		return distance_list.index(min(distance_list))

	def update_details_list(self, index):
		distance_list = []
		for details_list in self.particle_list:
			for i in range(0, 3):
				details_list[0][i] += index*details_list[1][i] + self.sum_of_numbers(index)*details_list[2][i]
				details_list[1][i] += index*details_list[2][i]
			self.operation(distance_list, details_list)
		return distance_list

	def operation(self, distance_list, details_list):
		distance_list.append(self.calculate_distance(details_list[0]))

	def sum_of_numbers(self, no):
		return no*(no + 1)//2

	def calculate_distance(self, position):
		return abs(position[0]) + abs(position[1]) + abs(position[2])