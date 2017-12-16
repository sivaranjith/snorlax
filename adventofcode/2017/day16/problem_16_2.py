from problem_16_1 import Solution161

class Solution162(Solution161):

	def process_data(self):
		temp = self.dance_steps
		self.dance_steps = self.dance_steps[10001:]#since @10000 the pattern gets completed
		super().process_data()#since iteration needs to run from that point completed cycle
		self.dance_steps = temp#the back to full data
		#found the starting value by seeing if the pattern repeats after any iteration. Also since one iteration is done above increasing the number to 999999966
		for _ in range(999999966, 1000000000):
			result = super().process_data()
		return result