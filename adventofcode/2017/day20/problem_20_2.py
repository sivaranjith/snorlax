from problem_20_1 import Solution201
import math

class Solution202(Solution201):

	def process_data(self):
		black_list = {}
		for first_particle in range(0, len(self.particle_list)):
				for second_particle in range(first_particle + 1, len(self.particle_list)):
					if self.can_particle_collide(first_particle, second_particle):
						if not self.time in black_list:
							black_list[self.time] = set()
						black_list[self.time].add(first_particle)
						black_list[self.time].add(second_particle)
		all_vals = {i for i in range(0, len(self.particle_list))}
		removed = set()
		for key, vals in sorted(black_list.items()):
			if len(vals - removed) > 1:
				all_vals -= (vals - removed)
				removed = removed.union(set(vals))
		return len(all_vals)

	def can_particle_collide(self, first_particle, second_particle):
		first_details_list = self.particle_list[first_particle]
		second_details_list = self.particle_list[second_particle]
		colliding_index = []
		for index in range(0, 3):
			a = first_details_list[2][index] - second_details_list[2][index]
			v = first_details_list[1][index] - second_details_list[1][index]
			d = first_details_list[0][index] - second_details_list[0][index]
			b = 2*v + a
			c = 2 * d
			if a != 0:
				diff = b ** 2 - 4 * a * c
				if diff < 0:
					return False
				diff = int(math.sqrt(diff))
				val1 = -1 * b + diff
				val2 = -1 * b - diff
				den = 2 * a
				if (val1 % den != 0  or val1 // den < 0) and (val2 % den != 0  or val2 // den < 0):
					return False
				timings = set()
				if not (val1 % den != 0  or val1 // den < 0):
					timings.add(abs(val1 // den))
				if not (val2 % den != 0  or val2 // den < 0):
					timings.add(abs(val2 // den))
				colliding_index.append(timings)
			elif c == 0:
				colliding_index.append({0})
			elif b == 0 or (c % b != 0 or c // b > 0):
				return False
			else:
				colliding_index.append({abs(c // b)})
		if len(colliding_index[0].intersection(colliding_index[1])) > 0 and len(colliding_index[1].intersection(colliding_index[2])) > 0:
			self.time = list(colliding_index[0].intersection(colliding_index[1]))[0]
			return True
		else:
			return False

	def position(self, index, particle_index):
		details_list = self.particle_list[particle_index]
		distance_list = []
		for i in range(0, 3):
			distance_list.append(details_list[0][i] + index*details_list[1][i] + self.sum_of_numbers(index)*details_list[2][i])
		return distance_list