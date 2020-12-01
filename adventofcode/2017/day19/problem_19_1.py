from controller_abc import ControllerABC

class Solution191(ControllerABC):

	NEXT_STEP = {'D':(lambda self: self.line_no + 1), 'U':(lambda self:self.line_no - 1), 'R':(lambda self: self.curr_index + 1), 'L':(lambda self: self.curr_index - 1)}
	CHANGE_DIRECTION_CONDITION = {'D':(lambda self, check: self.line_no < self.no_of_lines - 1 and check(self.grid[self.line_no + 1][self.curr_index])),
								  'U':(lambda self, check: self.line_no > 0 and check(self.grid[self.line_no - 1][self.curr_index])),
								  'L':(lambda self, check: self.curr_index > 0 and check(self.grid[self.line_no][self.curr_index - 1])),
								  'R':(lambda self, check: self.curr_index < self.length_of_lines - 1 and check(self.grid[self.line_no][self.curr_index + 1]))
									}

	def __init__(self):
		self.grid = []

	def line_reader(self, line):
		self.grid.append(line.rstrip('\n'))

	def process_data(self):
		self.curr_index = self.grid[0].index('|')
		self.line_no = 0
		self.no_of_lines = len(self.grid)
		self.length_of_lines = len(self.grid[0])
		self.curr_direction = 'D'
		answer = []

		while True:
			if self.curr_direction in ('U', 'D'):
				self.line_no = Solution191.NEXT_STEP[self.curr_direction](self)
			else:
				self.curr_index = Solution191.NEXT_STEP[self.curr_direction](self)
			self.change_direction()
			if self.is_character():
				answer.append(self.grid[self.line_no][self.curr_index])
			if self.curr_direction is None:
				break
		return ''.join(answer)

	def change_direction(self):
		checker = (lambda val: val == ' ')
		if (self.grid[self.line_no][self.curr_index] == '+' or Solution191.CHANGE_DIRECTION_CONDITION[self.curr_direction](self, checker)):
			self.curr_direction = self.switch_direction(['L', 'R']) if self.curr_direction in ('D', 'U') else self.switch_direction(['D', 'U'])

	def switch_direction(self, directions):
		new_direction = None
		checker = (lambda val: val != ' ')
		if Solution191.CHANGE_DIRECTION_CONDITION[directions[0]](self, checker):
			new_direction = directions[0]
		elif Solution191.CHANGE_DIRECTION_CONDITION[directions[1]](self, checker):
			new_direction = directions[1]
		return new_direction

	def is_character(self):
		val = self.grid[self.line_no][self.curr_index]
		return (ord(val) >= 65 and ord(val) <= 90) or (ord(val) >= 97 and ord(val) <= 122)
