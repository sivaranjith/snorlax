from problem_13_1 import Solution131

class Solution132(Solution131):

	def process_data(self):
		return self.get_delay(self.generate_sequence())

	def generate_sequence(self):
		sequence_details = []
		for key, value in self.firewall_details.items():
			b = (value - 1) << 1
			sequence_details.append([b - key, b])
		return sequence_details

	def get_delay(self, sequence_details):
		delay = 0
		while True:
			delay += 1
			for item in sequence_details:
				if (delay - item[0]) % item[1] == 0:
					break
			else:
				break
		return delay