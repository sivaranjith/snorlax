from problem_20_1 import Solution201
import math

class Solution203(Solution201):

	def process_data(self):
		black_list = {}
		for first_particle in range(0, len(self.particle_list)):
			if not first_particle in black_list:
				for second_particle in range(first_particle + 1, len(self.particle_list)):
					if not second_particle in black_list and self.can_particle_collide(first_particle, second_particle):
						# if self.position(self.time, first_particle) == self.position(self.time, second_particle):
							# print(first_particle, second_particle)
						if not self.time in black_list:
							black_list[self.time] = set()
						black_list[self.time].add(first_particle)
						black_list[self.time].add(second_particle)
		# print(black_list)
		all_vals = {i for i in range(0, len(self.particle_list))}
		removed = set()
		for key, vals in sorted(black_list.items()):
			print(key,len(vals), len(removed))
			if len(vals - removed) > 1:
				all_vals -= (vals - removed)
				removed = removed.union(set(vals))
			else:
				print("FU")
		print(len(removed))
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
				# print(a, b, c, diff, val1, val2, den, val1 % den, val1 // den, val2 % den, val2 // den)
				if (val1 % den != 0  or val1 // den < 0) and (val2 % den != 0  or val2 // den < 0):
					return False
				elif not (val1 % den != 0  or val1 // den < 0):
					colliding_index.append(val1 // den)
				else:
					colliding_index.append(val2 // den)
			elif c == 0:
				colliding_index.append(0)
			elif b == 0 or (c % b != 0 or c // b > 0):
				return False
			else:
				colliding_index.append(c // b)
		self.time = abs(colliding_index[0])
		# print(self.position(abs(colliding_index[0]), first_particle))
		# print(self.position(abs(colliding_index[0]), second_particle))
		return abs(colliding_index[0]) == abs(colliding_index[1]) and abs(colliding_index[0]) == abs(colliding_index[2])# and self.position(abs(colliding_index[0]), first_particle) == self.position(abs(colliding_index[0]), second_particle)

	def position(self, index, particle_index):
		details_list = self.particle_list[particle_index]
		distance_list = []
		for i in range(0, 3):
			distance_list.append(details_list[0][i] + index*details_list[1][i] + self.sum_of_numbers(index)*details_list[2][i])
		return distance_list
