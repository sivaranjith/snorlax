import math

class Solution031:
	def line_reader(self, line):
		self.data = int(line)

	def process_data(self):
		steps = 0

		if self.data > 1:
			#calculating the layer no and corresponding details
			sqrt_val = int(math.sqrt(self.data))
			floor_odd = sqrt_val if sqrt_val & 1 else sqrt_val - 1
			ceil_odd = floor_odd + 2
			min_step = ceil_odd//2

			#calculating the four corner values
			floor_odd_sqr = floor_odd**2
			right_bottom = ceil_odd**2
			left_bottom = right_bottom - ceil_odd + 1
			left_top = left_bottom - ceil_odd + 1
			right_top = left_top - ceil_odd + 1

			#getting the mid value of the particular side
			if self.data <= right_top:
				mid = floor_odd_sqr + min_step
			elif self.data <= left_top:
				mid = right_top + min_step
			elif self.data <= left_bottom:
				mid = left_top + min_step
			else:
				mid = left_bottom + min_step

			#since the value range from min_step to 2*min_step. finding the exact value
			steps = min_step + abs(mid - self.data)

		print(steps)
