import abc

class ControllerABC(metaclass=abc.ABCMeta):

	@abc.abstractmethod
	def line_reader(self):
		pass

	@abc.abstractmethod
	def process_data(self):
		return