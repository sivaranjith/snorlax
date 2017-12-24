from problem_20_1 import Solution201
import math

class Solution202(Solution201):

	def process_data(self):
		self.t = {}
		for _ in range(0, 40):#because of my trail code i knew all collision happened by 38 so just safty 1000
			hash_list = self.update_details_list(1)
			# print(_)
			self.remove_particles(_, hash_list)
		print(self.t)
		return len(self.particle_list)

	def operation(self, hash_list, details_list):
		hash_list.append(str(details_list[0][0]) + str(details_list[0][1]) + str(details_list[0][2]))

	def remove_particles(self, time, hash_list):
		black_list = set()
		for first_particle in range(0, len(self.particle_list)):
			# if not first_particle in black_list:
				for second_particle in range(first_particle + 1, len(self.particle_list)):
					# not second_particle in black_list and 
					if hash_list[first_particle] == hash_list[second_particle]:
						if time == 9 and second_particle == 148:
							print(first_particle, second_particle, hash_list[first_particle], hash_list[second_particle], hash_list[first_particle] == hash_list[second_particle])
						black_list.add(first_particle)
						black_list.add(second_particle)

		self.t[time] = black_list
		# print(black_list)
		new_particle_list = []
		for index in range(0, len(self.particle_list)):
			if not index in black_list:
				new_particle_list.append(self.particle_list[index])
		self.particle_list = new_particle_list